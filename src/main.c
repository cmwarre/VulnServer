/*=============================================================================
 |      Program:  VulnServer
 |
 |       Author:  cmwarre
 |     Language:  C
 |   To Compile:  makefile...
 |
 |      Started:  9/23/11
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  A server to teach you the basics of computer security
 |                Don't use this for any real purpose please.  You'll 
 |                regret it.
 | 
 |
 |   Required Features Not Included:  Finish Functions in Command file.
 |                                    Multiple threads
 |                                    Log
 |                                    
 |		
 |		
 |
 |   Known Bugs:  Lots :)
 |
 +===========================================================================*/

#include "main.h"

int main(int argc, const char **argv){
    
    int i;
    BOOL start_flag, stop_flag;
    
    if(argc < 2){
        useage();
        return(0);
    }
    
    for(i = 1; i < argc; i++){
        if(argv[i][1] == '-')
            handleOptions(argv[i]);
        else if(strncmp(argv[i], "start", 5) == 0)
            start_flag = 1;
        else if (strncmp(argv[i], "stop", 4) == 0)
            stop_flag = 1;
        else{
            printf("Invalid argument\n");
            useage();
            return(0);
        }
    }
    
    if(start_flag)
        start();
    else if(stop_flag)
        stop();
    // if user just used options    
    else
        return(0);
    
	return(0);	
}

/*----------------------------------------------------------------
 |  Function: handleOptions
 |
 |  Purpose: when options are given at command line this handles them
 |
 |  Parameters:  None
 |
 |  Returns:  sucess/fail int
 |
 *-------------------------------------------------------------------*/   
int handleOptions(const char *options){
	
	printf("handling options\n");
	
	return(0);
}

/*----------------------------------------------------------------
 |  Function: start
 |
 |  Purpose: starts up the server
 |
 |  Parameters:  None
 |
 |  Returns:  sucess/fail int
 |
 *-------------------------------------------------------------------*/
int start(){
    int pid, client_id;
    
    printf("Starting server…\n");
    setupConfig(&main_configure);
    
	if(openServerLog()){
        printf("Failed to launch VulnServer\n");
        return(1);
    }
    else
        startServer();
    
	printf("Server up and running\n");
	
	while(1){
        client_id = listenServer();
        pid = fork();
        
        if(pid > 0){
            writeServerLog("User connected\n");
            printf("User connected\n");
        }
        else if(pid == 0)
            spawnClientShell(pid);
        else
            error("Process error");
	}
}
/*----------------------------------------------------------------
 |  Function: stopServer
 |
 |  Purpose: stops the server
 |
 |  Parameters:  None
 |
 |  Returns:  success/fail int
 |
 *-------------------------------------------------------------------*/
int stop(){
	printf("Stopping server");
	destroyCommands();
    closeServerLog();
	stopServer();
    return(0);
}
/*----------------------------------------------------------------
 |  Function: useage
 |
 |  Purpose:  displays the useage of the program
 |
 |  Parameters:  None
 |
 |  Returns:  success/fail int
 |
 *-------------------------------------------------------------------*/
int useage(){
    
    char use[] = " Useage:  ./Vulnserver <action>\n"
    			 " Example: ./VulnServer start  \n";
    puts(use);
    return(0);
}





