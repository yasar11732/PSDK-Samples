//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      Guids.h
//
//  Description:
//      File for definition of CLSIDs, GUIDs, and logging GUIDs.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once


//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#pragma warning( push )
#include <initguid.h>
#pragma warning( pop )

//////////////////////////////////////////////////////////////////////////////
//
// Reporting GUIDs
//
//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// CMgdClusCfgInit
////////////////////////////////////////////////////////////////////////

// {E9FBB913-DE7B-4d7d-B367-06E7EEC8019E}
DEFINE_GUID( TASKID_Minor_StorageResourceInitialize,
0xe9fbb913, 0xde7b, 0x4d7d, 0xb3, 0x67, 0x6, 0xe7, 0xee, 0xc8, 0x1, 0x9e);


////////////////////////////////////////////////////////////////////////
// CStorageResource
////////////////////////////////////////////////////////////////////////

// {A52B9965-6BF8-4216-8FC9-04E715180DD5}
DEFINE_GUID( TASKID_Minor_GetDriveLetterMappings_StorageResource,
0xa52b9965, 0x6bf8, 0x4216, 0x8f, 0xc9, 0x4, 0xe7, 0x15, 0x18, 0xd, 0xd5);

// {FA2988E6-51FC-47ce-861E-CE7A6E9ED6AF}
DEFINE_GUID( TASKID_Minor_GetName_Pointer,
0xfa2988e6, 0x51fc, 0x47ce, 0x86, 0x1e, 0xce, 0x7a, 0x6e, 0x9e, 0xd6, 0xaf);

// {2C130DBC-CDD3-4e24-A428-E284B64D4101}
DEFINE_GUID( TASKID_Minor_GetName_Memory, 
0x2c130dbc, 0xcdd3, 0x4e24, 0xa4, 0x28, 0xe2, 0x84, 0xb6, 0x4d, 0x41, 0x1);

// {E2986823-149E-40a8-8606-B8EDF1D07868}
DEFINE_GUID( TASKID_Minor_SetName_StorageResource,
0xe2986823, 0x149e, 0x40a8, 0x86, 0x6, 0xb8, 0xed, 0xf1, 0xd0, 0x78, 0x68);

// {47BE7AA7-A677-42f5-84C8-8E519179FE75}
DEFINE_GUID( TASKID_Minor_StorageResource_GetUID_Pointer,
0x47be7aa7, 0xa677, 0x42f5, 0x84, 0xc8, 0x8e, 0x51, 0x91, 0x79, 0xfe, 0x75);

// {A61D60C2-ABB4-4296-A42A-68860E97D2DD}
DEFINE_GUID( TASKID_Minor_StorageResource_GetUID_Memory,
0xa61d60c2, 0xabb4, 0x4296, 0xa4, 0x2a, 0x68, 0x86, 0xe, 0x97, 0xd2, 0xdd);

// {5771FF41-4B86-44a3-976E-00640B52AAEE}
DEFINE_GUID( TASKID_Minor_StorageResource_PreCreate,
0x5771ff41, 0x4b86, 0x44a3, 0x97, 0x6e, 0x0, 0x64, 0xb, 0x52, 0xaa, 0xee);

// {01D87B8E-0C74-4871-A4A3-6E573FCA5251}
DEFINE_GUID( TASKID_Minor_StorageResource_Create,
0x1d87b8e, 0xc74, 0x4871, 0xa4, 0xa3, 0x6e, 0x57, 0x3f, 0xca, 0x52, 0x51);

// {64D8F134-0767-4639-9A53-0388CE671405}
DEFINE_GUID( TASKID_Minor_SetWbemServices_StorageResource,
0x64d8f134, 0x767, 0x4639, 0x9a, 0x53, 0x3, 0x88, 0xce, 0x67, 0x14, 0x5);

// {626153A8-004D-49aa-AB43-DB2FF5A33A68}
DEFINE_GUID( TASKID_Minor_StorageResource_Signature,
0x626153a8, 0x4d, 0x49aa, 0xab, 0x43, 0xdb, 0x2f, 0xf5, 0xa3, 0x3a, 0x68);

// {6B10761B-5ECA-4ce7-8E9D-7FA8A078B0D4}
DEFINE_GUID( TASKID_Minor_SetWbemObject_StorageResource, 
0x6b10761b, 0x5eca, 0x4ce7, 0x8e, 0x9d, 0x7f, 0xa8, 0xa0, 0x78, 0xb0, 0xd4);

