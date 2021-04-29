//******************************************************************
 // 0: ERROR only, 1: INFO, 2: DEBUG
 #define LOGLEVEL 2

 #define ERROR(x) (std::cout << "[ERROR] " << x)

 #if LOGLEVEL == 2 // DEBUG
 #define DEBUG(x) (std::cout << "[DEBUG] " << x)
 #define INFO(x) (std::cout << "[INFO] " << x)

 #elif LOGLEVEL == 1 // INFO
 #define DEBUG(x) do{}while(0)
 #define INFO(x) (std::cout << "[INFO] " << x)

 #else // ERROR
 #define DEBUG(x) do{}while(0)
 #define INFO(x) do{}while(0)
 #endif
 //******************************************************************