/**
 **************************************************************************************************
 *  @file           : client-ctx.h
 *  @brief          : Encoder client context
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder client context
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __CLIENT_CTX__H__
#define __CLIENT_CTX__H__

#include "enc-ctx.h"

#define INPUT_FILE      0
#define OUTPUT_FILE     1
#define FILES_COUNT     2

typedef struct client_ctx_st {
        struct pmem_buffers_ctx_st pmem_buffers_ctxs[IO_CTX_COUNT];
        struct image_ctx_st        image_ctx;
        struct enc_config_st       config;
        struct file_ctx_st         files[FILES_COUNT];
        struct enc_ctx_st          enc_ctx;
} client_ctx_st_t;

#endif /* __CLIENT_CTX__H__ */

