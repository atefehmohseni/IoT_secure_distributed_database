# CS263_project

## Project Vision

The high-level goal of this project is to research the topic of data persistence in a distributed programming system, with a focus on data protection and reliability.

A distributed database is a database in which data is stored across different physical locations. In this project, we want to implement a simple but secure distributed database system in C++. Our architecture relies on a centralized server for managing nodes, but read/write operations can happen offline, and only data synchronization requires the nodes to be online. At the very core, our system should guarantee data protection and reliability among different nodes. 

References we might use for this projects are: \[[Condensation](https://condensationdb.com/white-paper/), [Data Protection in DDS](https://link.springer.com/chapter/10.1007/11425274_20)].


## Log of weekly progress:

### Week of April 19th
Reviewing related literature, added to README


## Related Literature
* [Condensation: a distributed data system with conflict-free synchronization
and end-to-end security.](https://condensationdb.com/white-paper/)
  * Goal: proposing a hybrid database structure, with mutable documents stored (and merged) locally and immutable objects transferred through one or more (distributed) intermediate servers.
  * The system provides data certification (with user signature), versioning (with transaction history), and conflict free merge (with CRDTs -- Conflict-free Replicated Data Types).
  * Centralized server data flow (one centralized server is used to synchronize the data): 
    1. The data is decrypted in the server 
    2. The data is manipulated by the server 
    3. The data is stored in the server. 
    
    This potentially creates a single point of failure and exposes the users to security and privacy issues like a data breach.
    
  * Condensation DB data flow: 
    1. a mutable object on node A is signed and encrypted for node B 
    2. the object is stored in an intermediate server and remains encrypted
    3. node A sends a message to node B 
    4. node B pulls the new object 
    5. node B decrypts and processes the object, then encrypts its version of the object and stores it in an intermediate server (the fact that objects are immutable naturally leads to a versioning abstraction)
