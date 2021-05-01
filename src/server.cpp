#include <iostream>
#include "common.h"
#include "database.h"
#include "httplib.h"

using namespace std;

class IServer{
    public:
    virtual std::string read_query(std::string key) = 0;
    virtual void write_query(std::string key, std::string value) = 0;

};

class Server: public IServer, public DataBase {
    public:
        httplib::Server *http_server;
        Server(){
            this-> http_server = new httplib::Server;

            // set up routes for read/write query
            
            // this-> http_server.listen("0.0.0.0", 4444);
        }
        std::string read_query(std::string key);
        void write_query(std::string key, std::string value);

};

std::string Server::read_query(std::string key){
    std::string key;
    // get key from client over REST

    std::string value = DataBase::read(key);

    //send the value back to the client
    
    return value;
}

void Server::write_query(std::string key, std::string value)
{
     std::string key;
     std::string value;
    // get key,value from client over REST

    DataBase::write(key,value);

}


int main()
{
    std::cout << "Server::main" << std::endl;
    
}