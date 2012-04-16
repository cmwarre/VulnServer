
#ifndef VulnSocket_h
#define VulnSocket_h

    // stdlib includes
    #include "VulnServer.h"

    // Global Variables
    int Server, Client;
    socklen_t ClientLength;
    struct sockaddr_in ServerAddress, ClientAddress;

    // Function Prototypes
    void error(const char *);
    void startServer(void);
    void stopServer(void);
    void readServer(char *);
    void writeServer(char *);
    void closeSocket(void);
    void closeClient(int);
    int listenServer(void);

#endif