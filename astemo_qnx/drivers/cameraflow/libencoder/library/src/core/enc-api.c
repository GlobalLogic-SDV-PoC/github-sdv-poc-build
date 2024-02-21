/**
 **************************************************************************************************
 *  @file           : enc-api.c
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

#include <unistd.h>

#include "MMSignal.h"

#include "enc-ctx.h"
#include "enc-logger.h"
#include "enc-state-api.h"
#include "enc-vidc-callback.h"
#include "enc-vidc-contexts-api.h"
#include "enc-vidc-converters.h"
#include "enc-vidc-frames-api.h"
#include "enc-vidc-headers.h"
#include "enc-vidc-ioctl.h"
#include "enc-vidc-properties-api.h"
#include "pfm-critical.h"
#include "pfm-resources.h"
#include "pfm-stdlib.h"
#include "pfm-string.h"
#include "pfm-types.h"

static
int enc_init_vidc(enc_ctx_st_t *ctx)
{
        int rc = EOK;

        log_dbg("Try to initialize VIDC driver\n");

        rc = vidc_open(ctx, vidc_callback);
        if (EOK != rc) {
                log_err("Failed to open VIDC driver. Error: %d\n", rc);

                return rc;
        }

        ctx->time_stamp_interval = ONE_MILIION / ctx->config.frame_rate;
        ctx->vidc_ctx.session_codec.session = VIDC_SESSION_ENCODE;
        ctx->vidc_ctx.session_codec.codec = ctx->config.codec;

        rc = vidc_set_properties(ctx);
        if (EOK != rc) {
                log_err("Failed to set VIDC properties. Error: %d\n", rc);

                return rc;
        }

        ctx->state = STATE_LOADED;

        rc = vidc_get_properties(ctx);
        if (EOK != rc) {
                log_err("Failed to get VIDC properties. Error: %d\n", rc);

                return rc;
        }

        log_dbg("Successfully initialized VIDC driver\n");

        return rc;
}

int enc_init(enc_ctx_st_t *ctx)
{
        int rc = EOK;

        log_dbg("Try to initialize encoder\n");

        rc = pfm_alloc_resources(ctx);
        if (EOK != rc) {
                log_err("Failed to allocate platform resource. Error: %d\n", rc);

                return rc;
        }

        rc = enc_init_vidc(ctx);
        if (EOK != rc) {
                log_err("Failed to initialize VIDC driver. Error: %d\n", rc);

                return rc;
        }

        log_dbg("Successfully initialized encoder\n");

        return rc;
}

static
int enc_deinit_vidc(enc_ctx_st_t *ctx)
{
        int rc = EOK;

        log_dbg("Try to de initialize VIDC driver\n");

        if (STATE_EXECUTING == ctx->state) {
                log_dbg("Send VIDC_IOCTL_STOP for stopping\n");

                rc = vidc_stop(ctx);
                if (EOK != rc) {
                        log_err("Failed to stop VIDC. Error: %d\n", rc);
                }

                rc = wait_for_state(STATE_IDLE, ctx);
                if (EOK != rc) {
                        log_err("Failed to wait STATE_IDLE state. Error: %d\n", rc);
                }

                rc = vidc_release_resourses(ctx);
                if (EOK != rc) {
                        log_err("Failed to release VIDC resources. Error: %d\n", rc);
                }

                rc = wait_for_state(STATE_LOADED, ctx);
                if (EOK != rc) {
                        log_err("Failed to wait STATE_LOADED state. Error: %d\n", rc);
                }
        }

        vidc_free_buffers_frames_ctxs(ctx);

        vidc_close(ctx);

        log_dbg("Successfully initialized VIDC driver\n");

        return rc;
}

void enc_deinit(enc_ctx_st_t *ctx)
{
        int rc = EOK;

        log_dbg("Try to de initialize encoder\n");

        rc = enc_deinit_vidc(ctx);
        if (EOK != rc) {
                log_err("Failed to de initialize VIDC driver. Error: %d\n");
        }

        rc = pfm_free_resources(ctx);
        if (EOK != rc) {
                log_err("Failed to clean resources. Error: %d\n");

                return;
        }

        log_dbg("Successfully de initialized encoder\n");
}

int enc_set_pmem_buffers(enc_ctx_st_t *ctx, pmem_buffers_ctx_st_t *buffers_ctx)
{
        int rc = EOK;

        log_dbg("Try to set PMEM buffers into theirs contexts\n");

        rc = vidc_allocate_buffers_frames_ctxs(ctx, buffers_ctx);
        if (EOK != rc) {
                log_err("Failed to allocate buffers/frames contexts. Error: %d\n", rc);

                return rc;
        }

        log_dbg("Successfully set PMEM buffers\n");

        return rc;
}

int enc_fill_output_buffers(enc_ctx_st_t *ctx)
{
        int rc = EOK;
        uint32 buff_idx = 0;

        log_dbg("Try to output frames\n");

        pfm_lock(ctx->output_lock);

        for (buff_idx = 0; buff_idx < ctx->io_ctxs[IO_OUTPUT_CTX].required_buffers; buff_idx++) {
                log_dbg("Try to fill buffer: %d\n", buff_idx);
                rc = vidc_fill_output_frame(ctx, buff_idx);
                if (EOK != rc) {
                        log_err("Failed to fill buffer [%d]. Error: %d\n", buff_idx, rc);

                        pfm_unlock(ctx->output_lock);

                        return rc;
                }
        }

        pfm_unlock(ctx->output_lock);

        log_dbg("Successfully filled output frames\n");

        return rc;
}

int enc_load_resources(enc_ctx_st_t *ctx)
{
        int rc = EOK;

        rc = vidc_load_resources(ctx);
        if (EOK != rc) {
                log_err("Failed to load VIDC resources. Error: %d\n", rc);

                return rc;
        }

        rc = vidc_start(ctx);
        if (EOK != rc) {
                log_err("Failed to start VIDC. Error: %d\n", rc);

                return rc;
        }

        rc = wait_for_state(STATE_EXECUTING, ctx);
        if (EOK != rc) {
                log_err("Failed to wait STATE_EXECUTING. Error: %d\n", rc);

                return rc;
        }

        log_dbg("Successfully loaded encoder\n");

        return rc;
}

int enc_start(enc_ctx_st_t *ctx)
{
        int rc = EOK;

        rc = enc_load_resources(ctx);
        if (EOK != rc) {
                log_err("Failed to load resources. Error: %d\n", rc);

                return rc;
        }

        rc = enc_fill_output_buffers(ctx);
        if (EOK != rc) {
                log_err("Failed to fill output buffers . Error: %d\n", rc);
        }

        return rc;
}

int enc_get_buffers_dimensions(enc_ctx_st_t *ctx, size_t *size, size_t *count, int buffer)
{
        *size = ctx->io_ctxs[buffer].reqmnts.size;
        *count = ctx->io_ctxs[buffer].reqmnts.actual_count;

        return EOK;
}

int enc_get_image_dimensions(enc_ctx_st_t *ctx, image_ctx_st_t *image_ctx)
{
        image_ctx->stride_y = ctx->vidc_ctx.plane_def_y.actual_stride;
        image_ctx->height_y = ctx->vidc_ctx.plane_def_y.actual_plane_buf_height;
        image_ctx->stride_uv = ctx->vidc_ctx.plane_def_uv.actual_stride;
        image_ctx->height_uv = ctx->vidc_ctx.plane_def_uv.actual_plane_buf_height;

        return EOK;
}

int enc_encode_wait(enc_ctx_st_t *ctx)
{
        int rc = EOK;
        int32 time_out = 0;

        pfm_lock(ctx->lock);

        while ((true != ctx->output_eos_flag) && (STATUS_ERROR != ctx->status)) {
                uint32 *arg = NULL;
                pfm_unlock(ctx->lock);

                time_out = 0;
                MM_SignalQ_TimedWait(ctx->status_signal_wait, WAIT_TIMEOUT_3_SEC, (void **)&arg,
                                     &time_out);

                log_dbg("Wait finish\n");
                log_dbg("time out       : %d\n", time_out);
                log_dbg("output EOS     : %s\n", BOOL_STR(ctx->output_eos_flag));
                log_dbg("obtained error : %s\n", (STATUS_ERROR == ctx->status) ? "true" : "false");

                if (1 == time_out) {
                        pfm_lock(ctx->lock);
                        break;
                }

                pfm_lock(ctx->lock);
        }

        log_dbg("Frames counters:\n");
        log_dbg("input frame count     : %d\n", ctx->input_frame_count);
        log_dbg("input frame obtained  : %d\n", ctx->input_frame_obtained);
        log_dbg("output frame obtained : %d\n", ctx->output_frame_obtained);

        pfm_unlock(ctx->lock);

        return rc;
}

