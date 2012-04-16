
#include "VulnUtility.h"

/*----------------------------------------------------------------
 |  Function: vulnFileSize
 |
 |  Purpose: Finds the size in bytes of a given file
 |
 |  Parameters:  the file pointer
 |
 |  Returns:  size in bytes of file
 |
 *-------------------------------------------------------------------*/
long vulnFileSize(FILE **f){
	
	long size;
	
	// obtain file size:
	fseek (*f , 0 , SEEK_END);
	size = ftell (*f);
	rewind (*f);	
	
	return(size);
}
/*----------------------------------------------------------------
 |  Function: vuln_strcpy
 |
 |  Purpose: Custom vulnserver string copy.  I was getting segfaults
 |           with c lib strcpy
 |
 |  Parameters:  two strings to be copied, destination and source
 |
 |  Returns:  success/fail int
 |
 *-------------------------------------------------------------------*/
int vulnStrcpy(char *dest, char *src){
    
    int src_size;
    int i;
    
    for(i = 0; i < src_size; i++){
        dest[i] = src[i];
    }
    
    return(i);
}
/*----------------------------------------------------------------
 |  Function: getTime
 |
 |  Purpose: to get the current time in string format
 |
 |  Parameters:  a string
 |
 |  Returns:  the string with what time it is and sucess/fail int
 |
 *-------------------------------------------------------------------*/
int getTime(char *timeStr){
    time_t currentTime;
    
    // get current time and write to buffer
    time(&currentTime);
    strcpy(timeStr, ctime(&currentTime));
    
    return(0);
}

/*----------------------------------------------------------------
 |  Function: getIp
 |
 |  Purpose: get the ip address that is currently connecting
 |
 |  Parameters:  None
 |
 |  Returns:  string with ip address and success/fail int
 |
 *-------------------------------------------------------------------*/
int getIp(char *ip_str){
    return(0);
}