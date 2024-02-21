/**
 **************************************************************************************************
 *  @file           : mcu_com-error.h
 **************************************************************************************************
 *  @author     Denys Sandrkin
 *
 *  @description:
 *      MCU communication manager error codes and error codes conversion API
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/

#ifndef __MCU_COM_ERROR__H__
#define __MCU_COM_ERROR__H__

#define MCU_COM_SUCCESS_STR             "Success"
#define MCU_COM_INVALID_PARAMETER_STR   "Invalid parameter"
#define MCU_COM_OOM_STR                 "Out of memory"
#define MCU_COM_COMMUNICATION_ERR_STR   "Communication error"
#define MCU_COM_INIT_FAILED_STR         "Initialization failed"
#define MCU_COM_SYNC_ERR_STR            "Synchronization error"

#define MCU_COM_UNDEFINED_ERR_STR       "Undefined error"

typedef enum {
        MCU_COM_SUCCESS             = 0,
        MCU_COM_INVALID_PARAMETER   = -1,
        MCU_COM_OOM                 = -2,
        MCU_COM_COMMUNICATION_ERROR = -3,
        MCU_COM_INIT_FAILED         = -4,
        MCU_COM_SYNC_ERROR          = -5,
} mcu_com_err_t;

static inline
char *mcu_com_strerror(mcu_com_err_t err_code)
{
        switch (err_code) {
        case MCU_COM_SUCCESS:
                return MCU_COM_SUCCESS_STR;
        case MCU_COM_INVALID_PARAMETER:
                return MCU_COM_INVALID_PARAMETER_STR;
        case MCU_COM_OOM:
                return MCU_COM_OOM_STR;
        case MCU_COM_COMMUNICATION_ERROR:
                return MCU_COM_COMMUNICATION_ERR_STR;
        case MCU_COM_INIT_FAILED:
                return MCU_COM_INIT_FAILED_STR;
        case MCU_COM_SYNC_ERROR:
                return MCU_COM_SYNC_ERR_STR;
        default:
                return MCU_COM_UNDEFINED_ERR_STR;
        }
}

#endif /* __MCU_COM_ERROR__H__ */

