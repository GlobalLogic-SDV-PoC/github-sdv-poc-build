/**
 **************************************************************************************************
 *  @file           : pfm-resources.h
 *  @brief          : Platform resources API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Platform resources API header
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __PFM_RESOURCES__H__
#define __PFM_RESOURCES__H__

#include "enc-ctx.h"

int pfm_alloc_resources(enc_ctx_st_t *ctx);
int pfm_free_resources(enc_ctx_st_t *ctx);

#endif /* __PFM_RESOURCES__H__ */

