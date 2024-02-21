/**
 **************************************************************************************************
 *  @file           : logger-x86.h
 *  @brief          : logger API
 **************************************************************************************************
 *  @author     Vitaliy Vasylskyy
 *
 *  @description:
 *      Substitution of xcp logger for x86 architecture that has no slog
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/

#pragma once

#include <string.h>
#define log(fmt, type, ...) \
        do { \
                printf("[%s:%d:%s] %s" fmt, __FILE__, __LINE__, __func__, \
                       type, ## __VA_ARGS__); \
        } while (0);

#define log_info(fmt, ...) log(fmt, "Inf:", ## __VA_ARGS__)
#define log_err(fmt, ...) log(fmt, "Err:", ## __VA_ARGS__)
#define log_dbg(fmt, ...) log(fmt, "Dbg:", ## __VA_ARGS__)

