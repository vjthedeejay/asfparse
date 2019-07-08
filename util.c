#include "util.h"

/*****************************************************************************
* NAME:  display_banner
* DESCRIPTION: Display version and configuration info
* RETURNS: none
******************************************************************************/
void
display_banner
    (
    )
{
    /* display version info */
    printf("\nASF File Parser\nVersion 0.1\n");
    printf("\n--------------------------------------------------\n");

}

/*****************************************************************************
* NAME: show_usage
* DESCRIPTION: Display usage to command line
* RETURNS: none
******************************************************************************/
void
show_usage
    (
    )
{
    display_banner();
    printf("Usage: asfparse <inputfile>\n");
}

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
    )
{
    /* check for the correct number of command line arguments 
       and set the filename parameter */
    if (argc != NUM_COMMAND_LINE_ARGS)
    {
        show_usage();
        return ASFPARSE_ERROR_INVALID_ARG;
    }
    else
    {
        params->p_filename = p_argv[1];
        return ASFPARSE_ERROR_OK;
    }
}

/*****************************************************************************
* NAME: convert_char_bytes_to_int
* DESCRIPTION: Helper function to convert an array of bytes to an integer 
*              value
* RETURNS: int
******************************************************************************/
int
convert_char_bytes_to_int
    (char      *buffer      /* [in] char buffer */
    ,int        num_bytes   /* [in] number of bytes in buffer */
    )
{
    if (num_bytes == 2)
    {
        return (unsigned char)buffer[0] + 
            256 * (unsigned char)buffer[1];
    }
    else
    {
        return (unsigned char)buffer[0] + 
            256 * (unsigned char)buffer[1] +
            65536 * (unsigned char)buffer[2] + 
            16777216 * (unsigned char)buffer[3];
    }
}

/*****************************************************************************
* NAME: get_object_type
* DESCRIPTION: Get ASF object type from its GUID (Globally Unique Identifier)
* RETURNS: asfparse_error_t
******************************************************************************/
asfparse_error_t
get_object_type
    (char          *guid        /* [in] char buffer containing object's GUID */
    ,object_type_t *obj_type    /* [out] object type */
    )
{
    /* Compare the input GUID to known GUIDs defined in the ASF specification */
    if (memcmp(guid, ASF_HEADER_OBJECT_GUID, GUID_LENGTH_IN_BYTES) == 0)
    {
        *obj_type = OBJECT_TYPE_HEADER;
        return ASFPARSE_ERROR_OK;
    }
    else if (memcmp(guid, ASF_FILE_PROPERTIES_OBJECT_GUID, GUID_LENGTH_IN_BYTES) == 0)
    {
        *obj_type = OBJECT_TYPE_FILE_PROPERTIES;
        return ASFPARSE_ERROR_OK;
    }
    else if (memcmp(guid, ASF_STREAM_PROPERTIES_OBJECT_GUID, GUID_LENGTH_IN_BYTES) == 0)
    {
        *obj_type = OBJECT_TYPE_STREAM_PROPERTIES;
        return ASFPARSE_ERROR_OK;
    }
    else if (memcmp(guid, ASF_CODEC_LIST_OBJECT_GUID, GUID_LENGTH_IN_BYTES) == 0)
    {
        *obj_type = OBJECT_TYPE_CODEC_LIST;
        return ASFPARSE_ERROR_OK;
    }
    else if (memcmp(guid, ASF_HEADER_EXTENSION_OBJECT_GUID, GUID_LENGTH_IN_BYTES) == 0)
    {
        *obj_type = OBJECT_TYPE_HEADER_EXTENSION;
        return ASFPARSE_ERROR_OK;
    }
    else if (memcmp(guid, ASF_EXTENDED_CONTENT_DESCRIPTION_OBJECT_GUID, GUID_LENGTH_IN_BYTES) == 0)
    {
        *obj_type = OBJECT_TYPE_EXTENDED_CONTENT_DESCRIPTION;
        return ASFPARSE_ERROR_OK;
    }
    else if (memcmp(guid, ASF_STREAM_BITRATE_PROPERTIES_OBJECT_GUID, GUID_LENGTH_IN_BYTES) == 0)
    {
        *obj_type = OBJECT_TYPE_STREAM_BITRATE_PROPERTIES;
        return ASFPARSE_ERROR_OK;
    }
    else
    {
        return ASFPARSE_ERROR_UNSUPPORTED_OBJECT_TYPE;
    }
}
