/**
 **************************************************************************************************
 *  @file           : enc-api.h
 *  @brief          : Encoder API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_API__H__
#define __ENC_API__H__

#include "enc-ctx.h"

int enc_init(enc_ctx_st_t *ctx);
int enc_deinit(enc_ctx_st_t *ctx);

int enc_get_buffers_dimensions(enc_ctx_st_t *ctx, size_t *size, size_t *count, int buffer);
int enc_get_image_dimensions(enc_ctx_st_t *ctx, image_ctx_st_t *image_ctx);
int enc_set_pmem_buffers(enc_ctx_st_t *ctx, pmem_buffers_ctx_st_t *buffers_ctx);

int enc_start(enc_ctx_st_t *ctx);
int enc_encode(enc_ctx_st_t *ctx);
int enc_encode_wait(enc_ctx_st_t *ctx);

#endif /* __ENC_API__H__ */

