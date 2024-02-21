/**
 **************************************************************************************************
 *  @file           : enc-vidc-frames-api.c
 *  @brief          : Encoder VIDC frames operations
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder VIDC frames operations
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "enc-ctx.h"
#include "enc-logger.h"
#include "enc-vidc-ioctl.h"
#include "pfm-string.h"

int vidc_fill_input_frame(enc_ctx_st_t *ctx, uint8_t index, bool eos_flag, size_t data_len)
{
        int rc = EOK;
        vidc_frame_data_type *frame_ctx = NULL;
        vidc_buffer_info_type *buffer_ctx = NULL;

        log_dbg("Try to fill input frame\n");

        if (NULL == ctx) {
                log_dbg("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        frame_ctx = ctx->io_ctxs[IO_INPUT_CTX].frames_ctxs[index];
        buffer_ctx = ctx->io_ctxs[IO_INPUT_CTX].buffers_ctxs[index];

        pfm_memset(frame_ctx, 0, sizeof(vidc_frame_data_type));

        frame_ctx->buf_type = VIDC_BUFFER_INPUT;
        frame_ctx->frame_addr = buffer_ctx->buf_addr;
        frame_ctx->alloc_len = buffer_ctx->buf_size;
        frame_ctx->frm_clnt_data = index;
        frame_ctx->data_len = data_len;
        frame_ctx->timestamp = ctx->time_stamp_Lfile;

        log_dbg("Frame info :\n");
        log_dbg("index      : %d\n", index);
        log_dbg("eos flag   : %s\n", BOOL_STR(eos_flag));
        log_dbg("data len   : 0x%08X\n", data_len);

        if (true == eos_flag) {
                frame_ctx->flags |= VIDC_FRAME_FLAG_EOS;
                ctx->input_eos_flag = true;
        }

        rc = vidc_empty_frame(ctx, frame_ctx);
        if (EOK != rc) {
                log_err("Failed to fill input frame. Error: %d\n", rc);

                return rc;
        }

        log_dbg("Successfully filled input frame\n");

        return rc;
}

int vidc_fill_output_frame(enc_ctx_st_t *ctx, uint8_t index)
{
        int rc = EOK;
        vidc_frame_data_type *frame_ctx = NULL;
        vidc_buffer_info_type *buffer_ctx = NULL;

        log_dbg("Try to fill output frame\n");

        if (NULL == ctx) {
                log_dbg("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        frame_ctx = ctx->io_ctxs[IO_OUTPUT_CTX].frames_ctxs[index];
        buffer_ctx = ctx->io_ctxs[IO_OUTPUT_CTX].buffers_ctxs[index];

        pfm_memset(frame_ctx, 0, sizeof(vidc_frame_data_type));

        frame_ctx->buf_type = VIDC_BUFFER_OUTPUT;
        frame_ctx->frame_addr = buffer_ctx->buf_addr;
        frame_ctx->alloc_len = buffer_ctx->buf_size;
        frame_ctx->frm_clnt_data = index;

        rc = vidc_fill_frame(ctx, frame_ctx);
        if (EOK != rc) {
                log_err("Failed to fill output frame. Error: %d\n", rc);

                return rc;
        }

        log_dbg("Successfully filled output frame\n");

        return rc;
}