// {9C22A873-9152-4b13-9160-CCB9C9279039}
DEFINE_GUID( TASKID_Minor_Next_StorageResource,
0x9c22a873, 0x9152, 0x4b13, 0x91, 0x60, 0xcc, 0xb9, 0xc9, 0x27, 0x90, 0x39);

// {FE52B921-C04B-47aa-8CC6-E320AF91D4BF}
DEFINE_GUID( TASKID_Minor_StorageResource_No_Partitions,
0xfe52b921, 0xc04b, 0x47aa, 0x8c, 0xc6, 0xe3, 0x20, 0xaf, 0x91, 0xd4, 0xbf);

// {E78EDBB5-5804-462e-870E-599BF898454C}
DEFINE_GUID( TASKID_Minor_Clone_StorageResource,
0xe78edbb5, 0x5804, 0x462e, 0x87, 0xe, 0x59, 0x9b, 0xf8, 0x98, 0x45, 0x4c);

// {255D2FC8-CF19-44f5-A515-7505C1F44A0A}
DEFINE_GUID( TASKID_Minor_HrGetSCSIBus, 
0x255d2fc8, 0xcf19, 0x44f5, 0xa5, 0x15, 0x75, 0x5, 0xc1, 0xf4, 0x4a, 0xa);

// {8979ADBE-6211-4e70-8503-5B279487123F}
DEFINE_GUID( TASKID_Minor_HrGetSCSIPort,
0x8979adbe, 0x6211, 0x4e70, 0x85, 0x3, 0x5b, 0x27, 0x94, 0x87, 0x12, 0x3f);

// {800ADB0B-7F9D-465b-B57B-F3AF46D67EC2}
DEFINE_GUID( TASKID_Minor_HrGetDeviceID_Pointer, 
0x800adb0b, 0x7f9d, 0x465b, 0xb5, 0x7b, 0xf3, 0xaf, 0x46, 0xd6, 0x7e, 0xc2);

// {401B7B17-D44D-4d45-A1A9-C7DD49FBEDA3}
DEFINE_GUID( TASKID_Minor_HrGetDeviceID_Memory,
0x401b7b17, 0xd44d, 0x4d45, 0xa1, 0xa9, 0xc7, 0xdd, 0x49, 0xfb, 0xed, 0xa3);

// {8B37A3E0-E23C-405e-A289-E89F9F5E8193}
DEFINE_GUID( TASKID_Minor_HrGetSignature_Pointer,
0x8b37a3e0, 0xe23c, 0x405e, 0xa2, 0x89, 0xe8, 0x9f, 0x9f, 0x5e, 0x81, 0x93);

// {E0A688F7-E589-4910-852E-7A3BD14A3A14}
DEFINE_GUID( TASKID_Minor_HrSetFriendlyName_StorageResource,
0xe0a688f7, 0xe589, 0x4910, 0x85, 0x2e, 0x7a, 0x3b, 0xd1, 0x4a, 0x3a, 0x14);

// {025AF944-540E-4b60-AC29-0B4145873719}
DEFINE_GUID( TASKID_Minor_HrGetPartitionInfo,
0x25af944, 0x540e, 0x4b60, 0xac, 0x29, 0xb, 0x41, 0x45, 0x87, 0x37, 0x19);

// {A63FEBA9-B876-458c-9D46-73E29E7DFD43}
DEFINE_GUID( TASKID_Minor_WMI_DiskDrivePartitions_Qry_Failed,
0xa63feba9, 0xb876, 0x458c, 0x9d, 0x46, 0x73, 0xe2, 0x9e, 0x7d, 0xfd, 0x43);

// {2865E3CF-251D-49d1-BD02-4A187BFE6B87}
DEFINE_GUID( TASKID_Minor_WQL_Partition_Qry_Next_Failed,
0x2865e3cf, 0x251d, 0x49d1, 0xbd, 0x2, 0x4a, 0x18, 0x7b, 0xfe, 0x6b, 0x87);

// {D099E738-2D66-4295-9C13-8E310C78BFB2}
DEFINE_GUID( TASKID_Minor_HrAddPartitionToArray,
0xd099e738, 0x2d66, 0x4295, 0x9c, 0x13, 0x8e, 0x31, 0xc, 0x78, 0xbf, 0xb2);

// {7F305E21-D0BF-4821-AB7E-25881FC5DB2E}
DEFINE_GUID( TASKID_Minor_HrCreateFriendlyName_VOID,
0x7f305e21, 0xd0bf, 0x4821, 0xab, 0x7e, 0x25, 0x88, 0x1f, 0xc5, 0xdb, 0x2e);

