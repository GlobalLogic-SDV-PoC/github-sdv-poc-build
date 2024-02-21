/**
 **************************************************************************************************
 *  @file           : pfm-stdlib.c
 *  @brief          : Platform stdlib wrappers
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Platform stdlib wrappers
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include <stdlib.h>

#include "enc-logger.h"

void *pfm_calloc(size_t nmemb, size_t size)
{
        void *ptr = NULL;

        ptr = calloc(nmemb, size);
        if (NULL == ptr) {
                log_err("Failed to allocate memory\n");

                return NULL;
        }

        log_dbg("MEMORY CALLOC   ptr = [0x%p], size = [%08zd]\n", ptr, size);

        return ptr;
}

void pfm_free(void *ptr)
{
        log_dbg("MEMORY FREE     ptr = [0x%p]\n", ptr);

        free(ptr);
}

