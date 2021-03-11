
/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from UUID.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#include "UUIDSupport.h"
#include "UUIDPlugin.h"

#ifndef dds_c_log_impl_h              
#include "dds_c/dds_c_log_impl.h"                                
#endif        

/* ========================================================================= */
/**
<<IMPLEMENTATION>>

Defines:   TData,
TDataWriter,
TDataReader,
TTypeSupport

Configure and implement 'unique_identifier_msgs_msg_UUID' support classes.

Note: Only the #defined classes get defined
*/

/* ----------------------------------------------------------------- */
/* DDSDataWriter
*/

/**
<<IMPLEMENTATION >>

Defines:   TDataWriter, TData
*/

/* Requires */
#define TTYPENAME   unique_identifier_msgs_msg_UUIDTYPENAME

/* Defines */
#define TDataWriter unique_identifier_msgs_msg_UUIDDataWriter
#define TData       unique_identifier_msgs_msg_UUID

#include "dds_cpp/generic/dds_cpp_data_TDataWriter.gen"

#undef TDataWriter
#undef TData

#undef TTYPENAME

/* ----------------------------------------------------------------- */
/* DDSDataReader
*/

/**
<<IMPLEMENTATION >>

Defines:   TDataReader, TDataSeq, TData
*/

/* Requires */
#define TTYPENAME   unique_identifier_msgs_msg_UUIDTYPENAME

/* Defines */
#define TDataReader unique_identifier_msgs_msg_UUIDDataReader
#define TDataSeq    unique_identifier_msgs_msg_UUIDSeq
#define TData       unique_identifier_msgs_msg_UUID

#include "dds_cpp/generic/dds_cpp_data_TDataReader.gen"

#undef TDataReader
#undef TDataSeq
#undef TData

#undef TTYPENAME

/* ----------------------------------------------------------------- */
/* TypeSupport

<<IMPLEMENTATION >>

Requires:  TTYPENAME,
TPlugin_new
TPlugin_delete
Defines:   TTypeSupport, TData, TDataReader, TDataWriter
*/

/* Requires */
#define TTYPENAME    unique_identifier_msgs_msg_UUIDTYPENAME
#define TPlugin_new  unique_identifier_msgs_msg_UUIDPlugin_new
#define TPlugin_delete  unique_identifier_msgs_msg_UUIDPlugin_delete

/* Defines */
#define TTypeSupport unique_identifier_msgs_msg_UUIDTypeSupport
#define TData        unique_identifier_msgs_msg_UUID
#define TDataReader  unique_identifier_msgs_msg_UUIDDataReader
#define TDataWriter  unique_identifier_msgs_msg_UUIDDataWriter
#define TGENERATE_SER_CODE
#define TGENERATE_TYPECODE

#include "dds_cpp/generic/dds_cpp_data_TTypeSupport.gen"

#undef TTypeSupport
#undef TData
#undef TDataReader
#undef TDataWriter
#undef TGENERATE_TYPECODE
#undef TGENERATE_SER_CODE
#undef TTYPENAME
#undef TPlugin_new
#undef TPlugin_delete

