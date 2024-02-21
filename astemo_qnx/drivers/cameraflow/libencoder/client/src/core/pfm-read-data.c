/**
 **************************************************************************************************
 *  @file           : pfm-read-data.c
 *  @brief          : Frame reading from input file
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Frame reading from input file
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "MMFile.h"

#include "client-ctx.h"
#include "enc-ctx.h"
#include "enc-logger.h"
#include "pfm-file.h"
#include "pfm-queue.h"
#include "pfm-types.h"

void read_frame(client_ctx_st_t *ctx, char *buffer, bool *flag_eos, int *read_bytes)
{
        int read_bytes_y = 0;
        int read_bytes_uv = 0;
        int read_bytes_total = 0;
        int count_bytes_y = 0;
        int count_bytes_uv = 0;
        int count_bytes_total = 0;
        bool flag_eos_tmp = false;
        image_ctx_st_t *image_ctx = &ctx->image_ctx;
        file_ctx_st_t *file_ctx = &ctx->files[INPUT_FILE];

        /* Read plane Y */
        count_bytes_y = image_ctx->height * image_ctx->width;
        pfm_read_file(file_ctx, buffer, count_bytes_y, &read_bytes_y);
        if (read_bytes_y < count_bytes_y) {
                log_err("Failed to read plane Y. Read bytes : %d\n", read_bytes_y);

                flag_eos_tmp = true;
        }

        count_bytes_total += count_bytes_y;
        read_bytes_total += read_bytes_y;

        /* Read plane UV */
        buffer = (char *)buffer + (image_ctx->stride_y * image_ctx->height_y);
        count_bytes_uv = (image_ctx->height * image_ctx->width) / 2;
        pfm_read_file(file_ctx, buffer, count_bytes_uv, &read_bytes_uv);
        if (read_bytes_uv < count_bytes_uv) {
                log_err("Failed to read plane UV. Read bytes : %d\n", read_bytes_uv);

                flag_eos_tmp = true;
        }

        *flag_eos = flag_eos_tmp;

        count_bytes_total += count_bytes_uv;
        read_bytes_total += read_bytes_uv;

        *read_bytes = read_bytes_total;

        log_dbg("Read frame info :\n");
        log_dbg("read bytes total  : %d\n", read_bytes_total);
        log_dbg("eos flag          : %s\n", BOOL_STR(flag_eos_tmp));
}

