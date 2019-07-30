#include "display.h"

/*****************************************************************************
* NAME:  display_header_object
* DESCRIPTION: Display header object information to command line
* RETURNS: none
******************************************************************************/
void
display_header_object
    (header_object_t   *header      /* [in] struct containing info about header object */
    )
{
    printf("\nHEADER OBJECT\n");
    printf("    Object size: %d bytes\n", header->object_size);
    printf("    Number of header objects: %d\n", header->num_objects);
    printf("\n--------------------------------------------------\n");
}

/*****************************************************************************
* NAME:  display_file_properties_object
* DESCRIPTION: Display file properties object information to command line
* RETURNS: none
******************************************************************************/
void
display_file_properties_object
    (file_properties_object_t  *file_properties      /* [in] struct containing info about file properties object */
    )
{
    printf("\nFILE PROPERTIES OBJECT\n");
    printf("    Object size: %d bytes\n", file_properties->object_size);
    printf("    File Size: %d bytes\n", file_properties->file_size);
    printf("    Min Data Pkt Size: %d bytes\n", file_properties->min_data_packet_size);
    printf("    Max Data Pkt Size: %d bytes\n", file_properties->max_data_packet_size);
    printf("    Max Bitrate: %d bps\n", file_properties->max_bitrate);
    printf("\n--------------------------------------------------\n");
}

/*****************************************************************************
* NAME:  display_stream_properties_object
* DESCRIPTION: Display stream properties object information to command line
* RETURNS: none
******************************************************************************/
void
display_stream_properties_object
    (stream_properties_object_t    *stream_properties   /* [in] struct containing info about stream properties object */
    )
{
    printf("\nSTREAM PROPERTIES OBJECT\n");
    printf("    Object Size: %d bytes\n", stream_properties->object_size);

    printf("    Stream type: ");
    if (memcmp(stream_properties->stream_type, ASF_AUDIO_MEDIA_GUID, GUID_LENGTH_IN_BYTES) == 0)
    {
        printf("Audio\n");
        printf("    Audio Type Data Length: %d bytes\n", stream_properties->type_specific_data_length);
    }
    else if (memcmp(stream_properties->stream_type, ASF_VIDEO_MEDIA_GUID, GUID_LENGTH_IN_BYTES) == 0)
    {
        printf("Video\n");
        printf("    Video Type Data Length: %d bytes\n", stream_properties->type_specific_data_length);
    }
    else
    {
        printf("?\n");
        printf("    Type Specific Data Length: %d bytes\n", stream_properties->type_specific_data_length);
    }
    printf("\n--------------------------------------------------\n");
}

/*****************************************************************************
* NAME:  display_header_extension_object
* DESCRIPTION: Display header extension object information to command line
* RETURNS: none
******************************************************************************/
void
display_header_extension_object
    (header_extension_object_t *header_ext  /* [in] struct containing info about header extension object */
    )
{
    printf("\nHEADER EXTENSION OBJECT\n");
    printf("    Object size: %d bytes\n", header_ext->object_size);
    printf("    Header extension data size: %d bytes\n", header_ext->data_size);
    printf("\n--------------------------------------------------\n");
}

/*****************************************************************************
* NAME:  display_codec_list_object
* DESCRIPTION: Display codec list object information to command line
* RETURNS: none
******************************************************************************/
void
display_codec_list_object
    (codec_list_object_t   *codec_list  /* [in] struct containing info about codec list object */
    )
{
    int i, j;

    printf("\nCODEC LIST OBJECT\n");
    printf("    Object size: %d bytes\n", codec_list->object_size);
    printf("    Number of codecs: %d\n\n", codec_list->codec_entry_count);

    /* print information about each codec entry */
    for (i = 0; i < codec_list->codec_entry_count; i++)
    {
        printf("\tCODEC %d\n", i+1);

        printf("\t    Name: ");
        for (j = 0; j < codec_list->codec_entry[i].codec_name_length*2; j+=2)
        {
            printf("%c", codec_list->codec_entry[i].codec_name[j]);
        }
        printf("\n");

        printf("\t    Description: ");
        for (j = 0; j < codec_list->codec_entry[i].codec_description_length*2; j+=2)
        {
            printf("%c", codec_list->codec_entry[i].codec_description[j]);
        }
        printf("\n");

        printf("\t    Information: ");
        for (j = 0; j < codec_list->codec_entry[i].codec_information_length; j++)
        {
            printf("%c", codec_list->codec_entry[i].codec_information[j]);
        }
        printf("\n\n");
    }
    printf("\n--------------------------------------------------\n");
}

/*****************************************************************************
* NAME:  display_extended_content_description_object
* DESCRIPTION: Display extended content description object information to 
*              command line
* RETURNS: none
******************************************************************************/
void
display_extended_content_description_object
    (extended_content_description_object_t *ext_content_descr   /* [in] struct containing info about extended content description object */
    )
{
    int i, j;

    printf("\nEXTENDED CONTENT DESCRIPTION OBJECT\n");
    printf("    Object size: %d bytes\n", ext_content_descr->object_size);
    printf("    Number of content descriptors: %d\n\n", ext_content_descr->descriptor_count);
    
    for (i = 0; i < ext_content_descr->descriptor_count; i++)
    {
        printf("\tCONTENT DESCRIPTOR %d\n", i+1);
        printf("\t    ");
        
        for (j = 0; j < ext_content_descr->descriptor[i].name_length; j+=2)
        {
            printf("%c", ext_content_descr->descriptor[i].name[j]);
        }
        printf(": ");

        switch (ext_content_descr->descriptor[i].value_data_type)
        {
        case 0:	/* unicode string */
            for (j=0; j < ext_content_descr->descriptor[i].value_length; j+=2)
            {
                printf("%c", ext_content_descr->descriptor[i].value[j]);
            }
            break;
        case 1:	/* byte array */
            for (j = 0; j < ext_content_descr->descriptor[i].value_length; j++)
            {
                printf("%d ", ext_content_descr->descriptor[i].value[j]);
            }
            break;
        case 2:	/* bool */
        case 3:	/* 32-bit word */
        case 4:	/* 64-bit word */
            printf("%lld", convert_char_bytes_to_int(ext_content_descr->descriptor[i].value, 4));
            break;
        case 5:	/* 16-bit word */
            printf("%lld", convert_char_bytes_to_int(ext_content_descr->descriptor[i].value, 2));
            break;
        }
        printf("\n\n");
    }
    printf("\n--------------------------------------------------\n");
}

/*****************************************************************************
* NAME:  display_stream_bitrate_properties_object
* DESCRIPTION: Display stream bitrate properties object information to 
*              command line
* RETURNS: none
******************************************************************************/
void
display_stream_bitrate_properties_object
    (stream_bitrate_properties_object_t    *stream_bitrate_properties   /* [in] struct containing info about stream bitrate properties object */
    )
{
    printf("\nSTREAM BITRATE PROPERTIES OBJECT:\n");
    printf("    Object size: %d bytes\n", stream_bitrate_properties->object_size);
    printf("    Number of records: %d\n", stream_bitrate_properties->bitrate_records_count);
    printf("\n--------------------------------------------------\n");
}