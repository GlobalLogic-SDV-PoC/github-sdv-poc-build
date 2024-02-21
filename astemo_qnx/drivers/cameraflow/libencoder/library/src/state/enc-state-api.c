/**
 **************************************************************************************************
 *  @file           : enc-state-api.c
 *  @brief          : Encoder state API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder state API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "MMSignal.h"
#include "MMTimer.h"

#include "enc-ctx.h"
#include "enc-logger.h"
#include "enc-state-types.h"
#include "enc-vidc-headers.h"
#include "pfm-critical.h"

int wait_for_state(state_t state, enc_ctx_st_t *ctx)
{
        size_t counter = 0;

        while (ctx->state != state) {
                MM_Timer_Sleep(ONE);
                counter++;

                if (counter > TIMEOUT_CNT) {
                        log_err("Wait state timeout\n");

                        return ERROR;
                }
        }

        return EOK;
}

void set_status(enc_ctx_st_t *ctx, status_t status)
{
        pfm_lock(ctx->lock);
        ctx->status = status;
        MM_Signal_Set(ctx->status_signal);
        pfm_unlock(ctx->lock);
}

