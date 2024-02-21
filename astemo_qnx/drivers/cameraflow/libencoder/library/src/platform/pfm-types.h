/**
 **************************************************************************************************
 *  @file           : pfm-types.h
 *  @brief          : Platform types
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Platform types
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __PFM_TYPES__H__
#define __PFM_TYPES__H__

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifndef EOK
#define EOK          0
#endif

#define ERROR        -1

#define MAX_LINE_LEN 1024

#define SAFE_STR(str)           (char *)((str) == NULL ? "(null)" : (str))
#define BOOL_STR(var)           (char *)((var) == true ? "true" : "false")

#endif /* __PFM_TYPES__H__ */

