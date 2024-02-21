/**
 **************************************************************************************************
 *  @file           : enc-error.h
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder error codes and error codes coversion API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_ERROR__H__
#define __ENC_ERROR__H__

#define ENC_SUCCESS_STR             "Success"
#define ENC_INVALID_PARAMETER_STR   "Invalid parameter"
#define ENC_OOM_STR                 "Out of memory"
#define ENC_COMMUNICATION_ERR_STR   "Communication error"
#define ENC_INIT_FAILED_STR         "Iniizalitaion failed"
#define ENC_SYNC_ERR_STR            "Synchronization error"
#define ENC_UNDEFINED_ERR_STR       "Undefined error"

typedef enum {
        ENC_SUCCESS             = 0,
        ENC_INVALID_PARAMETER   = -1,
        ENC_OOM                 = -2,
        ENC_COMMUNICATION_ERROR = -3,
        ENC_INIT_FAILED         = -4,
        ENC_SYNC_ERROR          = -5,
} enc_err_t;

static inline
char *enc_strerror(enc_err_t err_code)
{
        switch (err_code) {
        case ENC_SUCCESS:
                return ENC_SUCCESS_STR;
        case ENC_INVALID_PARAMETER:
                return ENC_INVALID_PARAMETER_STR;
        case ENC_OOM:
                return ENC_OOM_STR;
        case ENC_COMMUNICATION_ERROR:
                return ENC_COMMUNICATION_ERR_STR;
        case ENC_INIT_FAILED:
                return ENC_INIT_FAILED_STR;
        case ENC_SYNC_ERROR:
                return ENC_SYNC_ERR_STR;
        default:
                return ENC_UNDEFINED_ERR_STR;
        }
}

#endif /* __ENC_ERROR__H__ */

