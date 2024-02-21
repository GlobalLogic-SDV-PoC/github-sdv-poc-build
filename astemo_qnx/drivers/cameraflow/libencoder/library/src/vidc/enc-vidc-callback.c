/**
 **************************************************************************************************
 *  @file           : enc-vidc-callback.c
 *  @brief          : Encoder VIDC callback
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder VIDC callback function
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "MMSignal.h"

#include "enc-ctx.h"
#include "enc-logger.h"
#include "enc-state-api.h"
#include "enc-vidc-converters.h"
#include "enc-vidc-headers.h"
#include "enc-vidc-printing-api.h"
#include "pfm-critical.h"
#include "pfm-string.h"
#include "pfm-types.h"

int vidc_callback(uint8_t *msg, uint32_t length, void *payload)
{
        (void)length;
        vidc_drv_msg_info_type *event = (vidc_drv_msg_info_type *)msg;
        enc_ctx_st_t *ctx = (enc_ctx_st_t *)payload;
        vidc_frame_data_type *frame_ctx = NULL;
        uint64_t index = 0;
        const size_t str_size = sizeof(vidc_frame_data_type);

        log_dbg("Event '%s' processing\n", vidc_event2str(event->event_type));

        switch (event->event_type) {
        case VIDC_EVT_RESP_FLUSH_INPUT_DONE:
                set_status(ctx, STATUS_INPUT_PORT_FLUSH_DONE);
                break;
        case VIDC_EVT_RESP_FLUSH_OUTPUT_DONE:
                set_status(ctx, STATUS_OUTPUT_PORT_FLUSH_DONE);
                break;
        case VIDC_EVT_RESP_INPUT_DONE:
                ctx->input_frame_obtained++;

                frame_ctx = &event->payload.frame_data;
                index = frame_ctx->frm_clnt_data;

                print_frame_ctx(frame_ctx);

                if (true == ctx->input_eos_flag) {
                        log_dbg("End of input stream detected\n");
                }

                pfm_memcpy(ctx->io_ctxs[IO_INPUT_CTX].frames_ctxs[index], frame_ctx, str_size);

                pfm_lock(ctx->input_lock);

                pfm_queue_push(ctx->input_queue, ctx->io_ctxs[IO_INPUT_CTX].frames_ctxs[index]);
                MM_Signal_Set(ctx->input_signal);

                pfm_unlock(ctx->input_lock);

                break;
        case VIDC_EVT_RESP_OUTPUT_DONE:
                ctx->output_frame_obtained++;

                frame_ctx = &event->payload.frame_data;
                index = frame_ctx->frm_clnt_data;

                print_frame_ctx(frame_ctx);

                if (frame_ctx->flags & VIDC_FRAME_FLAG_EOS) {
                        ctx->output_eos_flag = true;
                }

                if (true == ctx->output_eos_flag) {
                        log_dbg("End of output stream detected\n");
                }

                pfm_memcpy(ctx->io_ctxs[IO_OUTPUT_CTX].frames_ctxs[index], frame_ctx, str_size);

                pfm_lock(ctx->output_lock);

                pfm_queue_push(ctx->output_queue, ctx->io_ctxs[IO_OUTPUT_CTX].frames_ctxs[index]);
                MM_Signal_Set(ctx->output_signal);

                pfm_unlock(ctx->output_lock);

                break;
        case VIDC_EVT_RELEASE_BUFFER_REFERENCE:
        case VIDC_EVT_ERR_CLIENTFATAL:
        case VIDC_EVT_ERR_HWFATAL:
        case VIDC_EVT_INFO_OUTPUT_RECONFIG:
        case VIDC_EVT_INPUT_RECONFIG:
        case VIDC_EVT_OUTPUT_RECONFIG:
                log_err("Error event obtained\n");

                set_status(ctx, STATUS_ERROR);
                break;
        case VIDC_EVT_RESP_START:
                ctx->state = STATE_EXECUTING;
                break;
        case VIDC_EVT_RESP_STOP:
                ctx->state = STATE_IDLE;
                break;
        case VIDC_EVT_RESP_PAUSE:
                ctx->state = STATE_PAUSE;
                break;
        case VIDC_EVT_RESP_RESUME:
                ctx->state = STATE_EXECUTING;
                break;
        case VIDC_EVT_RESP_LOAD_RESOURCES:
                ctx->state = STATE_IDLE;
                break;
        case VIDC_EVT_RESP_RELEASE_RESOURCES:
                ctx->state = STATE_LOADED;
                break;
        default:
                log_err("Error event obtained\n");
                break;
        }

        return EOK;
}

