#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include "common.h"
#include "httplib.h"

using namespace std;

class IClient {
    public:
        IClient(){}
        virtual string read_query(string key) = 0;
        virtual void write_query(string key, string value) = 0;
};

class Client : public IClient {
    public:
        httplib::Client *http_client;
        Client() {
            this->http_client = new httplib::Client("http://localhost:4444");
        }
        string read_query(string key);
        void write_query(string key, string value);
};

string Client::read_query(string key) {
    DEBUG("Client::read_query key=" << key << endl);
    auto res = this->http_client->Get(("&key="+key).c_str());
    if (res != nullptr && res->status == 200) {
        return res->body;
    } else {
        return "";
    }
}

void Client::write_query(string key, string value) {
    DEBUG("Client::write_query key=" << key << "&value=" << value << endl);
    auto res = this->http_client->Get(("&key="+key+"&value="+value).c_str());
    return;
}

string prompt(string prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int main() {
    string MENU_PROMPT = "r) read query  w) write query  q) quit\nPlease enter your choice: ";
    string KEY_PROMPT = "Please enter a key to query: ";
    string VALUE_PROMPT = "Please enter a value to query: ";

    Client *client = new Client();

    string key, value;
    while(1) {
        char choice = prompt(MENU_PROMPT)[0];
        switch (choice) {
            case 'r':
                key = prompt(KEY_PROMPT);
                value = client->read_query(key);
                break;
            case 'w':
                key = prompt(KEY_PROMPT);
                value = prompt(VALUE_PROMPT);
                client->write_query(key, value);
                break;
            case 'q':
                goto END;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    }

    END:;
}
