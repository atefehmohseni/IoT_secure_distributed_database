#include <iostream>
#include "base64.h"
#include "bcrypt.h"
#include "common.h"
#include "database.h"
#include "httplib.h"

using namespace std;

class IServer {
    public:
        IServer()= default;
        virtual void start() = 0;
        virtual int backup() = 0;
    private:
        virtual bool check_authorization(const httplib::Request &req) = 0;
};
//
// This server is running at the edge
//
class Server: public IServer {
    public:
        #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
        httplib::SSLServer *http_server;
        #else
        httplib::Server *http_server;
        #endif

        // define an http client to connect to the server in cloud
        httplib::Client *http_client;

        DataBase *database;
        DataBase *credentials;
        DataBase *salts;

        string server_unique_id;

        int write_counter;

        Server() {
            #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
            this->http_server = new httplib::SSLServer(SSL_CERT_FILE, SSL_KEY_FILE);
            #else
            this->http_server = new httplib::Server; //("/tmp/test.csr", "/tmp/test.key");
            #endif

            // set up an httpclient to connect to the master server (in cloud)
            this->http_client = new httplib::Client("http://localhost:5555");

            this->database = new DataBase(DATABASE_FILE);
            this->credentials = new DataBase(CREDENTIALS_FILE);
            this->salts = new DataBase(SALTS_FILE);

            this->write_counter = 0;         

            //TODO: make server IDs unique
            this->server_unique_id="100";
        }

        int backup() override {
            DEBUG("Backup local data to the cloud" << endl);
            //this->http_client->set_compress(true);
            //?id="+this->server_unique_id).c_str()
            auto res = this->http_client->Post("/backup",this->database->get_database().dump(),"application/json");
            if (res != nullptr && res->status == 200) {
                return res->status;
            } else {
                return 0;
            }
        }

        void start() override {
            DEBUG("Setting up /get endpoint" << endl);
            this->http_server->Get("/get", [&](const httplib::Request &req, httplib::Response &res) {
                if (!this->check_authorization(req)) {
                    res.set_header("WWW-Authenticate", "Basic");
                    res.status = 401;
                } else if (req.has_param("key")) {
                    string key = req.get_param_value("key");
                    string value = this->database->read_record(key);
                    res.set_content(value, "text/plain");
                } else {
                    res.set_content("", "text/plain");
                }
            });

            DEBUG("Setting up /put endpoint" << endl);
            this->http_server->Get("/put", [&](const httplib::Request &req, httplib::Response &res) {
                if (!this->check_authorization(req)) {
                    res.set_header("WWW-Authenticate", "Basic");
                    res.status = 401;
                } else if (req.has_param("key") && req.has_param("value")) {
                    string key = req.get_param_value("key");
                    string value = req.get_param_value("value");
                    this->database->write_record(key, value);

                    this->write_counter++;
                    if(this->write_counter == BACKUP_FREQUENCY){
                        int res = this->backup();
                        //cout<<res<<endl;
                        if(res == 200){
                        //after a successful backup, set write-operation counter to zero
                            DEBUG("Succefuly backed up!" << endl);
                            this->write_counter=0;
                        }
                    }
                    res.set_content("success", "text/plain");
                } else {
                    res.set_content("failure", "text/plain");
                }
            });

            DEBUG("Setting up /delete endpoint" << endl);
            this->http_server->Get("/delete", [&](const httplib::Request &req, httplib::Response &res) {
                if (!this->check_authorization(req)) {
                    res.set_header("WWW-Authenticate", "Basic");
                    res.status = 401;
                } else if (req.has_param("key")) {
                    string key = req.get_param_value("key");
                    this->database->delete_record(key);
                    res.set_content("success", "text/plain");
                } else {
                    res.set_content("failure", "text/plain");
                }
            });

            DEBUG("Binding to 0.0.0.0:4444" << endl);
            if (!this->http_server->listen("0.0.0.0", 4444)) {
                ERROR("Cannot bind to 0.0.0.0:4444" << endl);
            }
        }
    private:
        bool check_authorization(const httplib::Request &req) override {
            if (!req.has_header("Authorization")) {
                DEBUG("Not Authorized: missing Authorization header" << endl);
                return false;
            }

            string auth_header = req.get_header_value("Authorization");
            if ((auth_header.rfind("Basic", 0) == 0)) {
                //Extract credentials (skip "Basic")
                string b64_credentials = auth_header.substr(6);
                string credentials(b64_credentials.length() / 4 * 3, '\00');
                Base64::Decode(b64_credentials, credentials);

                // split username:password
                int delimiter = credentials.find_first_of(':');
                string username = credentials.substr(0, delimiter);
                string password = credentials.substr(delimiter+1);

                // read stored (hashed) password
                string stored_hash = this->credentials->read_record(username);

                if (stored_hash.empty()) {
                    // username not in the database
                    DEBUG("Not Authorized: username not in the database" << endl);
                    return false;
                }

                // read the stored salt
                string salt = this->salts->read_record(username);
                assert(!salt.empty());  // this should never happen

                // hash with bcrypt (with salt)
                char hash[BCRYPT_HASHSIZE] = {'\00'};
                bcrypt_hashpw(password.c_str(), salt.c_str(), hash);

                // compare the stored hash with the computed hash
                string computed_hash(hash);
                if (stored_hash == hash) {
                    return true;
                }
            }

            DEBUG("Not Authorized: failed to verify username:password" << endl);
            return false;
        }
};


int main() {
    DEBUG("Starting a Server instance" << endl);
    auto *server = new Server;
    server->start();
}
