/**
 **************************************************************************************************
 *  @file           : enc-logger.c
 *  @brief          : Encoder logger API implementation
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder logger API implementation
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include <stdarg.h>
#include <stdio.h>

#include "enc-logger.h"
#include "enc-slog2.h"
#include "pfm-types.h"

static inline
void enc_printf(const char *fmt, va_list args)
{
        va_list args_tmp;

#ifndef CONFIG_DEBUG_STDOUT
        return;
#endif /* CONFIG_DEBUG_STDOUT */

        va_copy(args_tmp, args);

        (void)vprintf(fmt, args_tmp);

        va_end(args);
}

int enc_log_init(char *buffer_name)
{
        int rc = EOK;

        if (NULL == buffer_name) {
                log_err("Invalid input: buffer_name = %p\n", buffer_name);

                return EINVAL;
        }

#ifdef CONFIG_DEBUG_SLOGGER2
        rc = slog2_init(buffer_name);
        if (EOK != rc) {
                return rc;
        }
#endif /* CONFIG_DEBUG_SLOGGER2 */

        return rc;
}

void enc_log(verbose_level_t log_level, const char *fmt, ...)
{
        if (NULL == fmt) {
                log_err("Invalid input: fmt = %p\n", fmt);

                return;
        }

        va_list args;

        va_start(args, fmt);

        slog2_log2f(log_level, fmt, args);

        enc_printf(fmt, args);

        va_end(args);
}

