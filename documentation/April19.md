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