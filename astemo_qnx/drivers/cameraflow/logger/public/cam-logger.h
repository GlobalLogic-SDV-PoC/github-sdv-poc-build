/**
 **************************************************************************************************
 *  @file           : cam-logger.h
 *  @brief          : Logger API
 **************************************************************************************************
 *  @authors     Vasyl Khursa
 *               Roman Hakh
 *
 *  @description:
 *      Camera Data Flow logger API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __CAM_LOGGER__H__
#define __CAM_LOGGER__H__

#include <errno.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_APP_NAME    "libcamflow"

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

#define DEFAULT_LOG_TAG     "cam"

#ifndef LOG_TAG
#define LOG_TAG             DEFAULT_LOG_TAG
#endif

#define LOG(log_level, msg, fmt, ...)                                                              \
        do {                                                                                       \
                cam_log(log_level,                                                                 \
                        "|%s|[%s:%d:%s] %s" fmt,                                                   \
                        LOG_TAG,                                                                   \
                        FILE_NAME_NO_PATH(__FILE__),                                               \
                        __LINE__,                                                                  \
                        __func__,                                                                  \
                        msg,                                                                       \
                        ## __VA_ARGS__);                                                           \
        } while (0)

#define log_err(fmt, ...)       LOG(VERBOSE_LEVEL_ERR, "Err :", fmt, ## __VA_ARGS__)
#define log_info(fmt, ...)      LOG(VERBOSE_LEVEL_INFO, "Info:", fmt, ## __VA_ARGS__)
#define log_dgb(fmt, ...)       LOG(VERBOSE_LEVEL_DBG, "Dbg :", fmt, ## __VA_ARGS__)

void cam_log(verbose_level_t log_level, const char *fmt, ...);
int cam_log_init(char *buffer_name);
int cam_log_deinit(void);

#endif /* __CAM_LOGGER__H__ */

