# CS263_project
The instruction is for execuritng the program on an Ubuntu 18.04 machine. 

## Prerequisites

### To Execute the Program
```bash
$ sudo apt -get install g++
$ sudo apt-get install python3.6
```

### To Get Profiling Information
- PyPy
- CPython

## Build
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Execute
You should separtely execute the master server, edge-server and a client.

### Run the Master Server
```bash
$ cd build/
$ ./master_server
```
### Run an Edge Server
```bash
$ cd build/
$ ./server
```

### Run a Client
```bash
$ cd build/
$ ./client
```

## Profiling

### Test cases
Check out the test queries in [test directory](https://github.com/atefehmohseni/IoT_secure_distributed_database/tree/main/test) that basically runs write/read/delete queries from a client to an edge server.

### Get the Profiling Result
To get the profiling information of test cases run the following script:
```bash
$ cd resources
$ ./run_profiling.sh
```
In order to parse the profiling information:
```bash
# within the resources directory 
 python3 parse_profiling.py
```

## Project Vision

The high-level goal of this project is to research the topic of data persistence in a distributed programming system, with a focus on data protection and reliability.

A distributed database is a database in which data is stored across different physical locations. In this project, we want to implement a simple but secure distributed database system in C++. Our architecture relies on a centralized server for managing nodes, but read/write operations can happen offline, and only data synchronization requires the nodes to be online. At the very core, our system should guarantee data protection and reliability among different nodes. 

References we might use for this projects are: \[[Condensation](https://condensationdb.com/white-paper/), [Data Protection in DDS](https://link.springer.com/chapter/10.1007/11425274_20)].
