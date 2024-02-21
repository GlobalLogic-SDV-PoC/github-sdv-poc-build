/**
 **************************************************************************************************
 *  @file           : pfm-file.h
 *  @brief          : Platform wrappers for file operation
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Platform wrappers for file operation
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __PFM_FILE__H__
#define __PFM_FILE__H__

#include "MMFile.h"

#include "pfm-types.h"

#define MAX_FILENAME    512

typedef struct file_ctx_st {
        char      name[MAX_FILENAME];
        MM_HANDLE fd;
        int       flags;
} file_ctx_st_t;

int pfm_create_file(file_ctx_st_t *ctx);
int pfm_release_file(file_ctx_st_t *ctx);

int pfm_write_file(file_ctx_st_t *ctx, char *buffer, uint32_t len, int32_t *written);
int pfm_read_file(file_ctx_st_t *ctx, char *buffer, uint32_t len, int32_t *read);

#endif /* __PFM_FILE__H__ */

