/**
 **************************************************************************************************
 *  @file           : mcu_com-logger.h
 *  @brief          : mcu_com logger API
 **************************************************************************************************
 *  @author     Denys Sandrkin
 *
 *  @description:
 *      MCU communication manager logger API provides logger types with logger initialization,
 *  deinitializaton and output routines
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/

#ifndef __MCU_COM_LOGGER__H__
#define __MCU_COM_LOGGER__H__

#include <string.h>

#include "mcu_com-error.h"

#define DEFAULT_APP_NAME "mcu_com"

#ifndef APP_NAME
#define APP_NAME DEFAULT_APP_NAME
#endif

#define FILE_NAME_NO_PATH(filepath)                                             \
        strrchr((filepath), '/') ? strrchr((filepath), '/') + 1 : (filepath)

#define LOG(log_level, msg, fmt, ...)                                           \
        mcu_com_logf(log_level, "|%s|[%s:%d:%s] %s" fmt, APP_NAME,              \
                     FILE_NAME_NO_PATH(__FILE__), __LINE__, __func__,           \
                     msg, ## __VA_ARGS__);

#define log_info(fmt, ...)      LOG(LOG_INFO, "Info:", fmt, ## __VA_ARGS__)
#define log_err(fmt, ...)       LOG(LOG_ERROR, "Err:", fmt, ## __VA_ARGS__)
#define log_dbg(fmt, ...)       LOG(LOG_DEBUG, "Dbg:", fmt, ## __VA_ARGS__)

typedef enum verbosity {
        LOG_ERROR = 0,
        LOG_INFO  = 1,
        LOG_DEBUG = 2,
} verbosity_t;

mcu_com_err_t mcu_com_logger_init(char *buffer_name);
mcu_com_err_t mcu_com_logger_deinit(char *buffer_name);

mcu_com_err_t mcu_com_logf(int verbosity, const char *fmt, ...);

#endif /* __MCU_COM_LOGGER__H__ */

