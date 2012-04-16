
#include "VulnSocket.h"

/*----------------------------------------------------------------
 |  Function: startServer
 |
 |  Purpose: start server and begin listening to socket
 |
 |  Parameters:  None
 |
 |  Returns:  
 |
 *-------------------------------------------------------------------*/
void startServer(){
    
	int sockBind;
    
    // open socket
    Server = socket(AF_INET, SOCK_STREAM, 0);	
	
	if(Server < 0)
		error("ERROR opening socket");
    
	// sets all values in buffer to 0
	bzero((char *) &ServerAddress, sizeof(ServerAddress)); 
    
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.s_addr = INADDR_ANY;
    ServerAddress.sin_port = htons(main_configure.serverPort);
    
    sockBind = bind(Server, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress));
    
    if (sockBind < 0){
    	error("ERROR on binding");
        exit(0);
    }
}

/*----------------------------------------------------------------
 |  Function: stopServer
 |
 |  Purpose: closes connections and quits listening
 |
 |  Parameters:  None
 |
 |  Returns:  
 |
 *-------------------------------------------------------------------*/
void stopServer(){
    close(Server);
}

/*----------------------------------------------------------------
 |  Function: stopServer
 |
 |  Purpose: closes connections and quits listening
 |
 |  Parameters:  None
 |
 |  Returns:  1 when Client connects
 |
 *-------------------------------------------------------------------*/
int listenServer(){
	
	listen(Server,5);
    
	ClientLength = sizeof(ClientAddress);
	Client = accept(Server, (struct sockaddr *) &ClientAddress, &ClientLength);
	
	
	
	if (Client < 0)
  		error("ERROR on accept");
    
  	return(Client);
    
}

/*----------------------------------------------------------------
 |  Function: readServer
 |
 |  Purpose: get input from server
 |
 |  Parameters:  a string
 |
 |  Returns:  the buffer string with input
 |
 *-------------------------------------------------------------------*/
void readServer(char *buffer){
    
    int n;
    
    writeServer("> ");
    
    bzero(buffer, main_configure.maxStrLen);
    n = (int)read(Client, buffer, main_configure.maxStrLen);
    
    if (n < 0) error("ERROR reading from socket");	
	
}



/*----------------------------------------------------------------
 |  Function: writeServer
 |
 |  Purpose: write message to client
 |
 |  Parameters:  message string
 |
 |  Returns:  None
 |
 *-------------------------------------------------------------------*/
void writeServer(char *message){
	int n = 0;
	
	long length = strlen(message);
	
	if(length > 1)
		n = (int)write(Client, message, length);
    
	if (n < 0) error("ERROR writing to socket");
}



void closeSocket(){
    close(Client);
}

/*----------------------------------------------------------------
 |  Function: error
 |
 |  Purpose: Writes an error to stdout and quits server
 |
 |  Parameters:  None
 |
 |  Returns:  None
 |
 *-------------------------------------------------------------------*/
void error(const char *msg)
{
    perror(msg);
    printf("Client disconnected\n");
    exit(1);
}