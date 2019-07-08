#include "parse.h"

/*****************************************************************************
* NAME:  parse_header_object
* DESCRIPTION: Parse header object information from ASF file according to
*              Section 3.1 of the ASF Specification
* RETURNS: asfparse_error_t
******************************************************************************/
asfparse_error_t
parse_header_object
    (header_object_t   *header      /* [out] struct containing info about header object */
    ,FILE              *fin         /* [in] file pointer to ASF file */
    )
{
    char                buffer[MAX_BYTES_TO_READ];
    asfparse_error_t    error;
    object_type_t       object_type;

    /* parse object id (16 bytes) */
    fread(buffer, 1, GUID_LENGTH_IN_BYTES, fin);
    error = get_object_type(buffer, &object_type);

    if (object_type != OBJECT_TYPE_HEADER)
    {
        return ASFPARSE_ERROR_INVALID_ASF_FILE;
    }

    /* parse object size (8 bytes) */
    fread(buffer, 1, 8, fin);
    header->object_size = convert_char_bytes_to_int(buffer, 8);

    /* parse number of header objects (4 bytes) */
    fread(buffer, 1, 4, fin);
    header->num_objects = convert_char_bytes_to_int(buffer, 4);

    /* parse and discard reserved fields (2 bytes) */
    fread(buffer, 1, 2, fin);

    return ASFPARSE_ERROR_OK;
}

/*****************************************************************************
* NAME:  parse_file_properties_object
* DESCRIPTION: Parse file properties object information from ASF file
*              according to Section 3.2 of the ASF Specification
* RETURNS: asfparse_error_t
******************************************************************************/
asfparse_error_t
parse_file_properties_object
    (file_properties_object_t  *file_properties     /* [out] struct containing info about file properties object */
    ,FILE                      *fin                 /* [in] file pointer to ASF file */
    )
{
    char    buffer[MAX_BYTES_TO_READ];

    /* parse object size (8 bytes) */
    fread(buffer, 1, 8, fin);
    file_properties->object_size = convert_char_bytes_to_int(buffer, 8);

    /* parse and discard file id (16 bytes) */
    fread(buffer, 1, 16, fin);

    /* parse file size (8 bytes) */
    fread(buffer, 1, 8, fin);
    file_properties->file_size = convert_char_bytes_to_int(buffer, 8);

    /* parse creation_date (8 bytes) */
    fread(buffer, 1, 8, fin);
    file_properties->creation_date = convert_char_bytes_to_int(buffer, 8); 

    /* parse data packets count (8 bytes) */
    fread(buffer, 1, 8, fin);
    file_properties->data_packets_count = convert_char_bytes_to_int(buffer, 8); 

    /* parse play duration (8 bytes) */
    fread(buffer, 1, 8, fin);
    file_properties->play_duration = convert_char_bytes_to_int(buffer, 8); 

    /* parse send duration (8 bytes) */
    fread(buffer, 1, 8, fin);
    file_properties->send_duration = convert_char_bytes_to_int(buffer, 8);

    /* parse preroll (8 bytes) */
    fread(buffer, 1, 8, fin);
    file_properties->preroll = convert_char_bytes_to_int(buffer, 8); 

    /* parse flags (4 bytes) */
    fread(buffer, 1, 4, fin);
    file_properties->flags = convert_char_bytes_to_int(buffer, 4);

    /* parse min data packet size (4 bytes) */
    fread(buffer, 1, 4, fin);
    file_properties->min_data_packet_size = convert_char_bytes_to_int(buffer, 4);

    /* parse max data packet size (4 bytes) */
    fread(buffer, 1, 4, fin);
    file_properties->max_data_packet_size = convert_char_bytes_to_int(buffer, 4);

    /* parse max bitrate (4 bytes) */
    fread(buffer, 1, 4, fin);
    file_properties->max_bitrate = convert_char_bytes_to_int(buffer, 4);

    return ASFPARSE_ERROR_OK;
}

