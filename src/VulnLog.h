
#ifndef VulnLog_h
#define VulnLog_h

    // stdlib includes
    #include "VulnServer.h"

    // global variables
    FILE *serverLog;
    FILE *clientLog;

    // Function definitions
    int openServerLog(void);
    int closeServerLog(void);
    int writeServerLog(const char *);
    int createClientLog(void);
    int writeClientLog(const char *);
    int closeClientLog(void);

#endif