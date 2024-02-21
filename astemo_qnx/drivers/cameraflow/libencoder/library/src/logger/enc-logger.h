/**
 **************************************************************************************************
 *  @file           : enc-logger.h
 *  @brief          : Encoder logger API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder logger API wraps the slog2 logger API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_LOGGER__H__
#define __ENC_LOGGER__H__

#include <stdio.h>
#include <string.h>

#define DEFAULT_APP_NAME    "vidc_enc_app"

#ifndef APP_NAME
#define APP_NAME            DEFAULT_APP_NAME
#endif /* APP_NAME */

#define FILE_NAME_NO_PATH(filepath) strrchr((filepath), '/') ?                                      \
        strrchr((filepath), '/') + 1 : (filepath)

typedef enum verbose_level {
        VERBOSE_LEVEL_NONE,
        VERBOSE_LEVEL_FATAL_ERR,
        VERBOSE_LEVEL_CRIT_INFO,
        VERBOSE_LEVEL_ERR,
        VERBOSE_LEVEL_INFO,
        VERBOSE_LEVEL_DBG,
} verbose_level_t;

#define DEFAULT_LOG_TAG     "enc"

#ifndef LOG_TAG
#define LOG_TAG             DEFAULT_LOG_TAG
#endif

#define LOG(log_level, msg, fmt, ...)                                                               \
        do {                                                                                        \
                enc_log(log_level,                                                                  \
                        "|%s|[%s:%d:%s] %s" fmt,                                                    \
                        LOG_TAG,                                                                    \
                        FILE_NAME_NO_PATH(__FILE__),                                                \
                        __LINE__,                                                                   \
                        __func__,                                                                   \
                        msg,                                                                        \
                        ## __VA_ARGS__);                                                            \
        } while (0)

#define log_err(fmt, ...)  LOG(VERBOSE_LEVEL_ERR, "Err :", fmt, ## __VA_ARGS__)
#define log_info(fmt, ...) LOG(VERBOSE_LEVEL_INFO, "Info:", fmt, ## __VA_ARGS__)
#define log_dbg(fmt, ...)  LOG(VERBOSE_LEVEL_INFO, "Dbg :", fmt, ## __VA_ARGS__)

void enc_log(verbose_level_t log_level, const char *fmt, ...);
int enc_log_init(char *buffer_name);

#endif /* __ENC_LOGGER__H__ */

