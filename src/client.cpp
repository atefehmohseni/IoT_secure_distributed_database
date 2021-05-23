#include <iostream>
#include "common.h"
#include "database.h"
#include "httplib.h"
#include <queue>
#include <thread>

using namespace std;

class IClient {
    public:
        IClient()= default;
        virtual void start() = 0;
        virtual string read_query(string key) = 0;
        virtual void write_query(string key, string value) = 0;
        virtual void delete_query(string key) = 0;
};

class Client : public IClient {
    public:
        #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
        httplib::SSLClient *http_client;
        #else
        httplib::Client *http_client;
        #endif

        DataBase *local_store;
        queue< pair<string,string> > action_queue;  // pair<action_type, key>

        thread local_store_thread;

        Client() {
            #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
            this->http_client = new httplib::SSLClient("localhost", 4444);
            // Use CA bundle
            this->http_client->set_ca_cert_path(SSL_CERT_FILE);
            // Disable cert verification
            this->http_client->enable_server_certificate_verification(false);
            #else
            this->http_client = new httplib::Client("localhost", 4444);
            #endif

            // Basic Authentication
            this->http_client->set_basic_auth("username", "password");

            this->local_store = new DataBase(LOCAL_STORE_FILE);
        }
        void start() override;
        string read_query(string key) override;
        void write_query(string key, string value) override;
        void delete_query(string key) override;

        static void local_store_callable(Client *client);
};

void Client::start() {
    this->local_store_thread = thread(&Client::local_store_callable, this);
}

string Client::read_query(string key) {
    DEBUG("Client::read_query key=" << key << endl);
    auto res = this->http_client->Get(("/get?key="+key).c_str());
    if (res != nullptr && res->status == 200) {
        return res->body;
    } else {
        return "";
    }
}

void Client::write_query(string key, string value) {
    DEBUG("Client::write_query key=" << key << "&value=" << value << endl);
    this->local_store->write_record(key, value);
    this->action_queue.push(make_pair("put", key));
}

void Client::delete_query(string key) {
    DEBUG("Client::delete_query key=" << key << endl);
    this->action_queue.push(make_pair("del", key));
}

void Client::local_store_callable (Client *client) {
    while (true) {
        // process action queue
        while (!client->action_queue.empty()) {
            int status = 500;
            auto[type, key] = client->action_queue.front();

            if (type == "del") {
                auto res = client->http_client->Get(("/delete?key="+key).c_str());
                status = res->status;
            } else if (type == "put") {
                string value = client->local_store->read_record(key);
                auto res = client->http_client->Get(("/put?key=" + key + "&value=" + value).c_str());
                status = res->status;
            }

            if (status == 200) {
                client->action_queue.pop();
                if (type == "put") {
                    client->local_store->delete_record(key);
                }
            } else {
                break;
            }
        }
        sleep(5);
    }
}

string prompt(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int main() {
    string MENU_PROMPT = "r) read query  w) write query  d) delete query  q) quit\nPlease enter your choice: ";
    string KEY_PROMPT = "Please enter a key: ";
    string VALUE_PROMPT = "Please enter a value: ";

    auto *client = new Client();
    client->start();

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