// {E8CB2D98-4634-442b-BEA5-C9FCAC08634A}
DEFINE_GUID( TASKID_Minor_HrCreateFriendlyName_BSTR,
0xe8cb2d98, 0x4634, 0x442b, 0xbe, 0xa5, 0xc9, 0xfc, 0xac, 0x8, 0x63, 0x4a);


////////////////////////////////////////////////////////////////////////
// CEnumStorageResource
////////////////////////////////////////////////////////////////////////

// {A07CEAC4-8C45-4938-B70F-F75CDAC71E18}
DEFINE_GUID( TASKID_Minor_InitWbem_Enum_StorageResource,
0xa07ceac4, 0x8c45, 0x4938, 0xb7, 0xf, 0xf7, 0x5c, 0xda, 0xc7, 0x1e, 0x18);

// {5D9625A4-9DE4-4872-9523-264E0D830A0F}
DEFINE_GUID( TASKID_Minor_SetWbemServices_Enum_StorageResource, 
0x5d9625a4, 0x9de4, 0x4872, 0x95, 0x23, 0x26, 0x4e, 0xd, 0x83, 0xa, 0xf);

// {C08A253C-A491-4a57-B50B-1AD2A349DA57}
DEFINE_GUID( TASKID_Minor_Boot_Partition_Not_NTFS, 
0xc08a253c, 0xa491, 0x4a57, 0xb5, 0xb, 0x1a, 0xd2, 0xa3, 0x49, 0xda, 0x57);

// {AC376681-2A03-4219-930B-5BCBF48784F3}
DEFINE_GUID( TASKID_Minor_Next_Enum_StorageResource,
0xac376681, 0x2a03, 0x4219, 0x93, 0xb, 0x5b, 0xcb, 0xf4, 0x87, 0x84, 0xf3);

// {75DE3C02-09DF-4bb2-99BD-830F122EDB87}
DEFINE_GUID( TASKID_Minor_Clone_Enum_StorageResource,
0x75de3c02, 0x9df, 0x4bb2, 0x99, 0xbd, 0x83, 0xf, 0x12, 0x2e, 0xdb, 0x87);

// {C08826D6-D99B-46d1-A5E4-996B8AAA336D}
DEFINE_GUID( TASKID_Minor_Pruning_Boot_Disk_Bus,
0xc08826d6, 0xd99b, 0x46d1, 0xa5, 0xe4, 0x99, 0x6b, 0x8a, 0xaa, 0x33, 0x6d);

// {3C02DAA7-4C68-4a68-AE56-454F26D6B8C6}
DEFINE_GUID( TASKID_Minor_Pruning_System_Disk_Bus,
0x3c02daa7, 0x4c68, 0x4a68, 0xae, 0x56, 0x45, 0x4f, 0x26, 0xd6, 0xb8, 0xc6);

// {3E18B282-DDD5-4eff-8ACE-BE2948372E51}
DEFINE_GUID( TASKID_Minor_HrAddObjectToArray,
0x3e18b282, 0xddd5, 0x4eff, 0x8a, 0xce, 0xbe, 0x29, 0x48, 0x37, 0x2e, 0x51);

// {46597D45-38D8-4134-9B34-97DDC094A875}
DEFINE_GUID( TASKID_Minor_HrIsLogicalDiskNTFS_InvalidArg,
0x46597d45, 0x38d8, 0x4134, 0x9b, 0x34, 0x97, 0xdd, 0xc0, 0x94, 0xa8, 0x75);

// {CD5CBE2E-9A98-4eac-BDC3-20195C217AD3}
DEFINE_GUID( TASKID_Minor_HrIsLogicalDiskNTFS,
0xcd5cbe2e, 0x9a98, 0x4eac, 0xbd, 0xc3, 0x20, 0x19, 0x5c, 0x21, 0x7a, 0xd3);

// {AFCFF8C7-F83C-482e-BBEF-60FDCD4CC41A}
DEFINE_GUID( TASKID_Minor_WMI_Get_LogicalDisk_Failed,
0xafcff8c7, 0xf83c, 0x482e, 0xbb, 0xef, 0x60, 0xfd, 0xcd, 0x4c, 0xc4, 0x1a);

// {B8F5736B-2046-4762-8122-C737ED92BF28}
DEFINE_GUID( TASKID_Minor_Non_SCSI_Disks,
0xb8f5736b, 0x2046, 0x4762, 0x81, 0x22, 0xc7, 0x37, 0xed, 0x92, 0xbf, 0x28);

