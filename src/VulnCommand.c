#include "VulnCommand.h"

/*----------------------------------------------------------------
 |  Function: LoadCommands
 |
 |  Purpose: Loads all commands into Commands structures
 |
 |  Parameters:  None
 |
 |  Returns:  None
 |
 |  Vulnerability: 
 |
 *-------------------------------------------------------------------*/

int loadCommands(){
	
	Commands = (Command *)malloc(main_configure.numOfCommands * sizeof(Command));
    
	int i = 0;
	
	strcpy(Commands[i].String, "HELP");
	Commands[i].FuncPtr = &vulnHelp;
	
	i++;
	
	strcpy(Commands[i].String, "EXIT");
	Commands[i].FuncPtr = &vulnExit;
	
	i++;
	
	strcpy(Commands[i].String, "LEV1");
	Commands[i].FuncPtr = &vulnLevel1;
	
	i++;
	
	strcpy(Commands[i].String, "LEV2");
	Commands[i].FuncPtr = &vulnLevel2;
	
	i++;
	
	strcpy(Commands[i].String, "LEV3");
	Commands[i].FuncPtr = &vulnLevel3;
	
	i++;
	return(0);
	
}

int destroyCommands(){
	free(Commands);
	Commands = NULL;
}


/*----------------------------------------------------------------
 |  Function: compareCommand
 |
 |  Purpose: Compares command from input to list of commands
 |
 |  Parameters:  None
 |
 |  Returns:  None
 |
 |  Vulnerability: 
 |
 *-------------------------------------------------------------------*/
int compareCommand(char *input){
    
	int i;
	
	for(i = 0; i < main_configure.numOfCommands; i++){
        
		if(strncmp(input, Commands[i].String, 4) == 0)	
			goto finish;
	}
	i = 100; // it's none of them
	writeServer(" Command not recognized\n");
	
finish:	
	return(i);
    
}



/*----------------------------------------------------------------
 |  Function: clearString
 |
 |  Purpose: I'll give you 3 guesses
 |
 |  Parameters:  string
 |
 |  Returns:  None
 |
 |  Vulnerability: 
 |
 *-------------------------------------------------------------------*/
int clearString(char *buffer){
	int i;
	
	for(i = 0; i < strlen(buffer); i++){
		buffer[i] = 0x00;	
	}
    
	return(0);
}

/*----------------------------------------------------------------
 |  Function: ExecuteCommand
 |
 |  Purpose: calls Command
 |
 |  Parameters:  process id, input string
 |
 |  Returns:  None
 |
 |  Vulnerability: 
 |
 *-------------------------------------------------------------------*/
int executeCommand(int pid, int argc, const char **argv){
	
	int returnStatus;
	returnStatus = Commands[pid].FuncPtr(argc, argv);
    
	return(returnStatus);
}



/*----------------------------------------------------------------
 |  Function: CountArgs
 |
 |  Purpose: Counts arguments and splits up strings
 |
 |  Parameters:  process id, input string, argv to be used
 |
 |  Returns:  None
 |
 |  Vulnerability: 
 |
 *-------------------------------------------------------------------*/

int countArgs(char *input, char **argv){
	char *pch;
	int i = 0;
    
    
	pch = strtok (input, " -");
    
	while (pch != '\0'){
        createArg((int)strlen(pch), i, argv);
    	vulnStrcpy(argv[i], pch);
    	pch = strtok (NULL, " -");
    	i++;
	}  
    
	return(i);	
}

int createArg(int length, int argnum, char **argv){
    argv[argnum] = malloc((length + 1) * sizeof(char));
    argv[length] = '\0';
    
    return(0);
}

int destroyArgs(int argc, char **argv){
    int i;

    for(i = 0; i < argc; i++){
        free(argv[i]);
        argv[i] = NULL;
    }
    return(0);
}

/*----------------------------------------------------------------
 |  Function: spawnClientShell
 |
 |  Purpose: When client connects this is the program they should see
 |
 |  Parameters:  None
 |
 |  Returns:  None
 |
 |  Vulnerability: 
 |
 *-------------------------------------------------------------------*/
int spawnClientShell(int psid){
	
	int done = 0;
	int pid, argc;
	char *ClientInput;
	char **argv;
	
    if(createClientLog()){
        shellExit("Log failed to open");
    }
    
    if(loadCommands()){
    	shellExit("Commands failed to load");	
    }
    
    ClientInput = (char *)malloc(main_configure.maxStrLen * sizeof(char));
	
	if(ClientInput == NULL){
		shellExit("Input vector failed initilization");
	}
    
    argv = malloc(10 * sizeof(char *));
    
    if(argv == NULL){
    	shellExit("argv failed initilization");
    }
    
    writeServer("Welcome to Vulnerable Server v1.0\n");
	
	while(!done){
		
		clearString(ClientInput);
		readServer(ClientInput);
        writeClientLog(ClientInput);
		
		pid = compareCommand(ClientInput);
		
		if(pid <= main_configure.numOfCommands && pid > 0){
			argc = countArgs(ClientInput, argv);
			done = executeCommand(pid, argc, (const char **)argv);
			destroyArgs(argc, argv);
		}
	}// end loop
    
    // deallocate argv
    free(argv);
    argv = NULL;
	
	shellExit(NULL);
}

int shellExit(const char *error){
	if(error != NULL)
		writeServerLog(error);
	closeClientLog();
	closeSocket();
	_Exit(1);
}
