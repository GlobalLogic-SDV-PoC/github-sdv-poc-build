/**
 **************************************************************************************************
 *  @file           : enc-slog2.h
 *  @brief          : slog2 wrappers
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Slog2 logger wrappers for encoder application
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_SLOG2__H__
#define __ENC_SLOG2__H__

#include <stdarg.h>

#include "enc-logger.h"

int slog2_init(char *buffer_name);

unsigned int get_slog2_level(verbose_level_t log_level);

void slog2_log2f(verbose_level_t log_level, const char *fmt, va_list args);

#endif /* __ENC_SLOG2__H__ */