// {95D0BDFA-0579-4b40-8DDB-4F9BCA9D7205}
DEFINE_GUID( TASKID_Minor_Pruning_PageFile_Disk_Bus,
0x95d0bdfa, 0x579, 0x4b40, 0x8d, 0xdb, 0x4f, 0x9b, 0xca, 0x9d, 0x72, 0x5);

// {32135624-E54D-46c2-A7EE-704DE416FBE3}
DEFINE_GUID( TASKID_Minor_Pruning_CrashDump_Disk_Bus,
0x32135624, 0xe54d, 0x46c2, 0xa7, 0xee, 0x70, 0x4d, 0xe4, 0x16, 0xfb, 0xe3);

// {94FEA8D6-A61D-43aa-9CD9-E22C1532F7A1}
DEFINE_GUID( TASKID_Minor_StorageResource_Cluster_Capable,
0x94fea8d6, 0xa61d, 0x43aa, 0x9c, 0xd9, 0xe2, 0x2c, 0x15, 0x32, 0xf7, 0xa1);

// {25205B87-3ABE-4527-B9B2-C4D30E46D250}
DEFINE_GUID( TASKID_Minor_HrGetDisks,
0x25205b87, 0x3abe, 0x4527, 0xb9, 0xb2, 0xc4, 0xd3, 0xe, 0x46, 0xd2, 0x50);

// {CDE9F8FC-5C95-4e9a-B73A-19807DA9F5A5}
DEFINE_GUID( TASKID_Minor_WQL_Disk_Qry_Next_Failed,
0xcde9f8fc, 0x5c95, 0x4e9a, 0xb7, 0x3a, 0x19, 0x80, 0x7d, 0xa9, 0xf5, 0xa5);


////////////////////////////////////////////////////////////////////////
// CStorageResType
////////////////////////////////////////////////////////////////////////

// {EE6AB597-5992-4a86-A785-C143C768DFB7}
DEFINE_GUID( TASKID_Minor_StorageResourceType_CommitChanges,
0xee6ab597, 0x5992, 0x4a86, 0xa7, 0x85, 0xc1, 0x43, 0xc7, 0x68, 0xdf, 0xb7);


////////////////////////////////////////////////////////////////////////
// CPartitionInfo
////////////////////////////////////////////////////////////////////////

// {65A8703B-D91A-4edc-861D-1BF37A3A0F84}
DEFINE_GUID( TASKID_Minor_SetWbemServices_Partition,
0x65a8703b, 0xd91a, 0x4edc, 0x86, 0x1d, 0x1b, 0xf3, 0x7a, 0x3a, 0xf, 0x84);

// {3704F82D-1B0E-4b2f-BD33-86E44AC9A59B}
DEFINE_GUID( TASKID_Minor_PartitionInfo_GetUID_Pointer,
0x3704f82d, 0x1b0e, 0x4b2f, 0xbd, 0x33, 0x86, 0xe4, 0x4a, 0xc9, 0xa5, 0x9b);

// {5872713B-70E1-4155-8974-209697627AC6}
DEFINE_GUID( TASKID_Minor_PartitionInfo_GetUID_Memory,
0x5872713b, 0x70e1, 0x4155, 0x89, 0x74, 0x20, 0x96, 0x97, 0x62, 0x7a, 0xc6);

// {31729C01-AAC2-4baa-86F4-F6DCDDCB700B}
DEFINE_GUID( TASKID_Minor_PartitionInfo_GetName_Pointer,
0x31729c01, 0xaac2, 0x4baa, 0x86, 0xf4, 0xf6, 0xdc, 0xdd, 0xcb, 0x70, 0xb);

// {EBF09D63-05D2-4019-9B8A-4EB064AF01F1}
DEFINE_GUID( TASKID_Minor_PartitionInfo_GetDescription_Pointer,
0xebf09d63, 0x5d2, 0x4019, 0x9b, 0x8a, 0x4e, 0xb0, 0x64, 0xaf, 0x1, 0xf1);

// {6CA61237-00C4-4e5b-90A0-68E26315D1FC}
DEFINE_GUID( TASKID_Minor_PartitionInfo_GetDescription_Memory,
0x6ca61237, 0xc4, 0x4e5b, 0x90, 0xa0, 0x68, 0xe2, 0x63, 0x15, 0xd1, 0xfc);

