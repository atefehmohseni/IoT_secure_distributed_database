import argparse
import json
import requests
import time
import threading
from requests.packages.urllib3.exceptions import InsecureRequestWarning

SSL_CERT_FILE = "./ssl.debug.crt"
SSL_KEY_FILE = "./ssl.debug.key"

requests.packages.urllib3.disable_warnings(InsecureRequestWarning)

class LocalStore:
    def __init__(self):
        with open('./local_store.json', 'rb') as f:
            self.data = json.loads(f.read())
        self.ofstream = open('./local_store.json', 'wb', buffering=0)
        # self.ofstream.truncate(0)
        self.ofstream.write(json.dumps(self.data).encode('utf-8'))

    def read_record(self, key):
        return self.data[key]

    def write_record(self, key, value):
        self.data[key] = value
        self.ofstream.truncate(0)
        self.ofstream.seek(0)
        self.ofstream.write(json.dumps(self.data).encode('utf-8'))

    def delete_record(self, key):
        del self.data[key]
        self.ofstream.truncate(0)
        self.ofstream.seek(0)
        self.ofstream.write(json.dumps(self.data).encode('utf-8'))

class Client:
    def __init__(self, ssl=True):
        self.http_session = requests.Session()
        self.http_session.auth = ('username', 'password')
        # self.http_session.cert = SSL_CERT_FILE
        self.http_session.verify = False

        self.action_queue = []
        self.local_store = LocalStore()

        if ssl:
            self.base_url = 'https://localhost:4444'
        else:
            self.base_url = 'http://localhost:4444'

        # start secondary thread
        threading.Thread(target=Client.local_store_callable, args=(self, )).start()

    def read_query(self, key):
        r = self.http_session.get(f'{self.base_url}/get', params={'key': key})

        if r.status_code == 200:
            return r.text

    def write_query(self, key, value):
        self.action_queue.append(('put', key))

        # write value to local value store
        self.local_store.write_record(key, value)

    def delete_query(self, key):
        self.action_queue.append(('del', key))

    @staticmethod
    def local_store_callable(client):
        while True:
            # print('running', client.action_queue)
            # process action queue
            while len(client.action_queue) > 0:
                status = 500
                type, key = client.action_queue[0]

                if type == 'del':
                    r = client.http_session.get(f'{client.base_url}/delete', params={'key': key})
                    status = r.status_code
                elif type == 'put':
                    # read value from local store
                    value = client.local_store.read_record(key)
                    r = client.http_session.get(f'{client.base_url}/put', params={'key': key, 'value': value})
                    status = r.status_code
                    pass

                # check status
                if status == 200:
                    client.action_queue.pop(0)
                    if type == 'put':
                        # delete key from local data store
                        client.local_store.delete_record(key)
                else:
                    break

            time.sleep(5)

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
