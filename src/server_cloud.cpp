#include <iostream>
#include "common.h"
#include "database.h"
#include "httplib.h"

using namespace std;

class IServerCloud {
    public:
        IServerCloud() = default;
        virtual void start() = 0;
};

//
// This server is running in teh Cloud
//
class ServerCloud: public IServerCloud {
    public:
        httplib::Server *http_server;
    
         DataBase *database;

        ServerCloud(){
            this->http_server = new httplib::Server;

            this->database = new DataBase(DATABASE_FILE_CLOUD);

        }
    
        void start() override {
            DEBUG("Setting up /backup endpoint" << endl);
            this->http_server->Get("/backup", [&](const httplib::Request &req, httplib::Response &res) {
            if (req.has_param("id")) {
                string server_id = req.get_param_value("id");

                //extract the attached file to the request and updatet the cloud_database
               
                res.set_content("", "text/plain");
            });
        }
}   

int main() {
    DEBUG("Starting the Cloud Server" << endl);
    auto *master_server = new ServerCloud;
    master_server->start();
}
