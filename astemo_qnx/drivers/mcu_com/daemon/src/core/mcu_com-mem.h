/**
 **************************************************************************************************
 *  @file           : mcu_com-mem.h
 *  @brief          : mcu_com memory allocation API
 **************************************************************************************************
 *  @author     Denys Sandrkin
 *
 *  @description:
 *      MCU communication manager memory allocation and deallocation API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __MCU_COM_MEM__H__
#define __MCU_COM_MEM__H__

#include <stdlib.h>

#define alloc_data(count, type) (type *)calloc((count), sizeof(type))

static inline
void clear_data(void *buf)
{
        void **ptr = (void **)buf;

        if (NULL == ptr) {
                return;
        }

        free(*ptr);
        *ptr = NULL;
}

#endif /* __MCU_COM_MEM__H__ */

