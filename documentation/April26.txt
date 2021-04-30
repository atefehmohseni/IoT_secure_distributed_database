## Design Centralized server

### Data object:
Key, value →  update the value if the key already existed
Query language →  supports read/update (key,value) pair

### Server:
Store data →  file (txt, json, xml? preferably a file that supports a structured data format)
Read data →  return value if key exists, otherwise Null
Write data →  write the value raise an error if key does not exist (requires mutex)

### Client: 
Query data => submit the query (based on the query language) 
Write new data 
(Synchronization with other nodes) → when the server will not be centralized
Do we need a caching mechanism? (ignore for now)

### Communication between server and client:
REST Api (get,put request?)


