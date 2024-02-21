/**
 **************************************************************************************************
 *  @file           : enc-state-api.h
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

#ifndef __ENC_STATE_API__H__
#define __ENC_STATE_API__H__

#include "enc-ctx.h"
#include "enc-state-types.h"

int wait_for_state(state_t state, enc_ctx_st_t *ctx);

void set_status(enc_ctx_st_t *ctx, status_t status);

#endif /* __ENC_STATE_API__H__ */

