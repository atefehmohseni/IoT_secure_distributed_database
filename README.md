# CS263_project

## project vision

A distributed database is a database in which data is stored across different physical locations. In this project, we want to implement a simple secure distributed database system in C++. At the very core, our system should guarantee "data protection" and "reliability" among different entities. In our architecture, there is a server for managing entities but read/write operations can happen offline and only synchronization requires nodes to be online. References we might use for this projects \[[Condensation](https://condensationdb.com/white-paper/), [Data Protection in DDS](https://link.springer.com/chapter/10.1007/11425274_20)]
