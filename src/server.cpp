#include <iostream>
#include "common.h"
#include "database.h"
#include "httplib.h"

using namespace std;

class IServer {
    public:
        IServer()= default;
        virtual void start() = 0;
};

class Server: public IServer {
    public:
        #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
        httplib::SSLServer *http_server;
        #else
        httplib::Server *http_server;
        #endif

        DataBase *database;
        Server() {
            #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
            this->http_server = new httplib::SSLServer(SSL_CERT_FILE, SSL_KEY_FILE);
            #else
            this->http_server = new httplib::Server; //("/tmp/test.csr", "/tmp/test.key");
            #endif

            this->database = new DataBase(DATABASE_FILE);
        }

        void start() override {
            DEBUG("Setting up /get endpoint" << endl);
            this->http_server->Get("/get", [&](const httplib::Request &req, httplib::Response &res) {
                if (req.has_param("key")) {
                    string key = req.get_param_value("key");
                    optional<string> value = this->database->read_record(key);
                    res.set_content(*value, "text/plain");
                } else {
                    res.set_content("", "text/plain");
                }
            });

            DEBUG("Setting up /put endpoint" << endl);
            this->http_server->Get("/put", [&](const httplib::Request &req, httplib::Response &res) {
                if (req.has_param("key") && req.has_param("value")) {
                    string key = req.get_param_value("key");
                    string value = req.get_param_value("value");
                    this->database->write_record(key, value);
                    res.set_content("success", "text/plain");
                } else {
                    res.set_content("failure", "text/plain");
                }
            });

            DEBUG("Setting up /delete endpoint" << endl);
            this->http_server->Get("/delete", [&](const httplib::Request &req, httplib::Response &res) {
                if (req.has_param("key")) {
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

};


int main() {
    DEBUG("Starting a Server instance" << endl);
    auto *server = new Server;
    server->start();
}
