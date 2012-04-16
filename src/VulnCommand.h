
#ifndef VulnCommand_h
#define VulnCommand_h

    // stdlib includes
    #include "VulnServer.h"

    // type definitions
    typedef struct{ 
        char String[5];
        int (*FuncPtr)(int, const char **);
    }Command;

    // Global Variables
    Command *Commands;

    // function prototypes
    int loadCommands(void);
    int destroyCommands(void);
    int compareCommand(char *);
    int executeCommand(int, int, const char **);
    int createArg(int, int, char **);
    int destroyArgs(int, char **);
    int countArgs(char *, char **);
    int clearString(char *);
    int spawnClientShell(int);

#endif