/**
 **************************************************************************************************
 *  @file           : cmd-parser.h
 *  @brief          : Client application command line parser
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Client application command line parser
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __CMD_PARSER__H__
#define __CMD_PARSER__H__

#include "client-ctx.h"
#include "enc-ctx.h"

int parse_args(int argc, char **argv, client_ctx_st_t *ctx);
void print_usage(char *name);

#endif /* __CMD_PARSER__H__ */

