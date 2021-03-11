

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from UUID.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef UUID_1902374198_h
#define UUID_1902374198_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

extern "C" {

    extern const char *unique_identifier_msgs_msg_UUIDTYPENAME;

}

struct unique_identifier_msgs_msg_UUIDSeq;
#ifndef NDDS_STANDALONE_TYPE
class unique_identifier_msgs_msg_UUIDTypeSupport;
class unique_identifier_msgs_msg_UUIDDataWriter;
class unique_identifier_msgs_msg_UUIDDataReader;
#endif

class unique_identifier_msgs_msg_UUID 
{
  public:
    typedef struct unique_identifier_msgs_msg_UUIDSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef unique_identifier_msgs_msg_UUIDTypeSupport TypeSupport;
    typedef unique_identifier_msgs_msg_UUIDDataWriter DataWriter;
    typedef unique_identifier_msgs_msg_UUIDDataReader DataReader;
    #endif

    DDS_Octet   uuid [16];

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* unique_identifier_msgs_msg_UUID_get_typecode(void); /* Type code */

DDS_SEQUENCE(unique_identifier_msgs_msg_UUIDSeq, unique_identifier_msgs_msg_UUID);

NDDSUSERDllExport
RTIBool unique_identifier_msgs_msg_UUID_initialize(
    unique_identifier_msgs_msg_UUID* self);

NDDSUSERDllExport
RTIBool unique_identifier_msgs_msg_UUID_initialize_ex(
    unique_identifier_msgs_msg_UUID* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool unique_identifier_msgs_msg_UUID_initialize_w_params(
    unique_identifier_msgs_msg_UUID* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
void unique_identifier_msgs_msg_UUID_finalize(
    unique_identifier_msgs_msg_UUID* self);

NDDSUSERDllExport
void unique_identifier_msgs_msg_UUID_finalize_ex(
    unique_identifier_msgs_msg_UUID* self,RTIBool deletePointers);

NDDSUSERDllExport
void unique_identifier_msgs_msg_UUID_finalize_w_params(
    unique_identifier_msgs_msg_UUID* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void unique_identifier_msgs_msg_UUID_finalize_optional_members(
    unique_identifier_msgs_msg_UUID* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool unique_identifier_msgs_msg_UUID_copy(
    unique_identifier_msgs_msg_UUID* dst,
    const unique_identifier_msgs_msg_UUID* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* UUID */

