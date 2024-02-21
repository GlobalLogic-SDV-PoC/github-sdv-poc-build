/**
 **************************************************************************************************
 *  @file           : xcp-logger.h
 *  @brief          : XCP logger API
 **************************************************************************************************
 *  @author     Oleksii Selivanov
 *
 *  @description:
 *      XCP logger API provides logger types with logger initialization, deinitializaton and
 *  output routines
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/

#ifndef __XCP_LOGGER__H__
#define __XCP_LOGGER__H__

#include <string.h>

/* The basename of the program being executed */
extern char *__progname;

#ifndef APP_NAME
#define APP_NAME __progname
#endif

#define FILE_NAME_NO_PATH(filepath)                                             \
        strrchr((filepath), '/') ? strrchr((filepath), '/') + 1 : (filepath)

#define LOG(log_level, msg, fmt, ...)                                           \
        xcp_logf(log_level, "|%s|[%s:%d:%s] %s" fmt, APP_NAME,                  \
                 FILE_NAME_NO_PATH(__FILE__), __LINE__, __func__,               \
                 msg, ## __VA_ARGS__);

#define log_info(fmt, ...)      LOG(LOG_INFO, "Info:", fmt, ## __VA_ARGS__)
#define log_err(fmt, ...)       LOG(LOG_ERROR, "Err:", fmt, ## __VA_ARGS__)
#define log_dbg(fmt, ...)       LOG(LOG_DEBUG, "Dbg:", fmt, ## __VA_ARGS__)

typedef enum {
        XCP_SUCCESS           = 0,
        XCP_INVALID_PARAMETER = -1,
        XCP_INIT_FAILED       = -4,
        XCP_SYNC_ERROR        = -5,
        XCP_UNKNOWN_ERROR     = -6,
} xcp_err_t;

typedef enum verbosity {
        LOG_ERROR = 0,
        LOG_INFO  = 1,
        LOG_DEBUG = 2,
} verbosity_t;

xcp_err_t xcp_logger_init(char *buffer_name);
xcp_err_t xcp_logger_deinit(char *buffer_name);

xcp_err_t xcp_logf(int verbosity, const char *fmt, ...);

#endif /* __XCP_LOGGER__H__ */

