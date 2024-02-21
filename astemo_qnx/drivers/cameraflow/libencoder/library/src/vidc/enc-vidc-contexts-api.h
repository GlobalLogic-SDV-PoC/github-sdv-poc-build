/**
 **************************************************************************************************
 *  @file           : enc-vidc-contexts-api.h
 *  @brief          : Encoder VIDC buffers/frames contexts API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder VIDC buffers/frames contexts API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_VIDC_CONTEXTS_API__H__
#define __ENC_VIDC_CONTEXTS_API__H__

#include "enc-ctx.h"

int buffer_type2ctx(vidc_buffer_type type);

int vidc_allocate_buffers_frames_ctxs(enc_ctx_st_t *ctx, pmem_buffers_ctx_st_t *buffers_ctx);
void vidc_free_buffers_frames_ctxs(enc_ctx_st_t *ctx);

#endif /* __ENC_VIDC_CONTEXTS_API__H__ */

