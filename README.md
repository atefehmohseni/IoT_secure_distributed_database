# CS263_project
These instructions have been tested on an Ubuntu 18.04 machine. 

## Requirements
`libopenssl` and `libpthread` must be installed on the target machine. The Python implementation of the client (`resources/client.py`) has been tested on Python 3.6 and uses the `requests` library for network communication (`pip install requests`). `pypy` must be installed in the target system in order to collect the profiling data.

Additionally, the `.json.default` files in the `resources` directory must be copied as `.json` files in the same directory.

```bash
# install libssl-dev libpthread-dev python3 pypy3
sudo add-apt-repository ppa:pypy/ppa
sudo apt update
sudo apt-get install -y libssl-dev libpthread-stubs0-dev python3 python3-pip pypy3

# create the python/pypy virtualenvs
python3 -m pip install virtualenv
virtualenv -p $(which pypy3) ~/venv_pypy3
virtualenv -p $(which python3) ~/venv_python3

# install the python requests module (pypy3)
source ~/venv_pypy3/bin/activate
pypy3 -m ensurepip
python3 -m pip install requests

# install the python requests module (python3)
source ~/venv_python3/bin/activate
pypy3 -m pip install requests

# copy the .json.default files
for f in resources/*.json.default; do cp $f ${f%%.default}; done
```

Finally, to parse the profiling files and generate the profiling charts, the `matplotlib` and `numpy` Python modules are required.

## Build
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Execute
You should separtely execute the master server, edge-server, and client.

### Run the Master Server
```bash
$ cd build/
$ ./master_server
```
### Run an Edge Server
```bash
$ # within the build directory 
$ ./server
```

### Run a Client
```bash
$ # within the build directory 
$ ./client
```

### Test cases
The test queries in [test directory](https://github.com/atefehmohseni/IoT_secure_distributed_database/tree/main/test) can be used to run write/read/delete queries from a client to an edge server (usage: `cat <test_file> | ./client`).

## Profiling
To collect the profiling information run the following script:
```bash
$ cd resources
$ ./run_profiling.sh
```
To parse the profiling information:
```bash
# within the resources directory 
 python3 parse_profiling.py
```

## Project Vision

The high-level goal of this project is to research the topic of data persistence in a distributed programming system, with a focus on data protection and reliability.

A distributed database is a database in which data is stored across different physical locations. In this project, we want to implement a simple but secure distributed database system in C++. Our architecture relies on a centralized server for managing nodes, but read/write operations can happen offline, and only data synchronization requires the nodes to be online. At the very core, our system should guarantee data protection and reliability among different nodes. 

References we might use for this projects are: \[[Condensation](https://condensationdb.com/white-paper/), [Data Protection in DDS](https://link.springer.com/chapter/10.1007/11425274_20)].
