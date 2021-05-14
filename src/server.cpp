#include <iostream>
#include "common.h"
#include "database.h"
#include "httplib.h"

using namespace std;

class IServer {
    public:
        IServer(){}
};

class Server: public IServer {
    public:
        httplib::Server *http_server;
        DataBase *database;
        Server() {
            this->http_server = new httplib::Server;
            this->database = new DataBase;

            DEBUG("Setting up /read endpoint");
            this->http_server->Get("/read", [&](const httplib::Request &req, httplib::Response &res) {
                if (req.has_param("key")) {
                    string key = req.get_param_value("key");
                    optional<string> value = this->database->read(key);
                    res.set_content(value->c_str(), "text/plain");
                } else {
                    res.set_content("", "text/plain");
                }
            });

            DEBUG("Setting up /write endpoint");
            this->http_server->Get("/write", [&](const httplib::Request &req, httplib::Response &res) {
                if (req.has_param("key") && req.has_param("value")) {
                    string key = req.get_param_value("key");
                    string value = req.get_param_value("value");
                    this->database->write(key, value);
                    res.set_content("success", "text/plain");
                } else {
                    res.set_content("failure", "text/plain");
                }
            });

            DEBUG("Listening on 0.0.0.0:4444");
            this-> http_server->listen("0.0.0.0", 4444);
        }

};


int main() {
    DEBUG("Starting a Server instance");
    Server *server = new Server;
}
