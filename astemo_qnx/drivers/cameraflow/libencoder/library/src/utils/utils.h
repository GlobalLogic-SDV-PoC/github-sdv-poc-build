/**
 **************************************************************************************************
 *  @file           : utils.h
 *  @brief          : Utils API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Utils API for parsing command line, printing hex dump
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __UTILS__H__
#define __UTILS__H__

#include <stdbool.h>

bool same_key(char *str, const char *key);
int get_next_command(int argc, char **argv, int *position);
void log_hex_dump(char *data, int count);

#endif /* __UTILS__H__ */

