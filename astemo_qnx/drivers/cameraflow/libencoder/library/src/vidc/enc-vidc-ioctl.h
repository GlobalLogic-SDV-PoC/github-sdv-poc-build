/**
 **************************************************************************************************
 *  @file           : enc-vidc-ioctl.h
 *  @brief          : Encoder VIDC IOCTL operations
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder VIDC IOCTL operations
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_VIDC_IOCTL__H__
#define __ENC_VIDC_IOCTL__H__

#include "enc-ctx.h"
#include "enc-vidc-headers.h"

int vidc_open(enc_ctx_st_t *ctx, callback_handler_t callback);
void vidc_close(enc_ctx_st_t *ctx);

int vidc_start(enc_ctx_st_t *ctx);
int vidc_stop(enc_ctx_st_t *ctx);

int vidc_set_buffer(enc_ctx_st_t *ctx, uint8_t *buffer);
int vidc_free_buffer(enc_ctx_st_t *ctx, uint8_t *buffer);

int vidc_fill_frame(enc_ctx_st_t *ctx, vidc_frame_data_type *frame_ctx);
int vidc_empty_frame(enc_ctx_st_t *ctx, vidc_frame_data_type *frame_ctx);

int vidc_load_resources(enc_ctx_st_t *ctx);
int vidc_release_resourses(enc_ctx_st_t *ctx);

int vidc_get_property(enc_ctx_st_t *ctx, vidc_property_id_type id, size_t size, uint8_t *property);
int vidc_set_property(enc_ctx_st_t *ctx, vidc_property_id_type id, size_t size, uint8_t *property);

#endif /* __ENC_VIDC_IOCTL__H__ */

