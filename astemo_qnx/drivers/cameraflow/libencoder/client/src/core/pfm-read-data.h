/**
 **************************************************************************************************
 *  @file           : pfm-read-data.h
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

#ifndef __PFM_READ_DATA__H__
#define __PFM_READ_DATA__H__

#include "client-ctx.h"
#include "enc-ctx.h"

void read_frame(client_ctx_st_t *ctx, char *buffer, bool *flag_eos, int *read_bytes);

#endif /* __READ_DATA_H__ */

