#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include "common.h"
#include "database.h"
#include "httplib.h"

using namespace std;

class IServer {
    public:
        IServer()= default;
};

class Server: public IServer {
    public:
        httplib::Server *http_server;
        DataBase *database;
        Server() {
            this->http_server = new httplib::Server; //("/tmp/test.csr", "/tmp/test.key");
            this->database = new DataBase;

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

            DEBUG("Listening on 0.0.0.0:4444" << endl);
            this->http_server->listen("0.0.0.0", 4444);
        }

};


int main() {
    DEBUG("Starting a Server instance" << endl);
    auto *server = new Server;
}
