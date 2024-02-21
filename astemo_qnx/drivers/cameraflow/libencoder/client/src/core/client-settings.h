/**
 **************************************************************************************************
 *  @file           : client-settings.h
 *  @brief          : Printing client settings
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Printing client settings header
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "client-ctx.h"

#ifndef __CLIENT_SETTINGS__H__
#define __CLIENT_SETTINGS__H__

void set_default_settings(client_ctx_st_t *ctx);
void print_settings(client_ctx_st_t *ctx);

#endif /* __CLIENT_SETTINGS__H__ */

