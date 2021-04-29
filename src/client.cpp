#include <iostream>
using namespace std;

class IClient {
    public:
        IClient(){}
        virtual string read_query(string key) = 0;
        virtual void write_query(string key, string value) = 0;
};

class Client : public IClient {
    public:
        Client(){}
        string read_query(string key);
        void write_query(string key, string value);
};

string Client::read_query(string key) {
    std::cout << "Client::read_query " << key << std::endl;
    return "test";
}

void Client::write_query(string key, string value) {
    std::cout << "Client::write_query " << key << " " << value << std::endl;
    return;
}

string prompt(string prompt) {
    string input;
    std::cout << prompt;
    getline(std::cin, input);
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
                client->read_query(key);
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
