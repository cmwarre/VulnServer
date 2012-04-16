
#ifndef VulnUtility_h
#define VulnUtility_h

    // stdlib includes
    #include "VulnServer.h"

    long vulnFileSize(FILE **);
    int vuln_strcpy(char *, char *);
    int getTime(char *);
    int getIp(char *);

#endif