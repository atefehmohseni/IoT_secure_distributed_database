#include <iostream>
#include "common.h"
#include "httplib.h"

using namespace std;

class IClient {
    public:
        IClient()= default;
        virtual string read_query(string key) = 0;
        virtual void write_query(string key, string value) = 0;
        virtual void delete_query(string key) = 0;
};

class Client : public IClient {
    public:
        httplib::Client *http_client;
        Client() {
            #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
            this->http_client = new httplib::Client("https://localhost:4444");
            // Use CA bundle
            this->http_client->set_ca_cert_path(SSL_CERT_FILE);
            // Disable cert verification
            this->http_client->enable_server_certificate_verification(false);
            #else
            this->http_client = new httplib::Client("http://localhost:4444");
            #endif
        }
        string read_query(string key) override;
        void write_query(string key, string value) override;
        void delete_query(string key) override;
};

string Client::read_query(string key) {
    DEBUG("Client::read_query key=" << key << endl);
    auto res = this->http_client->Get(("/get&key="+key).c_str());
    if (res != nullptr && res->status == 200) {
        return res->body;
    } else {
        return "";
    }
}

void Client::write_query(string key, string value) {
    DEBUG("Client::write_query key=" << key << "&value=" << value << endl);
    auto res = this->http_client->Get(("/put&key="+key+"&value="+value).c_str());
}

void Client::delete_query(string key) {
    DEBUG("Client::delete_query key=" << key << endl);
    auto res = this->http_client->Get(("/delete&key="+key).c_str());
}

string prompt(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int main() {
    string MENU_PROMPT = "r) read query  w) write query  d) delete query  q) quit\nPlease enter your choice: ";
    string KEY_PROMPT = "Please enter a key to query: ";
    string VALUE_PROMPT = "Please enter a value to query: ";

    auto *client = new Client();

    string key, value;
    while(true) {
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
            case 'd':
                key = prompt(KEY_PROMPT);
                client->delete_query(key);
                break;
            case 'q':
                goto END;
            default:
                cout << "Invalid choice" << endl;
        }
    }

    END:;
}
