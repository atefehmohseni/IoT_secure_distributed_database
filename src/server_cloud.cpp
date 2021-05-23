#include <iostream>
#include<fstream>
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
            this->http_server->Post("/backup", [&](const auto& req, auto& res) {
            auto size = req.files.size();
            auto ret = req.has_file("backup_100");
            auto file = req.get_file_value("backup_100");

            ofstream ofs(file.filename);
            ofs << file.content;

            });
          
            DEBUG("Binding to 0.0.0.0:5555" << endl);
            if (!this->http_server->listen("0.0.0.0", 5555)) {
                ERROR("Cannot bind to 0.0.0.0:5555" << endl);
            }
        }
};  

int main() {
    DEBUG("Starting the Cloud Server" << endl);
    auto *master_server = new ServerCloud;
    master_server->start();
}