/*****************************************************************************
* NAME:  parse_stream_properties_object
* DESCRIPTION: Parse stream properties object information from ASF file
*              according to Section 3.3 of the ASF Specification
* RETURNS: asfparse_error_t
******************************************************************************/
asfparse_error_t
parse_stream_properties_object
    (stream_properties_object_t    *stream_properties   /* [out] struct containing info about stream properties object */
    ,FILE                          *fin                 /* [in] file pointer to ASF file */
    )
{
    char    buffer[MAX_BYTES_TO_READ];

    /* parse object size (8 bytes) */
    fread(buffer, 1, 8, fin);
    stream_properties->object_size = convert_char_bytes_to_int(buffer, 8);

    /* parse stream type (16 bytes) */
    fread(stream_properties->stream_type, 1, 16, fin);

    /* parse error correction type (16 bytes) */
    fread(stream_properties->err_correction_type, 1, 16, fin);

    /* parse time offset (8 bytes) */
    fread(buffer, 1, 8, fin);
    stream_properties->time_offset = convert_char_bytes_to_int(buffer, 8);

    /* parse type specific data length (4 bytes) */
    fread(buffer, 1, 4, fin);
    stream_properties->type_specific_data_length = convert_char_bytes_to_int(buffer, 4);

    /* parse error correction data length (4 bytes) */
    fread(buffer, 1, 4, fin);
    stream_properties->err_correction_data_length = convert_char_bytes_to_int(buffer, 4);

    /* parse flags (2 bytes) */
    fread(buffer, 1, 2, fin);
    stream_properties->flags = convert_char_bytes_to_int(buffer, 2);

    /* parse and discard reserved field (4 bytes) */
    fread(buffer, 1, 4, fin);

    /* parse type-specific data */
    fread(stream_properties->type_specific_data
         ,1
         ,stream_properties->type_specific_data_length
         ,fin);

    /* parse error correction data */
    fread(stream_properties->err_correction_data
         ,1
         ,stream_properties->err_correction_data_length
         ,fin);

    return ASFPARSE_ERROR_OK;
}

/*****************************************************************************
* NAME:  parse_header_extension_object
* DESCRIPTION: Parse header extension object information from ASF file
*              according to Section 3.4 of the ASF Specification
* RETURNS: asfparse_error_t
******************************************************************************/
asfparse_error_t
parse_header_extension_object
    (header_extension_object_t *header_ext  /* [out] struct containing info about header extension object */
    ,FILE                      *fin         /* [in] file pointer to ASF file */
    )
{
    char    buffer[MAX_BYTES_TO_READ];

    /* parse object size (8 bytes) */
    fread(buffer, 1, 8, fin);
    header_ext->object_size = convert_char_bytes_to_int(buffer, 8);

    /* parse and discard reserved field 1 (16 bytes) */
    fread(buffer, 1, 16, fin);

    /* parse and discard reserved field 2 (2 bytes) */
    fread(buffer, 1, 2, fin);

    /* parse data size (4 bytes) */
    fread(buffer, 1, 4, fin);
    header_ext->data_size = convert_char_bytes_to_int(buffer, 4);

    /* parse data */
    fread(header_ext->data, 1, header_ext->data_size, fin);

    return ASFPARSE_ERROR_OK;
}

/*****************************************************************************
* NAME:  parse_codec_list_object
* DESCRIPTION: Parse codec list object information from ASF file according to
*              Section 3.5 of the ASF Specification
* RETURNS: asfparse_error_t
******************************************************************************/
asfparse_error_t
parse_codec_list_object
    (codec_list_object_t   *codec_list  /* [out] struct containing info about codec list object */
    ,FILE                  *fin         /* [in] file pointer to ASF file */
    )
{
    int     i;
    char    buffer[MAX_BYTES_TO_READ];

    /* parse object size (8 bytes) */
    fread(buffer, 1, 8, fin);
    codec_list->object_size = convert_char_bytes_to_int(buffer, 8);

    /* parse and discard reserved fields (16 bytes) */
    fread(buffer, 1, 16, fin);

    /* parse codec entries count (4 bytes) */
    fread(buffer, 1, 4, fin);
    codec_list->codec_entry_count = convert_char_bytes_to_int(buffer, 4);

    /* parse each codec entry */
    for (i = 0; i < codec_list->codec_entry_count; i++)
    {
        /* parse codec entry type (2 bytes) */
        fread(buffer, 1, 2, fin);
        codec_list->codec_entry[i].codec_type = convert_char_bytes_to_int(buffer, 2);

        /* parse codec name length (2 bytes) */
        fread(buffer, 1, 2, fin);
        codec_list->codec_entry[i].codec_name_length = convert_char_bytes_to_int(buffer, 2);

        /* parse codec name */
        fread(codec_list->codec_entry[i].codec_name
             ,1
             ,codec_list->codec_entry[i].codec_name_length * 2
             ,fin);

        /* parse codec description length (2 bytes) */
        fread(buffer, 1, 2, fin);
        codec_list->codec_entry[i].codec_description_length = convert_char_bytes_to_int(buffer, 2);

        /* parse codec description */
        fread(codec_list->codec_entry[i].codec_description
             ,1
             ,codec_list->codec_entry[i].codec_description_length * 2
             ,fin);

        /* parse codec information length (2 bytes) */
        fread(buffer, 1, 2, fin);
        codec_list->codec_entry[i].codec_information_length = convert_char_bytes_to_int(buffer, 2);

        /* parse codec information */
        fread(codec_list->codec_entry[i].codec_information
             ,1
             ,codec_list->codec_entry[i].codec_information_length
             ,fin);
    }
    
    return ASFPARSE_ERROR_OK;
}

