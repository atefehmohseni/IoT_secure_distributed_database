import requests


class Client:
    def __init__(self):
        self.http_session = requests.Session()
        self.base_url = 'http://localhost:4444'

    def read_query(self, key):
        r = requests.get(f'{self.base_url}/get', params={'key': key})

        if r.status_code == 200:
            return r.text

    def write_query(self, key, value):
        r = requests.get(f'{self.base_url}/put', params={'key': key, 'value': value})

        if r.status_code == 200:
            return r.text

    def delete_query(self, key):
        r = requests.get(f'{self.base_url}/delete', params={'key': key})

        if r.status_code == 200:
            return r.text

if __name__ == '__main__':
    client = Client()

    while True:
        print('r) read query  w) write query  d) delete query  q) quit\nPlease enter your choice: ')
        choice = input()[0]

        if choice == 'r':
            print('Please enter a key to query: ')
            key = input()
            client.read_query(key)
        elif choice == 'w':
            print('Please enter a key to write: ')
            key = input()
            print('Please enter a value to write: ')
            value = input()
            client.write_query(key, value)
        elif choice == 'd':
            print('Please enter a key to delete: ')
            key = input()
            client.delete_query(key)
        elif choice == 'q':
            exit(0)
