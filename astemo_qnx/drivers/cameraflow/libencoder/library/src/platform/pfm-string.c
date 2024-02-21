/**
 **************************************************************************************************
 *  @file           : pfm-string.c
 *  @brief          : Platform string wrappers
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Platform string wrappers
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include <string.h>

void *pfm_memset(void *s, int c, size_t n)
{
        return memset(s, c, n);
}

void *pfm_memcpy(void *dest, const void *src, size_t n)
{
        return memcpy(dest, src, n);
}

