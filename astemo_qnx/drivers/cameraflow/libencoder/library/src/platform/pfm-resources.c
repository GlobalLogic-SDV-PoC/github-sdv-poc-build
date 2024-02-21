/**
 **************************************************************************************************
 *  @file           : pfm-resources.c
 *  @brief          : Platform resources API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      The allocation of all needed resources (queues, lists, signals, etc.) for the encoder
 *      library. Function with deallocation of all used resources.
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "MMCriticalSection.h"
#include "MMDebugMsg.h"
#include "MMFile.h"
#include "MMSignal.h"
#include "MMThread.h"
#include "MMTimer.h"

#include "enc-ctx.h"
#include "enc-logger.h"
#include "enc-vidc-converters.h"
#include "enc-vidc-headers.h"
#include "enc-vidc-ioctl.h"
#include "enc-vidc-properties-api.h"
#include "pfm-critical.h"
#include "pfm-stdlib.h"
#include "pfm-string.h"
#include "pfm-types.h"

int pfm_alloc_resources(enc_ctx_st_t *ctx)
{
        int rc = EOK;

        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        log_dbg("Try to allocate encoder resources\n");

        rc = pfm_lock_create(&ctx->lock);
        if (EOK != rc) {
                log_err("Failed to create main lock. Error: %d\n", rc);

                return rc;
        }

        rc = pfm_lock_create(&ctx->input_lock);
        if (EOK != rc) {
                log_err("Failed to create input lock. Error: %d\n", rc);

                return rc;
        }

        rc = pfm_lock_create(&ctx->output_lock);
        if (EOK != rc) {
                log_err("Failed to create output lock. Error: %d\n", rc);

                return rc;
        }

        rc = MM_SignalQ_Create(&ctx->input_signal_wait);
        if (EOK != rc) {
                log_err("Failed to create input signal queue. Error: %d\n", rc);

                return rc;
        }

        rc = MM_Signal_Create(ctx->input_signal_wait, NULL, NULL,
                              &ctx->input_signal);
        if (EOK != rc) {
                log_err("Failed to create input signal wait. Error: %d\n", rc);

                return rc;
        }

        rc = MM_SignalQ_Create(&ctx->output_signal_wait);
        if (EOK != rc) {
                log_err("Failed to create output signal queue. Error: %d\n",
                        rc);

                return rc;
        }

        rc = MM_Signal_Create(ctx->output_signal_wait, NULL, NULL,
                              &ctx->output_signal);
        if (EOK != rc) {
                log_err("Failed to create output signal wait. Error: %d\n", rc);

                return rc;
        }

        rc = MM_SignalQ_Create(&ctx->status_signal_wait);
        if (EOK != rc) {
                log_err("Failed to create status signal queue. Error: %d\n",
                        rc);

                return rc;
        }

        rc = MM_Signal_Create(ctx->status_signal_wait, NULL, NULL,
                              &ctx->status_signal);
        if (EOK != rc) {
                log_err("Failed to create status signal wait. Error: %d\n", rc);

                return rc;
        }

        ctx->input_queue = pfm_allocate_queue();
        if (NULL == ctx->input_queue) {
                log_err("Failed to allocate input queue\n");

                return ENOMEM;
        }

        ctx->output_queue = pfm_allocate_queue();
        if (NULL == ctx->output_queue) {
                log_err("Failed to allocate output queue\n");

                return ENOMEM;
        }

        log_dbg("Successfully allocated encoder resources\n");

        return EOK;
}

int pfm_free_resources(enc_ctx_st_t *ctx)
{
        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        log_dbg("Try to free encoder resources\n");

        pfm_lock_release(ctx->lock);
        pfm_lock_release(ctx->input_lock);
        pfm_lock_release(ctx->output_lock);
        MM_Signal_Release(ctx->input_signal);
        MM_SignalQ_Release(ctx->input_signal_wait);
        MM_Signal_Release(ctx->output_signal);
        MM_SignalQ_Release(ctx->output_signal_wait);
        MM_Signal_Release(ctx->status_signal);
        MM_SignalQ_Release(ctx->status_signal_wait);

        pfm_free_queue(ctx->input_queue);
        pfm_free_queue(ctx->output_queue);

        log_dbg("Successfully freed encoder resources\n");

        return EOK;
}

