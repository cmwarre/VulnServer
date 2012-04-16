
#include "VulnLog.h"
/*----------------------------------------------------------------
 |  Function: openServerLog
 |
 |  Purpose: Runs when server is started.  Opens the log for the
 |           entire server and keeps track of connections and failures
 |
 |  Parameters:  None
 |
 |  Returns:  fail/success int
 |
 *-------------------------------------------------------------------*/
int openServerLog(){
    char logName[256];
    char logTime[256];
    
    getTime(logTime);
    
    sprintf(logName, "%s%s", main_configure.serverLogBaseDirectory, main_configure.serverLogName);
    
    serverLog = fopen(logName, "a+");
    
    if(serverLog == NULL){
        fprintf(stderr, "Server log wouldn't open\n");
        return(1);
    }
    
    fprintf(serverLog, "Server started on %s\n", logTime);
    
    return(0);
}
/*----------------------------------------------------------------
 |  Function: writeServerLog
 |
 |  Purpose: write the given message to the log and prints time
 |
 |  Parameters:  the message
 |
 |  Returns:  success/fail int
 |
 *-------------------------------------------------------------------*/
int writeServerLog(const char *message){
    char logTime[64];
    char *cleanMessage;
    
    if(serverLog == NULL){
    	serverLog = fopen("writeServerLogerror.txt", "w+");
    	fclose(serverLog);	
    }
    
    cleanMessage = (char *)malloc(strlen(message) * sizeof(char));
    
    sscanf(message, "%s", cleanMessage);
    
    getTime(logTime);
    fprintf(serverLog, "%s\t%s\n", logTime, cleanMessage);
    
    free(cleanMessage);
    return(0);
}
/*----------------------------------------------------------------
 |  Function: closeServerLog
 |
 |  Purpose: closes the server log when server is stopped
 |
 |  Parameters:  None
 |
 |  Returns:  success/fail int
 |
 *-------------------------------------------------------------------*/
int closeServerLog(){
    char logTime[256];
    
    getTime(logTime);
    
    fprintf(serverLog, "Server stoped on %s\n", logTime);
    
    fclose(serverLog);
    clientLog = NULL;
    return(0);
}
/*----------------------------------------------------------------
 |  Function: createClientLog
 |
 |  Purpose: when client connects this logs all of their activity
 |
 |  Parameters:  None
 |
 |  Returns:  success/fail int
 |
 *-------------------------------------------------------------------*/
int createClientLog(){
    
    char logTime[256];
    char logName[512];
    char ip[256];
    
    getTime(logTime);
    getIp(ip);
    
    // in the future it will log by their ip address
    sprintf(logName, "%s127.0.0.1",main_configure.clientLogBaseDirectory, logTime);
    
    clientLog = fopen(logName, "w+");
    if(clientLog == NULL){
        return(1);
    }
    
    fprintf(clientLog, "Connected at %s\n", logTime);
    
    return(0);
}
/*----------------------------------------------------------------
 |  Function: writeClientLog
 |
 |  Purpose: Writes the clients log with the given message and the
 |           time it was written
 |
 |  Parameters:  the message
 |
 |  Returns:  success/fail int
 |
 *-------------------------------------------------------------------*/
int writeClientLog(const char *message){
    char logTime[64];
    char *cleanMessage;
    
    cleanMessage = (char *)malloc(strlen(message) * sizeof(char));
    
    // cleans out newline in message
    sscanf(message, "%s", cleanMessage);
    
    getTime(logTime);
    fprintf(clientLog, "%s  %s", cleanMessage, logTime);
    
    free(cleanMessage);
    return(0);
}
/*----------------------------------------------------------------
 |  Function: closeClientLog
 |
 |  Purpose: closes the clients log before they dissconnect
 |
 |  Parameters:  None
 |
 |  Returns:  success/fail int
 |
 *-------------------------------------------------------------------*/
int closeClientLog(){
    char logTime[256];
    
    getTime(logTime);
    
    fprintf(clientLog, "Client quit on %s\n", logTime);
    
    fclose(clientLog);
    clientLog = NULL;
    return(0);
}
