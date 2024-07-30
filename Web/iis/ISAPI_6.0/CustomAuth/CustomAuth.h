/*++

Copyright (c) 2003  Microsoft Corporation

Module Name: CustomAuth.h

Abstract:

    ISAPI extension to demonstrate using a wildcard script
    map with HSE_REQ_EXEC_URL to implement a custom forms
    based authentication scheme.

Author:

    ISAPI developer (Microsoft employee), October 2002

--*/

#ifndef _customauth_h
#define _customauth_h

#define MODULE_NAME                 "CustomAuth"
#define DEFAULT_USE_BUILTIN_LOGON   1
#define DEFAULT_USE_BUILTIN_LOGOFF  1
#define DEFAULT_USE_SSL             0
#define DEFAULT_USE_CLIENT_IP       1
#define DEFAULT_LOGON_URL           "/Logon.htm"
#define DEFAULT_LOGOFF_URL          "/Logoff.htm"
#define DEFAULT_LOGON_SUCCESS_URL   "/"
#define DEFAULT_LOGON_TIMEOUT       1200
#define DEFAULT_LOGON_TYPE          "network_cleartext"
#define DELETE_COOKIE               "CustomAuth=; Path=/; Expires=Tue, 01 Jan 1980 00:01:00 GMT"

//
// Built-in HTML pages
//

#define SERVER_ERROR    \
    "<html>\r\n"                                         \
    "<head> <title>500 Server Error</title> </head>\r\n" \
    "<h1> Server Error </h1>\r\n"                        \
    "<hr>\r\n"                                           \
    "The server was unable to process your request.\r\n" \
    "</html>"

#define LOGON_PAGE      \
    "<html>\r\n"                                                        \
    "<head><title>Please Log On</title></head>\r\n"                     \
    "<h1> Please log on to this server. </h1>\r\n"                      \
    "<hr>\r\n"                                                          \
    "<form name=\"LogonForm\" action=\"%s/Logon\" method=\"POST\">\r\n" \
    "<table border=0 cellspacing=2 cellpadding=0>\r\n"                  \
    "  <tr>\r\n"                                                        \
    "    <td>User Name:</td>\r\n"                                       \
    "    <td><input type=text size=30 name=UserName></td>\r\n"          \
    "  </tr>\r\n"                                                       \
    "  <tr>\r\n"                                                        \
    "    <td>Password:</td>\r\n"                                        \
    "    <td><input type=password size=30 name=Password></td>\r\n"      \
    "  </tr>\r\n"                                                       \
    "</table>\r\n"                                                      \
    "<input type=submit value=\"Log On\">\r\n"                          \
    "</form>\r\n"                                                       \
    "</html>\r\n"

#define LOGOFF_PAGE     \
    "<html>\r\n"                                              \
    "<head><title>Successfully Logged Off</title></head>\r\n" \
    "<h1> Goodbye </h1>\r\n"                                  \
    "<hr>\r\n"                                                \
    "You have successfully logged off from this server\r\n"   \
    "</html>\r\n"

#define REDIRECT_ENTITY \
    "<head><title>Document Moved</title></head>\r\n" \
    "<body><h1>Object Moved</h1>This document may "  \
    "be found <a HREF=\"%s\">here</a></body>"

//
// External globals
//

extern ISAPI_EXTENSION  g_Extension;
extern ISAPI_STRING     g_strIniFile;
extern ISAPI_STRING     g_strLogonUrl;
extern ISAPI_STRING     g_strLogonSuccessUrl;
extern ISAPI_STRING     g_strLogoffUrl;
extern INT              g_LogonTimeoutSeconds;
extern BOOL             g_fFilterInitialized;
extern BOOL             g_fUseBuiltInLogon;
extern BOOL             g_fUseBuiltInLogoff;
extern BOOL             g_fUseSSLForSubmission;
extern BOOL             g_fUseClientIpForEncryption;
extern DWORD            g_LogonType;

#endif  // _customauth_h