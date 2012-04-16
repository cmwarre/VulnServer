#include "VulnConfig.h"

int setupConfig(VulnConfiguration *main_config){

	main_config->serverPort = 8000;
	main_config->maxStrLen = 4000;
	main_config->numOfCommands = 5;
	sprintf(main_config->htmlBaseDirectory, "html/");
	sprintf(main_config->serverLogBaseDirectory, "log/");
	sprintf(main_config->clientLogBaseDirectory, "log/Clients/");
	sprintf(main_config->serverLogName, "VulnServer.log");

	return(0);	
}