/**
 **************************************************************************************************
 *  @file           : xcp-logger.c
 *  @brief          : XCP logger API
 **************************************************************************************************
 *  @author     Oleksii Selivanov
 *
 *  @description:
 *      XCP logger API wraps the slog2 logger API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/

#include <sys/slog2.h>

#include <errno.h>
#include <stdint.h>

#include "xcp-logger.h"

#define LOGGER_NUM_PAGES   1
#define LOGGER_NUM_BUFFERS 1

#define LOGGER_VERBOSITY   SLOG2_DEBUG2

static slog2_buffer_t slog2_buf_handler;

static
xcp_err_t xcp_logger_find_buffer(char *buffer_name)
{
        slog2_buffer_t temp_buffer_handler = NULL;

        if (NULL == buffer_name) {
                fprintf(stderr, "Invalid input: buffer_name = %p\n", buffer_name);

                return XCP_INVALID_PARAMETER;
        }

        temp_buffer_handler = slog2_find_buffer(buffer_name, NULL);
        if (NULL != temp_buffer_handler) {
                slog2_buf_handler = temp_buffer_handler;

                return XCP_SUCCESS;
        }

        return XCP_INIT_FAILED;
}

static inline
uint64_t get_slog2_verbosity(verbosity_t verbosity)
{
        switch (verbosity) {
        case LOG_ERROR:
                return SLOG2_ERROR;
        case LOG_INFO:
                return SLOG2_INFO;
        case LOG_DEBUG:
        /* fall-through */
        default:
                return SLOG2_DEBUG1;
        }
}

xcp_err_t xcp_logger_deinit(char *buffer_name)
{
        (void)buffer_name;
        int ret = 0;

        ret = slog2_reset();
        if (0 == ret) {
                slog2_buf_handler = NULL;

                return XCP_SUCCESS;
        }

        return XCP_UNKNOWN_ERROR;
}

xcp_err_t xcp_logger_init(char *buffer_name)
{
        slog2_buffer_set_config_t buffer_config = {0};
        int ret = 0;

        if (NULL == buffer_name) {
                fprintf(stderr, "Invalid input: buffer_name = %p\n", buffer_name);

                return XCP_INVALID_PARAMETER;
        }

        ret = xcp_logger_find_buffer(buffer_name);
        if (XCP_SUCCESS == ret) { /* buffer already exists */
                return ret;
        }

        buffer_config.buffer_set_name = buffer_name;
        buffer_config.num_buffers = LOGGER_NUM_BUFFERS;
        buffer_config.verbosity_level = SLOG2_INFO;

        buffer_config.buffer_config[0].buffer_name = buffer_name;
        buffer_config.buffer_config[0].num_pages = LOGGER_NUM_PAGES;

        ret = slog2_register(&buffer_config, &slog2_buf_handler, SLOG2_DISCARD_NEWLINE);
        if (-1 == ret) {
                fprintf(stderr, "Failed to register slog2 buffer. Error: %s\n", strerror(errno));

                return XCP_INIT_FAILED;
        }

        slog2_set_verbosity(slog2_buf_handler, LOGGER_VERBOSITY);

        return XCP_SUCCESS;
}

xcp_err_t xcp_logf(int verbosity, const char *fmt, ...)
{
        uint64_t slog2_verbosity = SLOG2_DEBUG2;
        va_list args;

        if (NULL == fmt) {
                fprintf(stderr, "Invalid input: fmt = %p\n", fmt);

                return XCP_INVALID_PARAMETER;
        }

        if (NULL == slog2_buf_handler) {
                fprintf(stderr, "XCP Log subsystem was not properly initialized!\n");

                return XCP_INVALID_PARAMETER;
        }

        va_start(args, fmt);
        slog2_verbosity = get_slog2_verbosity(verbosity);
        vslog2f(slog2_buf_handler, 0, slog2_verbosity, fmt, args);
        va_end(args);

        return XCP_SUCCESS;
}

