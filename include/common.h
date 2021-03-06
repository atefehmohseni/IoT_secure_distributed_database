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

#define CPPHTTPLIB_OPENSSL_SUPPORT
#define SSL_CERT_FILE "../resources/ssl.debug.crt"
#define SSL_KEY_FILE "../resources/ssl.debug.key"

#define DATABASE_FILE "../resources/database.json"
#define CREDENTIALS_FILE "../resources/credentials.json"
#define SALTS_FILE "../resources/salts.json"
#define DATABASE_FILE_CLOUD "../resources/cloud_database.json"

#define LOCAL_STORE_FILE "../resources/local_store.json"

//set backup frequency to enable edge server backup to the cloud server every x write operation
#define BACKUP_FREQUENCY 1000