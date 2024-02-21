/**
 **************************************************************************************************
 *  @file           : pfm-string.h
 *  @brief          : Platform string wrappers header
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Platform string wrappers header
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __PFM_STRING__H__
#define __PFM_STRING__H__

#include <string.h>

void *pfm_memset(void *s, int c, size_t n);
void *pfm_memcpy(void *dest, const void *src, size_t n);

#endif /* __PFM_STRING__H__ */

