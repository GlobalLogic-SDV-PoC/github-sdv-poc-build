/**
 **************************************************************************************************
 *  @file           : main.c
 *  @brief          : Encoder test client
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder test client
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#include "MMSignal.h"

#include "client-resources.h"
#include "client-settings.h"
#include "cmd-parser.h"
#include "enc-api.h"
#include "enc-ctx.h"
#include "enc-logger.h"
#include "enc-ops.h"
#include "enc-state-api.h"
#include "enc-vidc-callback.h"
#include "enc-vidc-contexts-api.h"
#include "enc-vidc-converters.h"
#include "enc-vidc-frames-api.h"
#include "enc-vidc-headers.h"
#include "enc-vidc-ioctl.h"
#include "enc-vidc-printing-api.h"
#include "enc-vidc-properties-api.h"
#include "pfm-critical.h"
#include "pfm-pmem.h"
#include "pfm-queue.h"
#include "pfm-read-data.h"
#include "pfm-resources.h"
#include "pfm-stdlib.h"
#include "pfm-string.h"
#include "pfm-types.h"

#define WAIT_TIMEOUT_1_MSEC  1
#define WAIT_TIMEOUT_10_MSEC 10

static
int client_app_init(int argc, char **argv, client_ctx_st_t *ctx)
{
        int rc = EOK;

        log_dbg("Try to initialize client application\n");

        set_default_settings(ctx);

        rc = enc_log_init(APP_NAME);
        if (EOK != rc) {
                printf("Failed to initialize logger. Error: %d\n", rc);

                return rc;
        }

        log_dbg("Build version: %s\n", BUILD_VERSION);

        pthread_setname_np(0, "main_thrd\n");

        rc = parse_args(argc, argv, ctx);
        if (EOK != rc) {
                printf("Failed to parse command line arguments. Error: %d", rc);

                print_usage(argv[0]);

                return rc;
        }

        print_settings(ctx);

        log_dbg("Successfully initialized client application\n");

        return rc;
}

static
void write_queue_data(client_ctx_st_t *ctx)
{
        int rc = EOK;
        enc_ctx_st_t *enc_ctx = &ctx->enc_ctx;
        vidc_frame_data_type *frame_ctx = NULL;
        static int processed_frames_counter = 0;
        int32_t written = 0;

        pfm_lock(enc_ctx->output_lock);
        frame_ctx = (vidc_frame_data_type *)pfm_queue_pop(enc_ctx->output_queue);
        pfm_unlock(enc_ctx->output_lock);

        if (NULL == frame_ctx) {
                log_err("Empty queue\n");
                return;
        }

        while (NULL != frame_ctx) {
                log_dbg("Processing output frame : %u\n", processed_frames_counter);

                print_frame_ctx(frame_ctx);

                if (VIDC_FRAME_FLAG_EOS != (frame_ctx->flags & VIDC_FRAME_FLAG_EOS)) {
                        rc = pfm_write_file(&ctx->files[OUTPUT_FILE],
                                            (char *)frame_ctx->frame_addr,
                                            frame_ctx->data_len, &written);
                        if (EOK != rc || frame_ctx->data_len != written) {
                                log_err("Failed to write to file. Error: %d\n", rc);

                                return;
                        }
                }

                rc = vidc_fill_frame(enc_ctx, frame_ctx);
                if (EOK != rc) {
                        log_err("Failed to fill output buffer. Error: %d\n", rc);
                }

                pfm_lock(enc_ctx->output_lock);
                frame_ctx = (vidc_frame_data_type *)pfm_queue_pop(enc_ctx->output_queue);
                pfm_unlock(enc_ctx->output_lock);

                processed_frames_counter++;
        }
}

int main(int argc, char **argv)
{
        int rc = EOK;
        bool flag_eos = false;
        client_ctx_st_t ctx = {0};
        enc_ctx_st_t *enc_ctx = &ctx.enc_ctx;

        printf("Run encoder test client. Version '%s'\n", SAFE_STR(BUILD_VERSION));

        rc = client_app_init(argc, argv, &ctx);
        if (EOK != rc) {
                log_err("Failed to initialize client application. Error: %d\n", rc);

                return rc;
        }

        log_dbg("Run encoder test client. Version '%s'\n", SAFE_STR(BUILD_VERSION));

        rc = pfm_resourses_init(&ctx);
        if (EOK != rc) {
                log_err("Failed to initialize client resources. Error: %d\n", rc);

                return rc;
        }

        /* Set encoder configuration */
        ctx.enc_ctx.config = ctx.config;

        rc = enc_init(&ctx.enc_ctx);
        if (EOK != rc) {
                log_err("Failed to initialize encoder. Error: %d\n", rc);

                goto fail_exit;
        }

        rc = get_encoder_parameters(&ctx);
        if (EOK != rc) {
                log_err("Failed to get encoder parameters. Error: %d\n", rc);

                goto fail_exit;
        }

        rc = pfm_allocate_pmem_buffers(&ctx);
        if (EOK != rc) {
                log_err("Failed to allocate PMEM buffers. Error: %d\n", rc);

                goto fail_exit;
        }

        rc = enc_set_pmem_buffers(&ctx.enc_ctx, ctx.pmem_buffers_ctxs);
        if (EOK != rc) {
                log_err("Failed to set buffers. Error: %d\n", rc);

                goto fail_exit;
        }

        rc = enc_start(&ctx.enc_ctx);
        if (EOK != rc) {
                log_err("Failed to start encoder. Error: %d\n", rc);

                goto fail_exit;
        }

        ctx.enc_ctx.input_frame_count = 0;

        /* Expected output frames count +1 for sequence header */
        ctx.enc_ctx.output_frame_count = 1;

        uint32_t *arg = NULL;
        int32_t time_out = 0;
        bool got_frame = false;
        int output_frame_count = 2; /* For first frame */
        for (int j = 0; j < ctx.enc_ctx.config.encode_frames; j++) {
                log_dbg("Try to read frame [%d] from file\n", j);

                if (j > 0) {
                         output_frame_count = 1;
                }

                ctx.enc_ctx.input_frame_count++;
                ctx.enc_ctx.output_frame_count++;

                int i = j % ctx.enc_ctx.config.input_buffers;

                char *buffer = ctx.pmem_buffers_ctxs[IO_INPUT_CTX].buffers[i];
                int read_bytes = 0;
                read_frame(&ctx, buffer, &flag_eos, &read_bytes);

                if (j == ctx.enc_ctx.config.encode_frames - 1) {
                        log_dbg("Last frame, set end of stream flag\n");

                        flag_eos = true;

                        /* Expected output frames count +1 for end of stream frame */
                        output_frame_count = 2;
                }

                rc = vidc_fill_input_frame(&ctx.enc_ctx, i, flag_eos, read_bytes);
                if (EOK != rc) {
                        log_err("Failed to encode frame [%d]. Error: %d\n", i, rc);

                        goto fail_exit;
                }

                /* Increase timestamp */
                ctx.enc_ctx.time_stamp_Lfile += ctx.enc_ctx.time_stamp_interval;

                /* Wait input frame processing */
                got_frame = false;
                while (true != got_frame) {
                        time_out = 0;
                        MM_SignalQ_TimedWait(enc_ctx->input_signal_wait, WAIT_TIMEOUT_1_MSEC,
                                             (void **)&arg, &time_out);
                        while (0 == time_out) {
                                got_frame = true;
                                break;
                        }
                }

                /* Wait output frame(s) */
                got_frame = false;
                while (true != got_frame) {
                        int output_frames_ready = 0;
                        time_out = 0;
                        MM_SignalQ_TimedWait(enc_ctx->output_signal_wait, WAIT_TIMEOUT_1_MSEC,
                                             (void **)&arg, &time_out);
                        while (0 == time_out) {
                                pfm_lock(enc_ctx->output_lock);

                                output_frames_ready = enc_ctx->output_queue->count;

                                pfm_unlock(enc_ctx->output_lock);

                                if (output_frame_count != output_frames_ready) {
                                        break;
                                }

                                got_frame = true;
                                break;
                        }

                        log_dbg("count output frame ready: %d", output_frames_ready);
                }

                write_queue_data(&ctx);
        }

        rc = enc_encode_wait(&ctx.enc_ctx);
        if (EOK != rc) {
                log_err("Failed to encode. Error: %d\n", rc);
        }

fail_exit:
        enc_deinit(&ctx.enc_ctx);

        pfm_resourses_deinit(&ctx);

        pfm_free_pmem_buffers(&ctx);

        printf("Finished with result: %d\n", rc);
        log_dbg("Finished with result: %d\n", rc);

        return rc;
}

