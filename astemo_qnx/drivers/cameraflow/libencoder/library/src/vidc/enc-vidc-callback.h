/**
 **************************************************************************************************
 *  @file           : enc-vidc-callback.h
 *  @brief          : Encoder VIDC callback
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder VIDC callback function
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_VIDC_CALLBACK__H__
#define __ENC_VIDC_CALLBACK__H__

#include "pfm-types.h"

int vidc_callback(uint8_t *msg, uint32_t length, void *payload);

#endif /* __ENC_VIDC_CALLBACK__H__ */