/*****************************************************************************
* NAME:  parse_extended_content_description_object
* DESCRIPTION: Parse extended content description object information from ASF
*              file according to Section 3.11 of the ASF Specification
* RETURNS: asfparse_error_t
******************************************************************************/
asfparse_error_t
parse_extended_content_description_object
    (extended_content_description_object_t *ext_content_descr   /* [out] struct containing info about extended content description object */
    ,FILE                                  *fin                 /* [in] file pointer to ASF file */
    )
{
    int     i;
    char    buffer[MAX_BYTES_TO_READ];

    /* parse object size (8 bytes) */
    fread(buffer, 1, 8, fin);
    ext_content_descr->object_size = convert_char_bytes_to_int(buffer, 8);

    /* parse content descriptors count (2 bytes) */
    fread(buffer, 1, 2, fin);
    ext_content_descr->descriptor_count = convert_char_bytes_to_int(buffer, 2);

    /* parse each content descriptor */
    for (i = 0; i < ext_content_descr->descriptor_count; i++)
    {
        /* parse descriptor name length (2 bytes) */
        fread(buffer, 1, 2, fin);
        ext_content_descr->descriptor[i].name_length = convert_char_bytes_to_int(buffer, 2);

        /* parse descriptor name */
        fread(ext_content_descr->descriptor[i].name
             ,1
             ,ext_content_descr->descriptor[i].name_length
             ,fin);

        /* parse descriptor value data type (2 bytes) */
        fread(buffer, 1, 2, fin);
        ext_content_descr->descriptor[i].value_data_type = convert_char_bytes_to_int(buffer, 2);

        /* parse descriptor value length (2 bytes) */
        fread(buffer, 1, 2, fin);
        ext_content_descr->descriptor[i].value_length = convert_char_bytes_to_int(buffer, 2);

        /* parse descriptor value */
        fread(ext_content_descr->descriptor[i].value
             ,1
             ,ext_content_descr->descriptor[i].value_length
             ,fin);
    }
    
    return ASFPARSE_ERROR_OK;
}

/*****************************************************************************
* NAME:  parse_stream_bitrate_properties_object
* DESCRIPTION: Parse stream bitrate properties object information from ASF
*              file according to Section 3.12 of the ASF Specification
* RETURNS: asfparse_error_t
******************************************************************************/
asfparse_error_t
parse_stream_bitrate_properties_object
    (stream_bitrate_properties_object_t    *stream_bitrate_properties   /* [out] struct containing info about stream bitrate properties object */
    ,FILE                                  *fin                         /* [in] file pointer to ASF file */
    )
{
    int     i;
    char    buffer[MAX_BYTES_TO_READ];

    /* parse object size (8 bytes) */
    fread(buffer, 1, 8, fin);
    stream_bitrate_properties->object_size = convert_char_bytes_to_int(buffer, 8);

    /* parse bitrate records count (2 bytes) */
    fread(buffer, 1, 2, fin);
    stream_bitrate_properties->bitrate_records_count = convert_char_bytes_to_int(buffer, 2);

    /* parse and discard bitrate records */
    for (i = 0; i < stream_bitrate_properties->bitrate_records_count; i++)
    {
        fread(buffer, 1, 6, fin);
    }

    return ASFPARSE_ERROR_OK;
}