/**
 **************************************************************************************************
 *  @file           : cam-slog2.h
 *  @brief          : slog2 wrappers
 **************************************************************************************************
 *  @authors     Vasyl Khursa
 *               Roman Hakh
 *
 *  @description:
 *      Slog2 logger wrappers, headers for camera flow library
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __CAM_SLOG2__H__
#define __CAM_SLOG2__H__

#include <stdarg.h>

#include "cam-logger.h"

unsigned int get_slog2_level(verbose_level_t log_level);
int slog2_init(char *buffer_name);
void slog2_log2f(verbose_level_t log_level, const char *fmt, va_list args);

#endif /* __CAM_SLOG2__H__ */

