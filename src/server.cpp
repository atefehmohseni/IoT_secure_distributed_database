#include <iostream>
#include "common.h"
#include "database.h"
#include "httplib.h"

using namespace std;

class IServer {
    public:
    virtual optional<string> read_query(string key) = 0;
    virtual void write_query(string key, string value) = 0;

};

class Server: public IServer, public DataBase {
    public:
        httplib::Server *http_server;
        Server(){
            this-> http_server = new httplib::Server;

            // set up routes for read/write query
            
            //this-> http_server.listen("0.0.0.0", 4444);
        }
        optional<string> read_query(string key);
        void write_query(string key, string value);

};

optional<string> Server::read_query(string key) {
    optional<string> value = DataBase::read(key);
    return value;
}

void Server::write_query(string key, string value) {
    DataBase::write(key,value);
}


int main() {
    DEBUG("Starting a Server instance");
    Server *server = new Server();
}
