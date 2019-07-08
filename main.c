#include <stdio.h>
#include <string.h>

#include "util.h"
#include "parse.h"
#include "display.h"

/*****************************************************************************
* NAME: main 
* DESCRIPTION: Entry point to application
******************************************************************************/
int 
main
    (int argc
    ,char* argv[]
    )
{
    asfparse_error_t    error;
    char                object_id[GUID_LENGTH_IN_BYTES];
    int                 i;
    params_t            params;
    object_type_t       object_type = OBJECT_TYPE_NONE;

    /* declare structs needed for parsing ASF file */
    header_object_t                         header;
    file_properties_object_t                file_properties;
    stream_properties_object_t              stream_properties;
    header_extension_object_t               header_extension;
    codec_list_object_t                     codec_list;
    extended_content_description_object_t   ext_content_descr;
    stream_bitrate_properties_object_t      stream_bitrate_properties;

    /* initialize structs */
    memset(&header, 0, sizeof(header_object_t));
    memset(&file_properties, 0, sizeof(file_properties_object_t));
    memset(&stream_properties, 0, sizeof(stream_properties_object_t));
    memset(&header_extension, 0, sizeof(header_extension_object_t));
    memset(&codec_list, 0, sizeof(codec_list_object_t));
    memset(&ext_content_descr, 0, sizeof(extended_content_description_object_t));
    memset(&stream_bitrate_properties, 0, sizeof(stream_bitrate_properties_object_t));

    /* initialize user-specified parameters */
    params.p_file = NULL;
    params.p_filename = NULL;

    /* parse command-line arguments */
    error = parse_command_line(argc, argv, &params);
    if (error != ASFPARSE_ERROR_OK)
    {
        return error;
    }

    /* display banner information */
    display_banner();

    /* print ASF file name to command line */
    printf("PARSING ASF FILE:\n    %s\n", params.p_filename);
    printf("\n--------------------------------------------------\n");

    /* open ASF file */
    params.p_file = fopen(params.p_filename, "rb");
    if (params.p_file == NULL)
    {
        printf("Error opening input file\n");
        return ASFPARSE_ERROR_OPEN_FILE;
    }

    /* parse and display header object in ASF file */
    error = parse_header_object(&header, params.p_file);
    if (error)
    {
        printf("Error parsing header object\n");
        fclose(params.p_file);
        return error;
    }
    else
    {
        display_header_object(&header);
    }
    
    /* parse and display subsequent objects in ASF file */
    for (i = 0; i < header.num_objects; i++)
    {
        /* read object id from file to get object type */
        fread(object_id, 1, GUID_LENGTH_IN_BYTES, params.p_file);
        error = get_object_type(object_id, &object_type);

        /* parse and display specific object based on its type
           print descriptive message and close file if an error occurs */
        if (error)
        {
            printf("Error parsing file: unsupported object\n");
            fclose(params.p_file);
            return error;
        }
        else
        {
            switch (object_type)
            {
            case OBJECT_TYPE_FILE_PROPERTIES:
                error = parse_file_properties_object(&file_properties, params.p_file);
                if (error)
                {
                    printf("Error parsing file properties object\n");
                    fclose(params.p_file);
                    return error;
                }
                else
                {
                    display_file_properties_object(&file_properties);
                }
                break;
            case OBJECT_TYPE_STREAM_PROPERTIES:
                error = parse_stream_properties_object(&stream_properties, params.p_file);
                if (error)
                {
                    printf("Error parsing stream properties object\n");
                    fclose(params.p_file);
                    return error;
                }
                else
                {
                    display_stream_properties_object(&stream_properties);
                }
                break;
            case OBJECT_TYPE_HEADER_EXTENSION:
                error = parse_header_extension_object(&header_extension, params.p_file);
                if (error)
                {
                    printf("Error parsing header extension object\n");
                    fclose(params.p_file);
                    return error;
                }
                else
                {
                    display_header_extension_object(&header_extension);
                }
                break;
            case OBJECT_TYPE_CODEC_LIST:
                error = parse_codec_list_object(&codec_list, params.p_file);
                if (error)
                {
                    printf("Error parsing codec list object\n");
                    fclose(params.p_file);
                    return error;
                }
                else
                {
                    display_codec_list_object(&codec_list);
                }
                break;
            case OBJECT_TYPE_EXTENDED_CONTENT_DESCRIPTION:
                error = parse_extended_content_description_object(&ext_content_descr, params.p_file);
                if (error)
                {
                    printf("Error parsing extended content description object\n");
                    fclose(params.p_file);
                    return error;
                }
                else
                {
                    display_extended_content_description_object(&ext_content_descr);
                }
                break;
            case OBJECT_TYPE_STREAM_BITRATE_PROPERTIES:
                error = parse_stream_bitrate_properties_object(&stream_bitrate_properties, params.p_file);
                if (error)
                {
                    printf("Error parsing stream bitrate properties object\n");
                    fclose(params.p_file);
                    return error;
                }
                else
                {
                    display_stream_bitrate_properties_object(&stream_bitrate_properties);
                }
                break;
            case OBJECT_TYPE_NONE:
            case OBJECT_TYPE_HEADER:
            default:
                break;
            }
        }
    }

    /* ensure file is closed after parsing */
    fclose(params.p_file);

    return ASFPARSE_ERROR_OK;
}