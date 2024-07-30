==============================================
Networking, Protocols, & Data Formats - FTPJr
==============================================
Last Updated: OCT. 18, 2001              


SUMMARY
========
FtpJr sample demonstrates FTP WinInet APIs. FtpJr mimics FTP client, which 
comes with Windows 95 or with Windows NT, but it is entirely written with 
WinInet APIs.


USAGE
======
This sample includes Microsoft Visual Studio .NET project files. To create ftpjr.exe,
load FTPJr.sln and build the project.

With Visual Studio 6.0, you must need to create a blank console application and add FTPJr.cpp to the project.
You must also add wininet.lib to the linker's list of libraries. 

To run the sample:

1.  If you have a direct connection to the Internet, type: 
    c:> ftpjr   
2.  If you have a proxy connection to the Internet, type: 
    c:> ftpjr FtpProxy
    
Upon starting FtpJr, it prompts user to enter FTP command. It resembles to the 
standard command like based FTP server.

Once you see the FTP Jr> prompt, you can type any command supported by the sample.
To get the list of the supported commands type "help".

For example, to get the file from the remote FTP server following sequence of
commands needed:
    open -> to open a session to the remote server
    ls   -> to list the contains of the server
    type -> to set the proper file type (BIN or ASCII)
    get  -> to get the file
    
If the command requires extra parameters (such as file names, for example), it 
will prompt the user for it.

Error reporting:
All errors are reported in form of the numeric error codes and
extended information reported by the server (if available). For example, if you try 
to change directory which does not exist following will take place:

FTP Jr>cd MyBogusDir
FtpSetCurrentDirectory error 12003
 550 MyBogusDir: The system cannot find the file specified.
 
In this sample server reported an extended information. FtpSetCurrentDirectory in its
turn failed with the error 12003. This error could be located in the WinInet.h file and 
it is:

#define ERROR_INTERNET_EXTENDED_ERROR           (INTERNET_ERROR_BASE + 3)

It is possible that some WinInet fails without any extended information supplied by the
server, for example if you use wrong password:

FTP Jr>open ftp.microsoft.com
Enter user, pass: WrongUser BogusPass
InternetConnect error 12014

Session closed.

Error 12014 (from WinInet.h) is:
#define ERROR_INTERNET_INCORRECT_PASSWORD       (INTERNET_ERROR_BASE + 14)

Notes:
-------
CERN type proxy does not work with FTP WinInet APIs, because it returns 
information in HTML format. You will need to use TIS style FTP 	proxy with FTP
WinInet APIs. If you have Remote Windows Sockets installed (client part of the 
Catapult server), FTP WinInet API may fail because of the following reason: server
will specify a random port for a client to connect to for a data connection. 
If access via this port is disallowed, then error 10061 ("connection refused")
may be returned by the FTP APIs such as FtpFindFirstFile.
   

BROWSER/PLATFORM COMPATIBILITY
===============================
This sample is supported in Internet Explorer 4 or later on the 
Win32 platform.
 

SOURCE FILES
=============
FTPJr.cpp
FTPJr.ncp
FTPJr.vcproj
FTPjr.sln

SEE ALSO
=========
For more information on Networking, Protocols & Data Formats go to:
http://msdn.microsoft.com/library/default.asp?url=/workshop/networking/networking_node_entry.asp?frame=true.



==================================
© Microsoft Corporation  
