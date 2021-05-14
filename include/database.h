/*
our database query language supports two queries:
- read key
- write key value
*/

#include<iostream>
#include <iomanip>
#include<fstream>
#include "common.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

string DATABASE_FILE = "/tmp/database.json";

class IDataBase {
    public:
        virtual optional<string> read(string key) = 0;
        virtual void delete_record(string key) = 0;
        virtual void write(string key, string value) = 0;
};

class DataBase : public IDataBase {
    private:
        json database;
        ofstream database_ofstream;
    public:
        DataBase() {
            // read a JSON file into the json database object (see https://github.com/nlohmann/json)
            ifstream file;
            file.open(DATABASE_FILE);
            file >> this->database;
            file.close();

            // init the ofstream
            this->database_ofstream.open(DATABASE_FILE);
        }
        ~DataBase() {
            this->database_ofstream.close();
        }

        optional<string> read(string key);
        void delete_record(string key);
        void write(string key, string value);
};

optional<string> DataBase::read(string key) {
    //TODO: sharding the database to prevent load the whole database each time!
    //TODO: check database access. Have some authorization mechanism.
    DEBUG("Database::read key=" << key << endl);

    return database["records"][key];
}

void DataBase::delete_record(string key) {
    DEBUG("Database::delete key=" << key << endl);
    this->database["records"].erase(key);
}

void DataBase::write(string key, string value) {
    DEBUG("Database::write key=" << key << ", value=" << value << endl);

    // overwrite any existing value
    this->database["records"][key] = value;

    // write back the database to disk
    this->database_ofstream <<  setw(4) << this->database << endl;
}
