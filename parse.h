#ifndef PARSE_H
#define PARSE_H

/* Includes */
#include <stdio.h>
#include "util.h"

/* Function prototypes */
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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

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
    );

#endif