/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Apr 13 15:05:07 1999
 */
/* Compiler settings for C:\projects\RTK\ADsError\ADsError.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IADsError = {0x417D01DF,0xF1C6,0x11D2,{0xBC,0x88,0x00,0xC0,0x4F,0xD4,0x30,0xAF}};


const IID LIBID_ADSERRORLib = {0x417D01D3,0xF1C6,0x11D2,{0xBC,0x88,0x00,0xC0,0x4F,0xD4,0x30,0xAF}};


const CLSID CLSID_ADsError = {0x417D01E0,0xF1C6,0x11D2,{0xBC,0x88,0x00,0xC0,0x4F,0xD4,0x30,0xAF}};


#ifdef __cplusplus
}
#endif

