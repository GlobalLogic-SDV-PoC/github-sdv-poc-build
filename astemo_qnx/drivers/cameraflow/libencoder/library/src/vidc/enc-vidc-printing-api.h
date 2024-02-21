/**
 **************************************************************************************************
 *  @file           : enc-vidc-printing-api.h
 *  @brief          : Encoder VIDC printing API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder VIDC printing API for print VIDC structures
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_VIDC_PRINTING_API__H__
#define __ENC_VIDC_PRINTING_API__H__

#include "enc-vidc-headers.h"

void print_property(vidc_property_id_type id, void *property);

void print_buffer_ctx(vidc_buffer_info_type *ctx);
void print_frame_ctx(vidc_frame_data_type *ctx);

#endif /* __ENC_VIDC_PRINTING_API__H__ */

