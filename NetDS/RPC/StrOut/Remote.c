/*************************************************************************
                    Copyright Microsoft Corp. 1992 - 2000
                        Remote Machine strout sample

  FILE      :   remote.c

  PURPOSE   :   The remote procedures that will be called from the client.

  COMMENTS  :   These procedures will be linked into the server side of 
                the application.

*************************************************************************/
#include "strout.h"                 //Generated by the MIDL compiler   
#include "common.h"                 //Common definitions for all files 

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Procedure   :   void GetRemoteEnv(unsigned long, str **)            */
/*  Desc.       :   This procedure get the environment variables from   */
/*                  the server and reuturns a pointer to an array of    */
/*                  pointer to the environment strings                  */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void GetRemoteEnv(unsigned long *nNumLines, str **psEnvironmentBlock)
{
    int nIdx = 0;       // Loop counter                                 
    TCHAR 
        *pcTemp,        // Temporary pointer to the environment block   
        *pcEnv;         // Pointer to the environment block             


    // Get pointer to environment block	
    pcEnv = (TCHAR *) GetEnvironmentStrings();

    // First count how many lines, must know how much memory to allocate
    *nNumLines  = 0;            // Initialize number of lines to 0      
    pcTemp = pcEnv;             // Set tempptr equal to envptr          
    while (*pcTemp != NULL_CHAR)
    {
        // Don't count the lines that starts with IGNORE_CHAR	        
        if(*pcTemp != IGNORE_CHAR)
        {
            (*nNumLines)++;     // Increase the number of lines     
        }

        // Increment the string pointer. Each line ends in \0, and  
        // \0\0 means end of block                                  
        pcTemp += (_tcslen(pcTemp) + 1);
    }

    // Allocate the memory needed for the line pointer 
    if(NULL == (*psEnvironmentBlock = (str *) 
        midl_user_allocate((*nNumLines) * sizeof(str))))
    {
        _tprintf(TEXT("REMOTE.C : Memory allocation error\n"));
        return;
    }

    // Iterate through all the environment strings, allocate memory,    
    // and copy them                                                    
    while (*pcEnv != NULL_CHAR)
    {
        // Don't count the lines that starts with IGNORE_CHAR
        if(*pcEnv != IGNORE_CHAR)
        {
            // Allocate the space needed for the strings 
            (*psEnvironmentBlock)[nIdx] = (str) midl_user_allocate(
                sizeof(TCHAR) * (_tcslen(pcEnv) + 1));
			
            // Copy the environment string to the allocated memory
            _tcscpy((*psEnvironmentBlock)[nIdx++], pcEnv);
        }
        
        // Increment the string pointer. Each line ends in \0, and
        // \0\0 means end of block
        pcEnv += (_tcslen(pcEnv) + 1);
    }
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Procedure    :   void ShutDown(void);                                */
/* Desc.        :   This procedure send a message to the server that it */
/*                  can	stop listening for remote procedure calls       */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void ShutDown(void)
{
    RPC_STATUS nStatus;

    // Tell the server to stop listening for remote procedure calls
    _tprintf(TEXT("Shutting down the server\n"));
    nStatus = RpcMgmtStopServerListening(NULL);
    EXIT_IF_FAIL(nStatus, "RpcMgmtStopServerListening");
}
