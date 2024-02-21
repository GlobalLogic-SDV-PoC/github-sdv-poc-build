/**
 **************************************************************************************************
 *  @file           : cam-slog2.c
 *  @brief          : Slog2 logger wrappers implementation
 **************************************************************************************************
 *  @authors     Vasyl Khursa
 *               Roman Hakh
 *
 *  @description:
 *      Slog2 logger wrappers implementation
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include <errno.h>
#include <sys/slog2.h>

#include "cam-logger.h"
#include "cam-slog2.h"

#if defined(CONFIG_DEBUG_SLOGGER2)

#define SLOG2_DEFAULT_NUM_PAGES 16

#if !defined(CONFIG_SLOG2_NUM_PAGES) || CONFIG_SLOG2_NUM_PAGES == 0
#define CONFIG_SLOG2_NUM_PAGES SLOG2_DEFAULT_NUM_PAGES
#endif

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
        va_list copy;

        if (NULL == fmt) {
                fprintf(stderr, "Invalid input: fmt = %p\n", fmt);

                return;
        }

        va_copy(copy, args);
        (void)vslog2f(slog2_buf_handler, 0, get_slog2_level(log_level), fmt, copy);

        va_end(copy);
}

int slog2_init(char *buffer_name)
{
        slog2_buffer_t temp_buffer_handler = NULL;
        slog2_buffer_set_config_t buffer_config = {0};
        int rc = EOK;

        if (NULL == buffer_name) {
                fprintf(stderr, "Invalid input: buffer_name = %p\n", buffer_name);

                return EINVAL;
        }

        temp_buffer_handler = slog2_find_buffer(buffer_name, NULL);
        if (NULL != temp_buffer_handler) {
                fprintf(stderr, "Buffer %s is already registered\n", buffer_name);

                slog2_buf_handler = temp_buffer_handler;

                return EOK;
        }

        buffer_config.buffer_set_name = buffer_name;
        buffer_config.num_buffers = 1;
        buffer_config.verbosity_level = SLOG2_DEBUG1;

#if defined(CONFIG_VERBOSE_LEVEL)
        buffer_config.verbosity_level =
                get_slog2_level((verbose_level_t)CONFIG_VERBOSE_LEVEL);
#endif

        buffer_config.buffer_config[0].buffer_name = buffer_name;
        buffer_config.buffer_config[0].num_pages = CONFIG_SLOG2_NUM_PAGES;

        rc = slog2_register(&buffer_config, &slog2_buf_handler, SLOG2_DISCARD_NEWLINE);
        if (EOK != rc) {
                return EINVAL;
        }

        return EOK;
}

#else /* CONFIG_DEBUG_SLOGGER2 */

unsigned int get_slog2_level(verbose_level_t log_level)
{
        (void)log_level;

        return EOK;
}

int slog2_init(char *buffer_name)
{
        (void)buffer_name;

        return EOK;
}

void slog2_log2f(verbose_level_t log_level, const char *fmt, va_list args)
{
        (void)log_level;
        (void)fmt;
        (void)args;
}

#endif /* CONFIG_DEBUG_SLOGGER2 */

