/**
 **************************************************************************************************
 *  @file           : cam-logger.c
 *  @brief          : Logger API implementation
 **************************************************************************************************
 *  @authors     Vasyl Khursa
 *               Roman Hakh
 *
 *  @description:
 *      Logger API implementation. Logger supports slog2 and stdout output
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include <stdarg.h>
#include <stdio.h>

#include "cam-logger.h"
#include "cam-slog2.h"

#if defined(CONFIG_DEBUG_STDOUT)

static inline
void cam_printf(const char *fmt, va_list args)
{
        (void)vprintf(fmt, args);
}

#else /* CONFIG_DEBUG_STDOUT */

static inline
void cam_printf(const char *fmt, va_list args)
{
        (void)(fmt);
        (void)(args);
}

#endif /* CONFIG_DEBUG_STDOUT */

int cam_log_init(char *buffer_name)
{
        int rc = EOK;

        if (NULL == buffer_name) {
                fprintf(stderr, "Invalid input: buffer_name = %p\n", buffer_name);

                return EINVAL;
        }

        rc = slog2_init(buffer_name);
        if (EOK != rc) {
                return rc;
        }

        return rc;
}

int cam_log_deinit(void)
{
        return EOK;
}

void cam_log(verbose_level_t log_level, const char *fmt, ...)
{
        va_list args;

        if (NULL == fmt) {
                fprintf(stderr, "Invalid input: fmt = %p\n", fmt);

                return;
        }

        va_start(args, fmt);

        slog2_log2f(log_level, fmt, args);
        cam_printf(fmt, args);

        va_end(args);
}

