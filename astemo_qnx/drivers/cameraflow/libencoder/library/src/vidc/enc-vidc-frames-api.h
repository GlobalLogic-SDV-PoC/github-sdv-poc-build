/**
 **************************************************************************************************
 *  @file           : enc-vidc-frames-api.h
 *  @brief          : Encoder VIDC frames operations
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder VIDC frames operations header
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_VIDC_FRAME_API__H__
#define __ENC_VIDC_FRAME_API__H__

#include "enc-ctx.h"

int vidc_fill_input_frame(enc_ctx_st_t *ctx, uint8_t index, bool eos_flag, size_t data_len);
int vidc_fill_output_frame(enc_ctx_st_t *ctx, uint8_t index);

#endif /* __ENC_VIDC_FRAME_API__H__ */

