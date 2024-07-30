// Start of ADOHeader.h

#ifndef _ADOHEADER_4B4143B7_6072_419e_ADD5_B8B57E5EC713_H
#define _ADOHEADER_4B4143B7_6072_419e_ADD5_B8B57E5EC713_H

#pragma warning(disable: 4146)  // Q231931 
#pragma warning(disable: 4192)  
#undef EOF
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" rename_namespace("ado20")
#pragma warning(default: 4146) 
#import "C:\Program Files\Common Files\System\ole db\oledb32.dll" rename_namespace("msdasc")
#pragma warning(default: 4192)  

#define MAX_COUNT 256
#define TRYDB try{
#define CATCHDB } catch(CException *err) {	err->ReportError();	err->Delete(); }

#endif

// Start of ADOHeader.h