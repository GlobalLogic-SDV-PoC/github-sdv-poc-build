/**
 **************************************************************************************************
 *  @file           : pfm-stdlib.h
 *  @brief          : Platform stdlib wrappers header
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Platform stdlib wrappers header
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include <stdlib.h>

#ifndef __PFM_STDLIB__H__
#define __PFM_STDLIB__H__

void *pfm_calloc(size_t nmemb, size_t size);
void pfm_free(void *ptr);

#endif /* __PFM_STDLIB__H__ */

