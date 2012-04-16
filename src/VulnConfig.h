#ifndef VulnConfig_h
#define VulnConfig_h

    #include "VulnServer.h"

    #define CONFIG_FILENAME "config/VulnServer.config"

    typedef struct{
            int  serverPort;
            int  maxStrLen;
            int  numOfCommands;
            char htmlBaseDirectory[256];
            char serverLogBaseDirectory[256];
            char clientLogBaseDirectory[256];
            char serverLogName[256];
        }VulnConfiguration;

    VulnConfiguration main_configure;

    // coming in the fugure
    //int readConfig(void);

    int setupConfig(VulnConfiguration *);

#endif
