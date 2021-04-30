/*
our database query language supports two queries:
- read key
- write key value
*/

#include<iostream>
#include<fstream>
#include "common.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

string DATABASE_FILE = "./database.json";

class IDataBase {
    public:
        virtual std::string read(std::string key) = 0;
        virtual void delete_record(std::string key) = 0;
        virtual void write(string key, string value) = 0;
};

class DataBase : public IDataBase{
    private:
        json database;
        ifstream i;

    public:
        DataBase(){
            ifstream i(DATABASE_FILE);
            i >> database;
        }
        ~DataBase(){
            i.close();
        }
        std::string read(std::string key);
        void delete_record(std::string key);
        void write(std::string key, std::string value);
};

std::string DataBase::read(string key){
    //TODO: sharding the database to prevent load the whole database each time!
    //TODO: check database access. Have some authorization mechanism.

    // ifstream i(DATABASE_FILE);
    // i >> database;
    json records = database["records"];

    for (auto it = records.begin(); it != records.end(); ++it)
    {
        if(it.key() == key) {
            DEBUG("Database: Read key" << key << " Value: "<< it.value()<< std::endl);
            return it.value();
        }
    }
    return "";
}

void DataBase::delete_record(string key){
    // ifstream i(DATABASE_FILE);
    // i >> database;
    json records = database["records"];
    records.erase(key);
}

void DataBase::write(string key, string value){
    std::string old_value = DataBase::read(key);
    if (old_value != ""){
        DataBase::delete_record(key);
    }
    // ifstream i(DATABASE_FILE);
    // i >> database;
    json records = database["records"];
    
    //TODO: can we use basic_json::update?
    records[key] = value;
    
}