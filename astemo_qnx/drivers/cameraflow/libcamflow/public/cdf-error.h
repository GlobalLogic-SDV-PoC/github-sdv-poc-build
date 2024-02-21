/**
 **************************************************************************************************
 *  @file           : cdf-error.h
 **************************************************************************************************
 *  @author     Roman Kovalivskyi
 *
 *  @description:
 *  CDF error codes and error codes coversion API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
*
 **************************************************************************************************
 **/

#ifndef __CDF_ERROR__H__
#define __CDF_ERROR__H__

#define CDF_OK_STR                  "OK"
#define CDF_INVALID_PARAMETER_STR   "Invalid parameter"
#define CDF_OOM_STR                 "Out of memory"
#define CDF_BUFFER_NOT_FOUND_STR    "Framebuffer not found"
#define CDF_UNDEFINED_ERR_STR       "Undefined error"

typedef enum {
        CDF_OK                = 0,
        CDF_INVALID_PARAMETER = -1,
        CDF_OOM               = -2,
        CDF_BUFFER_NOT_FOUND  = -3,
} cdf_err_t;

static inline
const char *cdf_strerror(cdf_err_t err_code)
{
        switch (err_code) {
        case CDF_OK:
                return CDF_OK_STR;
        case CDF_INVALID_PARAMETER:
                return CDF_INVALID_PARAMETER_STR;
        case CDF_OOM:
                return CDF_OOM_STR;
        case CDF_BUFFER_NOT_FOUND:
                return CDF_BUFFER_NOT_FOUND_STR;
        default:
                return CDF_UNDEFINED_ERR_STR;
        }
}

#endif /* __CDF_ERROR__H__ */

