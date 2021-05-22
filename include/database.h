/*
our database query language supports two queries:
- read key
- write key value
*/

#include<iostream>
#include <iomanip>
#include<fstream>
#include <filesystem>
#include "common.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class IDataBase {
    public:
        virtual string read_record(string key) = 0;
        virtual void delete_record(string key) = 0;
        virtual void write_record(string key, string value) = 0;
};

class DataBase : public IDataBase {
    private:
        string filename;
        json database;
        ofstream database_ofstream;
    public:
        explicit DataBase(const string& filename) {
            this->filename = string(filename);
            // read a JSON file into the json database object (see https://github.com/nlohmann/json)
            ifstream file;
            file.open(this->filename, ifstream::in);
            file >> this->database;
            file.close();

            // init the ofstream
            this->database_ofstream.open(this->filename, ofstream::out | ofstream::trunc);

            // write back the database to disk
            this->database_ofstream.seekp(0);
            this->database_ofstream << setw(4) << this->database << endl;
        }
        ~DataBase() {
            // write back the database to disk
            this->database_ofstream.seekp(0);
            this->database_ofstream << setw(4) << this->database << endl;
            this->database_ofstream.close();
        }

        string read_record(string key) override;
        void delete_record(string key) override;
        void write_record(string key, string value) override;
};

string DataBase::read_record(string key) {
    //TODO: sharding the database to prevent load the whole database each time!
    //TODO: check database access. Have some authorization mechanism.
    DEBUG("Database::read key=" << key << endl);

    if (this->database.contains(key)) {
        return this->database[key];
    } else {
        return "";
    }
}

void DataBase::delete_record(string key) {
    DEBUG("Database::delete key=" << key << endl);
    this->database.erase(key);

    // write back the database to disk
    std::filesystem::resize_file(this->filename, 0);
    this->database_ofstream.seekp(0);
    this->database_ofstream << setw(4) << this->database << endl;
}

void DataBase::write_record(string key, string value) {
    DEBUG("Database::write key=" << key << ", value=" << value << endl);

    // overwrite any existing value
    this->database[key] = value;

    // write back the database to disk
    this->database_ofstream.seekp(0);
    this->database_ofstream << setw(4) << this->database << endl;
}
