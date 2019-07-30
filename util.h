#ifndef UTIL_H
#define UTIL_H

/* Includes */
#include <stdio.h>
#include <string.h>

/* Defines and constants */
#define NUM_COMMAND_LINE_ARGS   (2)                     /* number of expected arguments from the command line */
#define GUID_LENGTH_IN_BYTES    (16)                    /* length of Globally Unique Identifier in bytes */
#define MAX_BYTES_TO_READ       (GUID_LENGTH_IN_BYTES)  /* maximum number of bytes to read from a file pointer */
#define MAX_LENGTH_DATA         (5000)                  /* maximum number of bytes in stream properties and header 
                                                           extension data */
#define MAX_NUM_CODEC_ENTRIES   (4)                     /* maximum number of codec entries in a codec list object */
#define MAX_LENGTH_CODEC_NAME   (256)                   /* maximum number of bytes in a codec name */
#define MAX_NUM_CONTENT_DESC    (256)                   /* maximum number of content descriptors in an extended content
                                                           description object */
#define MAX_LENGTH_DESC_NAME    (256)                   /* maximum number of bytes in a content descriptor name */
#define MAX_LENGTH_DESC_VALUE   (128)                   /* maximum number of bytes in a content descriptor value */

/* Top-level Header Object GUID, defined in Section 10.1 of the ASF Specification */
static const char ASF_HEADER_OBJECT_GUID[GUID_LENGTH_IN_BYTES] =
{
    0x30, 0x26, 0xb2, 0x75, 0x8e, 0x66, 0xcf, 0x11,
    0xa6, 0xd9, 0x00, 0xaa, 0x00, 0x62, 0xce, 0x6c
};

/* Header Object GUIDs, defined in Section 10.2 of the ASF Specification */
static const char ASF_FILE_PROPERTIES_OBJECT_GUID[GUID_LENGTH_IN_BYTES] =
{
    0xa1, 0xdc, 0xab, 0x8c, 0x47, 0xa9, 0xcf, 0x11,
    0x8e, 0xe4, 0x00, 0xc0, 0x0c, 0x20, 0x53, 0x65
};

static const char ASF_STREAM_PROPERTIES_OBJECT_GUID[GUID_LENGTH_IN_BYTES] =
{
    0x91, 0x07, 0xdc, 0xb7, 0xb7, 0xa9, 0xcf, 0x11,
    0x8e, 0xe6, 0x00, 0xc0, 0x0c, 0x20, 0x53, 0x65
};

static const char ASF_HEADER_EXTENSION_OBJECT_GUID[GUID_LENGTH_IN_BYTES] =
{
    0xb5, 0x03, 0xbf, 0x5f, 0x2e, 0xa9, 0xcf, 0x11,
    0x8e, 0xe3, 0x00, 0xc0, 0x0c, 0x20, 0x53, 0x65
};

static const char ASF_CODEC_LIST_OBJECT_GUID[GUID_LENGTH_IN_BYTES] =
{
    0x40, 0x52, 0xd1, 0x86, 0x1d, 0x31, 0xd0, 0x11,
    0xa3, 0xa4, 0x00, 0xa0, 0xc9, 0x03, 0x48, 0xf6
};

static const char ASF_EXTENDED_CONTENT_DESCRIPTION_OBJECT_GUID[GUID_LENGTH_IN_BYTES] =
{
    0x40, 0xa4, 0xd0, 0xd2, 0x07, 0xe3, 0xd2, 0x11,
    0x97, 0xf0, 0x00, 0xa0, 0xc9, 0x5e, 0xa8, 0x50
};

static const char ASF_STREAM_BITRATE_PROPERTIES_OBJECT_GUID[GUID_LENGTH_IN_BYTES] =
{
    0xce, 0x75, 0xf8, 0x7b, 0x8d, 0x46, 0xd1, 0x11,
    0x8d, 0x82, 0x00, 0x60, 0x97, 0xc9, 0xa2, 0xb2
};

/* Stream Properties Object Stream Type GUIDs, defined in Section 10.4 of the ASF Specification */
static const char ASF_AUDIO_MEDIA_GUID[GUID_LENGTH_IN_BYTES] =
{
    0x40, 0x9e, 0x69, 0xf8, 0x4d, 0x5b, 0xcf, 0x11,
    0xa8, 0xfd, 0x00, 0x80, 0x5f, 0x5c, 0x44, 0x2b
};

static const char ASF_VIDEO_MEDIA_GUID[GUID_LENGTH_IN_BYTES] =
{
    0xc0, 0xef, 0x19, 0xbc, 0x4d, 0x5b, 0xcf, 0x11,
    0xa8, 0xfd, 0x00, 0x80, 0x5f, 0x5c, 0x44, 0x2b
};

/* Enums and structs */
/* Enum describing possible errors */
typedef enum {
     ASFPARSE_ERROR_OK = 0
    ,ASFPARSE_ERROR_INVALID_ARG
    ,ASFPARSE_ERROR_OPEN_FILE
    ,ASFPARSE_ERROR_INVALID_ASF_FILE
    ,ASFPARSE_ERROR_UNSUPPORTED_OBJECT_TYPE
} asfparse_error_t;

