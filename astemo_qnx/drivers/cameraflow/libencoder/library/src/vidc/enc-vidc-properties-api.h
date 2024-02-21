/**
 **************************************************************************************************
 *  @file           : enc-vidc-properties-api.h
 *  @brief          : Encoder VIDC properties API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder VIDC properties API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_VIDC_PROPERTIES_API__H__
#define __ENC_VIDC_PROPERTIES_API__H__

#include "enc-ctx.h"

int vidc_get_properties(enc_ctx_st_t *ctx);
int vidc_set_properties(enc_ctx_st_t *ctx);

#endif /* __ENC_VIDC_PROPERTIES_API__H__ */

