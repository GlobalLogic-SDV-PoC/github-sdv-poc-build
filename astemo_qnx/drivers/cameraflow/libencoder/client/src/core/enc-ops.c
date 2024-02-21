/**
 **************************************************************************************************
 *  @file           : enc-ops.c
 *  @brief          : Encoder operations
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Functions to get buffer and image dimensions and encoder parameters
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "client-ctx.h"
#include "enc-api.h"
#include "enc-logger.h"

static
int get_buffer_dimensions(client_ctx_st_t *ctx)
{
        int rc = EOK;
        enc_ctx_st_t *enc_ctx = &ctx->enc_ctx;
        size_t *size = &ctx->pmem_buffers_ctxs[IO_INPUT_CTX].size;
        size_t *count = &ctx->pmem_buffers_ctxs[IO_INPUT_CTX].count;

        rc = enc_get_buffers_dimensions(enc_ctx, size, count, IO_INPUT_CTX);
        if (EOK != rc) {
                log_err("Failed to get input buffer size. Error: %d\n", rc);

                return rc;
        }

        log_dbg("Input buffer count : %d, size : 0x%08X (dec: %d)\n", count, size, size);

        size = &ctx->pmem_buffers_ctxs[IO_OUTPUT_CTX].size;
        count = &ctx->pmem_buffers_ctxs[IO_OUTPUT_CTX].count;

        rc = enc_get_buffers_dimensions(enc_ctx, size, count, IO_OUTPUT_CTX);
        if (EOK != rc) {
                log_err("Failed to get output buffer size. Error: %d\n", rc);

                return rc;
        }

        log_dbg("Output buffer count : %d, size : 0x%08X (dec: %d)\n", count, size, size);

        return rc;
}

static
int get_image_dimensions(client_ctx_st_t *ctx)
{
        int rc = EOK;
        enc_ctx_st_t *enc_ctx = &ctx->enc_ctx;
        image_ctx_st_t *image_ctx = &ctx->image_ctx;

        rc = enc_get_image_dimensions(enc_ctx, image_ctx);
        if (EOK != rc) {
                log_err("Failed to get input image dimensions. Error: %d\n", rc);

                return rc;
        }

        image_ctx->width = enc_ctx->config.width;
        image_ctx->height = enc_ctx->config.height;

        log_dbg("Input image dimensions:\n");
        log_dbg("width     : %d", image_ctx->width);
        log_dbg("height    : %d", image_ctx->height);
        log_dbg("stride Y  : %d", image_ctx->stride_y);
        log_dbg("height Y  : %d", image_ctx->height_y);
        log_dbg("stride UV : %d", image_ctx->stride_uv);
        log_dbg("height UV : %d", image_ctx->height_uv);

        return rc;
}

int get_encoder_parameters(client_ctx_st_t *ctx)
{
        int rc = EOK;

        log_dbg("Try to get encoder parameters\n");

        rc = get_buffer_dimensions(ctx);
        if (EOK != rc) {
                log_err("Failed to get buffers dimensions. Error: %d\n", rc);

                return rc;
        }

        rc = get_image_dimensions(ctx);
        if (EOK != rc) {
                log_err("Failed to get image dimensions. Error: %d\n", rc);

                return rc;
        }

        log_dbg("Successfully got encoder parameters\n");

        return rc;
}

