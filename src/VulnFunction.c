#include "VulnFunction.h"

/*----------------------------------------------------------------
 |  Function: Help
 |
 |  Purpose: Displays all current commands
 |
 |  Parameters:  None
 |
 |  Returns:  None
 |
 |  Vulnerability: 
 |
 *-------------------------------------------------------------------*/
int vulnHelp(int argc, const char **argv){
    
	int i;
	char buffer[10];
	
	writeServer(" Installed commands are: ");
	
	for(i = 0; i < main_configure.numOfCommands; i++){
		sprintf(buffer, "%s\n", Commands[i].String);
		writeClientLog(buffer);
		writeServer(buffer);
    }
    
	return(0);
}
/*----------------------------------------------------------------
 |  Function: Exit
 |
 |  Purpose: Quit
 |
 |  Parameters:  None
 |
 |  Returns:  None
 |
 |  Vulnerability: 
 |
 *-------------------------------------------------------------------*/
int vulnExit(int argc, const char **argv){
	writeServer("  Bye!");
	closeSocket();
	return(1);	
}
/*----------------------------------------------------------------
 |  Function: Level1
 |
 |  Purpose: Does what I tell it to do
 |
 |  Parameters:  None
 |
 |  Returns:  None
 |
 |  Vulnerability: 
 |
 *-------------------------------------------------------------------*/
int vulnLevel1(int argc, const char **argv){
    
	char username[256];
	
	if(argc != 2){
		useage_Level1();
		return(0);
	}
	
	strcpy(username, argv[1]);
    
    // Username is always invalid... muahaha
	sprintf(username, "  Username: %s does not exist\n", argv[1]);
	
	writeServer(username);
	
	writeClientLog(argv[0]);
    writeClientLog(argv[1]);
	
	return(0);
}

void useage_Level1(){
	char UseageString[] = 
	"  Useage: LEV1 <username>\n"
	"  Logs you in as given user\n";
	
	writeServer(UseageString);
}

/*----------------------------------------------------------------
 |  Function: Level2
 |
 |  Purpose: Get password to admin server
 |
 |  Parameters:  password string
 |
 |  Returns:  None
 |
 |  Vulnerability: 
 |
 *-------------------------------------------------------------------*/
int vulnLevel2(int argc, const char **argv){
	
	int i;
	int Authenticated = 1; // boolean var
	char pass[] = "i8&sFjlon";
	
	if(argc != 2){
		useage_Level2();
		return(0);
	}
	
	for(i = 0; i < 5; i++){
		Authenticated = Authenticated && (argv[1][i] == pass[i]);
	}
	
	if(Authenticated)
		writeServer("  User:Admin Logged In!\n");
	else
		writeServer("  Sorry, Try Again\n");
	
	writeClientLog(argv[0]);
    writeClientLog(argv[1]);
	
	return(0);
}

void useage_Level2(){
	char UseageString[] = 
	"  Useage: LEV2 <password>\n"
	"  This program will authenticate you as\n"
	"  Admin if you enter correct password\n" ;
    
	writeServer(UseageString);
}

/*----------------------------------------------------------------
 |  Function: Level3
 |
 |  Purpose: Login as unprivlidged user
 |
 |  Parameters:  None
 |
 |  Returns:  None
 |
 |  Vulnerability: Dangling Pointer in the future...
 |
 *-------------------------------------------------------------------*/
int vulnLevel3(int argc, const char **argv){
    char *message;
    
	if(argc != 2){
		useage_Level3();
		return(0);
	}		
    
    writeClientLog(argv[0]);
    writeClientLog(argv[1]);
    
    message = (char *)malloc(strlen(argv[1]) * sizeof(char));
    
    sprintf(message, argv[1]);
    writeServer(message);
    
    free(message);
    message = NULL;
	return(0);	
}

void useage_Level3(){
	char UseageString[] = 
	"  Useage: LEV3 <string>             \n"
	"  Echoes the string given to it back\n";
    
	writeServer(UseageString);
}












