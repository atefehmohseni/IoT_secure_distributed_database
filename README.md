# CS263_project

## Project Vision

The high-level goal of this project is to research the topic of data persistence in a distributed programming system, with a focus on data protection and reliability.

A distributed database is a database in which data is stored across different physical locations. In this project, we want to implement a simple but secure distributed database system in C++. Our architecture relies on a centralized server for managing nodes, but read/write operations can happen offline, and only data synchronization requires the nodes to be online. At the very core, our system should guarantee data protection and reliability among different nodes. 

References we might use for this projects are: \[[Condensation](https://condensationdb.com/white-paper/), [Data Protection in DDS](https://link.springer.com/chapter/10.1007/11425274_20)].
