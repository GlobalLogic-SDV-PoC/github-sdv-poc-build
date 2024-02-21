/**
 **************************************************************************************************
 *  @file           : pfm-file.c
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

#include "MMFile.h"

#include "enc-logger.h"
#include "pfm-file.h"
#include "pfm-types.h"

int pfm_create_file(file_ctx_st_t *ctx)
{
        int rc = EOK;

        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        rc = MM_File_Create(ctx->name, ctx->flags, &ctx->fd);
        if (EOK != rc) {
                log_err("Failed to open file '%s'. Error: %d\n", ctx->name, rc);
        }

        return rc;
}

int pfm_release_file(file_ctx_st_t *ctx)
{
        int rc = EOK;

        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        rc = MM_File_Release(ctx->fd);
        if (EOK != rc) {
                log_err("Failed to release file '%s'. Error: %d\n", ctx->name, rc);
        }

        return rc;
}

int pfm_write_file(file_ctx_st_t *ctx, char *buffer, uint32_t length, int32_t *written)
{
        int rc = EOK;
        int32_t written_tmp = 0;

        if (NULL == ctx || NULL == buffer || NULL == written) {
                log_err("Invalid input: ctx = %p, buffer = %p, written = %p\n", ctx, buffer,
                        written);

                return EINVAL;
        }

        rc = MM_File_Write(ctx->fd, buffer, length, &written_tmp);
        if (EOK != rc) {
                log_err("Failed to write to file '%s'. Error: %d\n", ctx->name, rc);

                return rc;
        }

        log_dbg("Write to file: length = %d, written = %d\n", length, written_tmp);

        *written = written_tmp;

        return rc;
}

int pfm_read_file(file_ctx_st_t *ctx, char *buffer, uint32_t length, int32_t *read)
{
        int rc = EOK;
        int32_t read_tmp = 0;

        if (NULL == ctx || NULL == buffer || NULL == read) {
                log_err("Invalid input: ctx = %p, buffer = %p, read = %p\n", ctx, buffer, read);

                return EINVAL;
        }

        rc = MM_File_Read(ctx->fd, buffer, length, &read_tmp);
        if (EOK != rc) {
                log_err("Failed to read from file '%s'. Error: %d\n", ctx->name, rc);

                return rc;
        }

        log_dbg("Read from file: length = %d, read = %d\n", length, read_tmp);

        *read = read_tmp;

        return rc;
}

