import argparse
import requests
from requests.packages.urllib3.exceptions import InsecureRequestWarning

SSL_CERT_FILE = "./ssl.debug.crt"
SSL_KEY_FILE = "./ssl.debug.key"

requests.packages.urllib3.disable_warnings(InsecureRequestWarning)

class Client:
    def __init__(self, ssl=True):
        self.http_session = requests.Session()
        # self.http_session.cert = SSL_CERT_FILE
        self.http_session.verify = False

        if ssl:
            self.base_url = 'https://localhost:4444'
        else:
            self.base_url = 'http://localhost:4444'

    def read_query(self, key):
        r = self.http_session.get(f'{self.base_url}/get', params={'key': key})

        if r.status_code == 200:
            return r.text

    def write_query(self, key, value):
        r = self.http_session.get(f'{self.base_url}/put', params={'key': key, 'value': value})

        if r.status_code == 200:
            return r.text

    def delete_query(self, key):
        r = self.http_session.get(f'{self.base_url}/delete', params={'key': key})

        if r.status_code == 200:
            return r.text

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--no-ssl', action='store_true', default=False,
                        help='Disable SSL')
    args = parser.parse_args()

    client = Client(ssl=(not args.no_ssl))

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
