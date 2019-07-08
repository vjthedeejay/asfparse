#ifndef DISPLAY_H
#define DISPLAY_H

/* Includes */
#include <stdio.h>
#include <string.h>
#include "util.h"

/* Function prototypes */
/*****************************************************************************
* NAME:  display_header_object
* DESCRIPTION: Display header object information to command line
* RETURNS: none
******************************************************************************/
void
display_header_object
    (header_object_t   *header      /* [in] struct containing info about header object */
    );

/*****************************************************************************
* NAME:  display_file_properties_object
* DESCRIPTION: Display file properties object information to command line
* RETURNS: none
******************************************************************************/
void
display_file_properties_object
    (file_properties_object_t  *file_properties      /* [in] struct containing info about file properties object */
    );

/*****************************************************************************
* NAME:  display_stream_properties_object
* DESCRIPTION: Display stream properties object information to command line
* RETURNS: none
******************************************************************************/
void
display_stream_properties_object
    (stream_properties_object_t    *stream_properties   /* [in] struct containing info about stream properties object */
    );

/*****************************************************************************
* NAME:  display_header_extension_object
* DESCRIPTION: Display header extension object information to command line
* RETURNS: none
******************************************************************************/
void
display_header_extension_object
    (header_extension_object_t *header_ext  /* [in] struct containing info about header extension object */
    );

/*****************************************************************************
* NAME:  display_codec_list_object
* DESCRIPTION: Display codec list object information to command line
* RETURNS: none
******************************************************************************/
void
display_codec_list_object
    (codec_list_object_t   *codec_list  /* [in] struct containing info about codec list object */
    );

/*****************************************************************************
* NAME:  display_extended_content_description_object
* DESCRIPTION: Display extended content description object information to 
*              command line
* RETURNS: none
******************************************************************************/
void
display_extended_content_description_object
    (extended_content_description_object_t *ext_content_descr   /* [in] struct containing info about extended content description object */
    );

/*****************************************************************************
* NAME:  display_stream_bitrate_properties_object
* DESCRIPTION: Display stream bitrate properties object information to 
*              command line
* RETURNS: none
******************************************************************************/
void
display_stream_bitrate_properties_object
    (stream_bitrate_properties_object_t    *stream_bitrate_properties   /* [in] struct containing info about stream bitrate properties object */
    );

#endif