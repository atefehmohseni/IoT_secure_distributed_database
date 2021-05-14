#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include "common.h"
#include "httplib.h"

using namespace std;

class IClient {
    public:
        IClient(){}
        virtual std::string read_query(std::string key) = 0;
        virtual void write_query(std::string key, std::string value) = 0;
};

class Client : public IClient {
    public:
        httplib::Client *http_client;
        Client() {
            this->http_client = new httplib::Client("http://localhost:4444");
        }
        std::string read_query(std::string key);
        void write_query(std::string key, std::string value);
};

std::string Client::read_query(std::string key) {
    DEBUG("Client::read_query key=" << key << std::endl);
    auto res = this->http_client->Get(("&key="+key).c_str());
    if (res != nullptr && res->status == 200) {
        return res->body;
    } else {
        return "";
    }
}

void Client::write_query(std::string key, std::string value) {
    DEBUG("Client::write_query key=" << key << "&value=" << value << std::endl);
    auto res = this->http_client->Get(("&key="+key+"&value="+value).c_str());
    return;
}

std::string prompt(std::string prompt) {
    std::string input;
    std::cout << prompt;
    getline(std::cin, input);
    return input;
}

int main() {
    std::string MENU_PROMPT = "r) read query  w) write query  q) quit\nPlease enter your choice: ";
    std::string KEY_PROMPT = "Please enter a key to query: ";
    std::string VALUE_PROMPT = "Please enter a value to query: ";

    Client *client = new Client();

    std::string key, value;
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
                std::cout << "Invalid choice" << std::endl;
        }
    }

    END:;
}
