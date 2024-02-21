/**
 **************************************************************************************************
 *  @file           : client-resources.h
 *  @brief          : Client resources API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Client resources API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __CLIENT_RESOURCES__H__
#define __CLIENT_RESOURCES__H__

#include "client-ctx.h"

int pfm_resourses_init(client_ctx_st_t *ctx);
void pfm_resourses_deinit(client_ctx_st_t *ctx);

int pfm_allocate_pmem_buffers(client_ctx_st_t *ctx);
void pfm_free_pmem_buffers(client_ctx_st_t *ctx);

#endif /* __CLIENT_RESOURCES__H__ */

