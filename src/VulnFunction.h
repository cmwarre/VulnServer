
#ifndef VulnFunction_h
#define VulnFunction_h

    // stdlib includes
    #include "VulnServer.h"

    // Defined functions
    int vulnHelp(int, const char **);
    int vulnExit(int, const char **);
    int vulnLevel1(int, const char **);
    int vulnLevel2(int, const char **);
    int vulnLevel3(int, const char **);
    int vulnLevel4(int, const char **);

    // Useage functions
    void useage_Level1(void);
    void useage_Level2(void);
    void useage_Level3(void);
    void useage_Level4(void);

#endif