// {927ECC61-E8B3-4919-88B7-2E89874784AB}
DEFINE_GUID( TASKID_Minor_GetDriveLetterMappings_Partition,
0x927ecc61, 0xe8b3, 0x4919, 0x88, 0xb7, 0x2e, 0x89, 0x87, 0x47, 0x84, 0xab);

// {8AF69452-886B-45ee-B4FD-D2FA7F47F4C4}
DEFINE_GUID( TASKID_Minor_GetSize,
0x8af69452, 0x886b, 0x45ee, 0xb4, 0xfd, 0xd2, 0xfa, 0x7f, 0x47, 0xf4, 0xc4);

// {CF4008B3-E902-4a54-80DD-2695557F4FCC}
DEFINE_GUID( TASKID_Minor_SetWbemObject_Partition,
0xcf4008b3, 0xe902, 0x4a54, 0x80, 0xdd, 0x26, 0x95, 0x55, 0x7f, 0x4f, 0xcc);

// {6EA41D85-B149-406c-93C5-59718C3EFE3C}
DEFINE_GUID( TASKID_Minor_Disk_No_File_System,
0x6ea41d85, 0xb149, 0x406c, 0x93, 0xc5, 0x59, 0x71, 0x8c, 0x3e, 0xfe, 0x3c);

// {F0493CC2-90BE-4199-9847-E71BED990B63}
DEFINE_GUID( TASKID_Minor_Disk_Not_NTFS,
0xf0493cc2, 0x90be, 0x4199, 0x98, 0x47, 0xe7, 0x1b, 0xed, 0x99, 0xb, 0x63);

// {721099AF-7CC8-4f87-A213-487297F7194F}
DEFINE_GUID( TASKID_Minor_GetFriendlyName,
0x721099af, 0x7cc8, 0x4f87, 0xa2, 0x13, 0x48, 0x72, 0x97, 0xf7, 0x19, 0x4f);

// {BD4BE998-6400-46a2-A1D8-0BB5FC17DD42}
DEFINE_GUID( TASKID_Minor_HrGetFriendlyName,
0xbd4be998, 0x6400, 0x46a2, 0xa1, 0xd8, 0xb, 0xb5, 0xfc, 0x17, 0xdd, 0x42);

// {721099AF-7CC8-4f87-A213-487297F7194F}
DEFINE_GUID( TASKID_Minor_HrAddLogicalDiskToArray,
0x721099af, 0x7cc8, 0x4f87, 0xa2, 0x13, 0x48, 0x72, 0x97, 0xf7, 0x19, 0x4f);

// {3787CC20-5822-4e23-B4B2-8712EA4823D6}
DEFINE_GUID( TASKID_Minor_HrGetLogicalDisks,
0x3787cc20, 0x5822, 0x4e23, 0xb4, 0xb2, 0x87, 0x12, 0xea, 0x48, 0x23, 0xd6);

// {B2211A28-6F50-4532-B16F-09FA7EB55472}
DEFINE_GUID( TASKID_Minor_WMI_Logical_Disks_Qry_Failed,
0xb2211a28, 0x6f50, 0x4532, 0xb1, 0x6f, 0x9, 0xfa, 0x7e, 0xb5, 0x54, 0x72);

// {67215FFB-C63D-4fee-B2D4-EA23E9F84C7E}
DEFINE_GUID( TASKID_Minor_HrGetLogicalDisks_Next,
0x67215ffb, 0xc63d, 0x4fee, 0xb2, 0xd4, 0xea, 0x23, 0xe9, 0xf8, 0x4c, 0x7e);


//////////////////////////////////////////////////////////////////////////////
//
// Registration GUIDs
//
//////////////////////////////////////////////////////////////////////////////

//
// The Resource Type's GUID
//
// TODO: Regenerate the GUID below using guidgen.exe so that the RESTYPE guid is
//       truly unique.
//       
//
// {215929D2-0007-4d94-92A8-C058C2045900}
DEFINE_GUID( RESTYPE_StorageResource,
0x215929d2, 0x7, 0x4d94, 0x92, 0xa8, 0xc0, 0x58, 0xc2, 0x4, 0x59, 0x0);

//
// This is the Cluster Administrator Extension dll CLSID to register for the type.
//
// TODO: Replace this CLSID with the one in the resource type's extension dll,
//       which can be found in ExtObjID.h.
//
// {67BBCE98-BEE6-47cf-8C21-EC09E4B942A5}
//DEFINE_GUID( CLSID_CoStorageResourceDllEx,
//0x67bbce98, 0xbee6, 0x47cf, 0x8c, 0x21, 0xec, 0x9, 0xe4, 0xb9, 0x42, 0xa5);