/* Enum describing possible object types */
typedef enum {
     OBJECT_TYPE_NONE = 0
    ,OBJECT_TYPE_HEADER
    ,OBJECT_TYPE_FILE_PROPERTIES
    ,OBJECT_TYPE_STREAM_PROPERTIES
    ,OBJECT_TYPE_CODEC_LIST
    ,OBJECT_TYPE_HEADER_EXTENSION
    ,OBJECT_TYPE_EXTENDED_CONTENT_DESCRIPTION
    ,OBJECT_TYPE_STREAM_BITRATE_PROPERTIES
} object_type_t;

/* Structure describing user-defined parameters */
typedef struct {
    const char     *p_filename;
    FILE           *p_file;
} params_t;

/* Structure describing a header object, defined in Section 3.1 of the ASF
   Specification */
typedef struct {
    int             object_size;
    int             num_objects;
} header_object_t;

/* Structure describing a file properties object, defined in Section 3.2 of 
   the ASF Specification */
typedef struct {
    int             object_size;
    int             file_size;
    int             creation_date;
    int             data_packets_count;
    int             play_duration;
    int             send_duration;
    int             preroll;
    int             flags;
    int             min_data_packet_size;
    int             max_data_packet_size;
    int             max_bitrate;
} file_properties_object_t;

/* Structure describing a stream properties object, defined in Section 3.3 of 
   the ASF Specification */
typedef struct {
    int             object_size;
    char            stream_type[GUID_LENGTH_IN_BYTES];
    char            err_correction_type[GUID_LENGTH_IN_BYTES];
    int             time_offset;
    int             type_specific_data_length;
    int             err_correction_data_length;
    int             flags;
    char            type_specific_data[MAX_LENGTH_DATA];
    unsigned char	err_correction_data[MAX_LENGTH_DATA];
} stream_properties_object_t;

/* Structure describing a header extension object, defined in Section 3.4 of 
   the ASF Specification */
typedef struct {
    int             object_size;
    int             data_size;
    char            data[MAX_LENGTH_DATA];
} header_extension_object_t;

/* Structures describing a codec entry and a codec list object, defined in 
   Section 3.5 of the ASF Specification */
typedef struct {
    int             codec_type;
    int             codec_name_length;
    char            codec_name[MAX_LENGTH_CODEC_NAME];
    int             codec_description_length;
    char            codec_description[MAX_LENGTH_CODEC_NAME];
    int             codec_information_length;
    char            codec_information[MAX_LENGTH_CODEC_NAME];
} codec_entry_t;

typedef struct {
    int             object_size;
    int             codec_entry_count;
    codec_entry_t   codec_entry[MAX_NUM_CODEC_ENTRIES];
} codec_list_object_t;

/* Structures describing a content descriptor and an extended content
   description object, defined in Section 3.11 of the ASF Specification */
typedef struct {
    int             name_length;
    char            name[MAX_LENGTH_DESC_NAME];
    int             value_data_type;
    int             value_length;
    char            value[MAX_LENGTH_DESC_VALUE];
} content_descriptor_t;

typedef struct {
    int                     object_size;
    int                     descriptor_count;
    content_descriptor_t    descriptor[MAX_NUM_CONTENT_DESC];
} extended_content_description_object_t;

/* Structure describing a stream bitrate properties object, defined in
   Section 3.12 of the ASF Specification */
typedef struct {
    int             object_size;
    int             bitrate_records_count;
} stream_bitrate_properties_object_t;


/* Function prototypes */
/*****************************************************************************
* NAME:  display_banner
* DESCRIPTION: Display version and configuration info
* RETURNS: none
******************************************************************************/
void
display_banner
    (
    );

/*****************************************************************************
* NAME: show_usage
* DESCRIPTION: Display usage to command line
* RETURNS: none
******************************************************************************/
void
show_usage
    (
    );

/*****************************************************************************
* NAME: parse_command_line
* DESCRIPTION: Parse command-line input
* RETURNS: asfparse_error_t
******************************************************************************/
asfparse_error_t
parse_command_line
    (int        argc        /* [in] number of command line arguments */
    ,char      *p_argv[]    /* [in] array of command line arguments */
    ,params_t  *params      /* [out] structure containing user-defined parameters */
    );

/*****************************************************************************
* NAME: convert_char_bytes_to_int
* DESCRIPTION: Convert an array of bytes to an integer value
* RETURNS: long long
******************************************************************************/
long long
convert_char_bytes_to_int
    (char      *buffer      /* [in] char buffer */
    ,int        num_bytes   /* [in] number of bytes in buffer */
    );

/*****************************************************************************
* NAME: get_object_type
* DESCRIPTION: Get ASF object type from its GUID (Globally Unique Identifier)
* RETURNS: asfparse_error
******************************************************************************/
asfparse_error_t
get_object_type
    (char          *guid        /* [in] char buffer containing object's GUID */
    ,object_type_t *obj_type    /* [out] object type */
    );

#endif