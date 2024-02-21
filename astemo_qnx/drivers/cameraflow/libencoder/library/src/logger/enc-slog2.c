/**
 **************************************************************************************************
 *  @file           : enc-slog2.c
 *  @brief          : Slog2 logger wrappers implementation
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Slog2 logger wrappers implementation
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include <sys/slog2.h>

#include "enc-logger.h"
#include "enc-slog2.h"
#include "pfm-types.h"

#define SLOG2_DEFAULT_NUM_PAGES 256

static slog2_buffer_t slog2_buf_handler;

unsigned int get_slog2_level(verbose_level_t log_level)
{
        unsigned int slog_log_level = SLOG2_SHUTDOWN;

        switch (log_level) {
        case VERBOSE_LEVEL_NONE:
                slog_log_level = SLOG2_SHUTDOWN;
                break;
        case VERBOSE_LEVEL_ERR:
                slog_log_level = SLOG2_ERROR;
                break;
        case VERBOSE_LEVEL_INFO:
                slog_log_level = SLOG2_INFO;
                break;
        case VERBOSE_LEVEL_DBG:
                slog_log_level = SLOG2_DEBUG1;
                break;
        default:
                slog_log_level = SLOG2_DEBUG2;
        }

        return slog_log_level;
}

void slog2_log2f(verbose_level_t log_level, const char *fmt, va_list args)
{
        va_list args_tmp;

#ifndef CONFIG_DEBUG_SLOGGER2
        return;
#endif /* CONFIG_DEBUG_SLOGGER2 */

        if (NULL == fmt) {
                log_err("Invalid input: fmt = %p\n", fmt);

                return;
        }

        va_copy(args_tmp, args);

        vslog2f(slog2_buf_handler, 0, get_slog2_level(log_level), fmt, args);

        va_end(args);
}

int slog2_init(char *buffer_name)
{
        slog2_buffer_t temp_buffer_handler = NULL;
        slog2_buffer_set_config_t buffer_config;

        if (NULL == buffer_name) {
                return EINVAL;
        }

        temp_buffer_handler = slog2_find_buffer(buffer_name, NULL);
        if (NULL != temp_buffer_handler) {
                log_err("Buffer %s is already registered\n", buffer_name);

                slog2_buf_handler = temp_buffer_handler;

                return EOK;
        }

        buffer_config.buffer_set_name = buffer_name;
        buffer_config.num_buffers = 1;

#if defined(CONFIG_VERBOSE_LEVEL)
        buffer_config.verbosity_level =
                get_slog2_level((verbose_level_t)CONFIG_VERBOSE_LEVEL);
#else
        buffer_config.verbosity_level = SLOG2_DEBUG1;
#endif

        buffer_config.buffer_config[0].buffer_name = buffer_name;

#if defined(CONFIG_SLOG2_NUM_PAGES) && CONFIG_SLOG2_NUM_PAGES != 0
        buffer_config.buffer_config[0].num_pages = CONFIG_SLOG2_NUM_PAGES;
#else
        buffer_config.buffer_config[0].num_pages = SLOG2_DEFAULT_NUM_PAGES;
#endif

        if (EOK != slog2_register(&buffer_config,
                                  &slog2_buf_handler,
                                  SLOG2_DISCARD_NEWLINE)) {
                return EINVAL;
        }

        return EOK;
}

