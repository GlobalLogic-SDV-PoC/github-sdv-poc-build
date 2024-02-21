/**
 **************************************************************************************************
 *  @file           : enc-vidc-contexts-api.c
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

#include <stdint.h>

#include "enc-ctx.h"
#include "enc-logger.h"
#include "enc-vidc-converters.h"
#include "enc-vidc-headers.h"
#include "enc-vidc-ioctl.h"
#include "enc-vidc-properties-api.h"
#include "pfm-stdlib.h"
#include "pfm-string.h"
#include "pfm-types.h"

void vidc_free_buffers_frames_ctxs(enc_ctx_st_t *ctx);

int buffer_type2ctx(vidc_buffer_type type)
{
        if (VIDC_BUFFER_INPUT == type) {
                return IO_INPUT_CTX;
        } else if (VIDC_BUFFER_OUTPUT == type){
                return IO_OUTPUT_CTX;
        } else {
            log_err("Incorrect buffer type: '%s'\n", vidc_buffer_type2str(type));

            return IO_INPUT_CTX;
        }
}

static
int allocate_frames_ctxs(vidc_frame_data_type ***ctxs, size_t count)
{
        int i = 0;
        vidc_frame_data_type **ctxs_tmp = NULL;
        const size_t ptr_size = sizeof(vidc_frame_data_type *);
        const size_t str_size = sizeof(vidc_frame_data_type);

        if (NULL == ctxs) {
                log_err("Invalid input: ctxs = %p\n", ctxs);

                return EINVAL;
        }

        log_dbg("Try to allocate [%d] frames contexts\n", count);

        ctxs_tmp = (vidc_frame_data_type **)pfm_calloc(1, ptr_size * count);
        if (NULL == ctxs_tmp) {
                log_err("Failed to allocate frames contexts\n");

                return ENOMEM;
        }

        for (i = 0; i < count; i++) {
                ctxs_tmp[i] = (vidc_frame_data_type *)pfm_calloc(1, str_size);
                if (NULL == ctxs_tmp[i]) {
                        log_err("Failed to allocate frame [%d] context\n", i);

                        return ENOMEM;
                }

                log_dbg("Successfully allocated frame [%d] context\n", i);
        }

        *ctxs = ctxs_tmp;

        log_dbg("Successfully allocated frames contexts\n");

        return EOK;
}

static
void free_frames_ctxs(vidc_frame_data_type ***ctxs, size_t count)
{
        int i = 0;
        vidc_frame_data_type **frames_ctxs_tmp = NULL;

        if (NULL == ctxs) {
                log_err("Invalid input: ctxs = %p\n", ctxs);

                return;
        }

        log_dbg("Try to free frames contexts\n");

        if (NULL == *ctxs) {
                log_dbg("Frames contexts already empty\n");

                return;
        }

        frames_ctxs_tmp = *ctxs;

        for (i = 0; i < count; i++) {
                log_dbg("Try to free frame [%d] context\n", i);

                pfm_free(frames_ctxs_tmp[i]);

                frames_ctxs_tmp[i] = NULL;
        }

        pfm_free(frames_ctxs_tmp);

        *ctxs = NULL;

        log_dbg("Successfully freed frames contexts\n");
}

static
int allocate_buffers_ctxs(enc_ctx_st_t *ctx, vidc_buffer_info_type ***buffers_ctxs,
        vidc_buffer_type type, size_t count, size_t size, void **buffers)
{
        int i = 0;
        int rc = EOK;
        vidc_buffer_info_type **buffers_ctxs_tmp = NULL;
        vidc_buffer_info_type buffer_ctx = {VIDC_BUFFER_UNUSED, 0};
        const size_t ptr_size = sizeof(vidc_buffer_info_type *);
        const size_t str_size = sizeof(vidc_buffer_info_type);

        if (NULL == ctx || NULL == buffers_ctxs || NULL == buffers) {
                log_err("Invalid input: ctx = %p, buffers_ctxs = %p, buffers = %p\n", ctx,
                        buffers_ctxs, buffers);

                return EINVAL;
        }

        log_dbg("Try to allocate [%d] buffers contexts\n", count);

        buffers_ctxs_tmp = (vidc_buffer_info_type **)pfm_calloc(1, ptr_size * count);
        if (NULL == buffers_ctxs_tmp) {
                log_err("Failed to allocate buffers contexts\n");

                return ENOMEM;
        }

        for (i = 0; i < count; i++) {
                buffers_ctxs_tmp[i] = (vidc_buffer_info_type *)pfm_calloc(1, str_size);
                if (NULL == buffers_ctxs_tmp[i]) {
                        log_err("Failed to allocate buffer [%d] context\n", i);

                        return ENOMEM;
                }

                buffers_ctxs_tmp[i]->buf_addr = (uint8_t *)buffers[i];
                buffers_ctxs_tmp[i]->buf_type = type;
                buffers_ctxs_tmp[i]->contiguous = true;
                buffers_ctxs_tmp[i]->buf_size = size;

                pfm_memcpy(&buffer_ctx, buffers_ctxs_tmp[i], str_size);

                rc = vidc_set_buffer(ctx, (uint8_t *)&buffer_ctx);
                if (EOK != rc) {
                        log_err("Failed to set buffer [%d] context. Error: %d\n", i, rc);

                        return rc;
                }

                log_dbg("Successfully allocated buffer [%d] context\n", i);
        }

        *buffers_ctxs = buffers_ctxs_tmp;

        log_dbg("Successfully allocated buffers contexts\n");

        return rc;
}

static
void free_buffers_ctxs(enc_ctx_st_t *ctx, vidc_buffer_info_type ***buffers_ctxs, size_t count)
{
        int i = 0;
        int rc = EOK;
        vidc_buffer_info_type **buffers_ctxs_tmp = NULL;
        vidc_buffer_info_type buffer_ctx = {VIDC_BUFFER_UNUSED, 0};

        if (NULL == ctx || NULL == buffers_ctxs) {
                log_err("Invalid input: ctx = %p, buffers_ctxs = %p\n", ctx, buffers_ctxs);

                return;
        }

        log_dbg("Try to free buffers contexts\n");

        if (NULL == *buffers_ctxs) {
                log_dbg("Buffers contexts already empty\n");

                return;
        }

        buffers_ctxs_tmp = *buffers_ctxs;

        for (i = 0; i < count; i++) {
                if (NULL != buffers_ctxs_tmp[i]) {
                        pfm_memcpy(&buffer_ctx, buffers_ctxs_tmp[i], sizeof(vidc_buffer_info_type));

                        rc = vidc_free_buffer(ctx, (uint8_t *)&buffer_ctx);
                        if (EOK != rc) {
                                log_err("Failed to free buffer [%d] context. Error: %d\n", i, rc);
                        }

                        pfm_free(buffers_ctxs_tmp[i]);

                        buffers_ctxs_tmp[i] = NULL;
                }

                log_dbg("Successfully freed buffer [%d] context\n", i);
        }

        pfm_free(buffers_ctxs_tmp);

        *buffers_ctxs = NULL;

        log_dbg("Successfully freed buffers contexts\n");
}

static
int allocate_buffers_frames_ctxs(enc_ctx_st_t *ctx, vidc_buffer_type type, void **buffers)
{
        int rc = EOK;
        int io_ctx = buffer_type2ctx(type);

        log_dbg("Try to allocate frames/buffers contexts for '%s'\n", vidc_buffer_type2str(type));
        log_dbg("Count frames/buffers contexts: %d\n", ctx->io_ctxs[io_ctx].required_buffers);

        rc = allocate_buffers_ctxs(ctx, &ctx->io_ctxs[io_ctx].buffers_ctxs,
                                   type, ctx->io_ctxs[io_ctx].required_buffers,
                                   ctx->io_ctxs[io_ctx].buffer_size, buffers);
        if (EOK != rc) {
                log_err("Failed to allocate buffers. Error: %d\n", rc);

                goto fail_exit;
        }

        rc = allocate_frames_ctxs(&ctx->io_ctxs[io_ctx].frames_ctxs,
                                  ctx->io_ctxs[io_ctx].required_buffers);
        if (EOK != rc) {
                log_err("Failed to allocate frames. Error: %d\n", rc);

                goto fail_exit;
        }

        log_dbg("Successfully allocated frames/buffers contexts\n");

        return rc;

fail_exit:
        log_dbg("Failed to allocate frames/buffers contexts. Error: %d\n", rc);

        return rc;
}

static
void free_buffers_frames_ctxs(enc_ctx_st_t *ctx, vidc_buffer_type type)
{
        int io_ctx = buffer_type2ctx(type);

        log_dbg("Try to free frames/buffers contexts\n");

        free_buffers_ctxs(ctx, &ctx->io_ctxs[io_ctx].buffers_ctxs,
                          ctx->io_ctxs[io_ctx].required_buffers);

        free_frames_ctxs(&ctx->io_ctxs[io_ctx].frames_ctxs,
                         ctx->io_ctxs[io_ctx].required_buffers);

        log_dbg("Successfully freed frames/buffers contexts\n");
}

int vidc_allocate_buffers_frames_ctxs(enc_ctx_st_t *ctx, pmem_buffers_ctx_st_t *buffers_ctxs)
{
        int rc = EOK;
        vidc_buffer_type type = VIDC_BUFFER_INPUT;
        int io_ctx = buffer_type2ctx(type);

        if (NULL == ctx || NULL == buffers_ctxs) {
                log_err("Invalid input: ctx = %p, buffers_ctxs = %p\n", ctx, buffers_ctxs);

                return EINVAL;
        }

        log_dbg("Try to allocate input/output frames/buffers contexts\n");

        rc = allocate_buffers_frames_ctxs(ctx, type, buffers_ctxs[io_ctx].buffers);
        if (EOK != rc) {
                log_err("Failed to allocate input frames/buffers contexts. Error: %d\n", rc);

                goto fail_exit;
        }

        type = VIDC_BUFFER_OUTPUT;
        io_ctx = buffer_type2ctx(type);
        rc = allocate_buffers_frames_ctxs(ctx, type, buffers_ctxs[io_ctx].buffers);
        if (EOK != rc) {
                log_err("Failed to allocate output frames/buffers. Error: %d\n", rc);

                goto fail_exit;
        }

        log_dbg("Successfully allocated input/output frames/buffers contexts\n");

        return EOK;

fail_exit:
        log_dbg("Failed to allocate inputs/outputs frames/buffers contexts. Error: %d\n", rc);

        vidc_free_buffers_frames_ctxs(ctx);

        return rc;
}

void vidc_free_buffers_frames_ctxs(enc_ctx_st_t *ctx)
{
        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return;
        }

        log_dbg("Try to free input/output buffers/frames contexts\n");

        free_buffers_frames_ctxs(ctx, VIDC_BUFFER_INPUT);

        free_buffers_frames_ctxs(ctx, VIDC_BUFFER_OUTPUT);

        log_dbg("Successfully freed input/output buffers/frames contexts\n");
}

