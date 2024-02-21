/*====================================================================
* File: sail_libs_types.h
* Project: FW for VIP
* Function: SAIL data type libraries
*====================================================================*/
/*
 *  Copyright (c) 2017, 2020-2022 Qualcomm Technologies, Inc and/or its subsidiaries.
 *  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc and/or its subsidiaries.
 */


#ifndef _SAIL_LIBS_TYPES_H
#define _SAIL_LIBS_TYPES_H

/**
 * Since safetylib modules are running on different OSes and
 * architectures, data type size should be taken carefully.
 * Luckily, C language makes sure the minimum data type size.
 * For instance, short is at least 16 bits long.
 * "int" is at lease 16 bit long in C language. In most cases,
 * "int" is 32 bits long. If not, please add a #define INT_16BIT
 *
 */

typedef unsigned long long  sl_u64_t;
typedef signed long long    sl_s64_t;
typedef unsigned short      sl_u16_t;
typedef signed short        sl_s16_t;
typedef unsigned char       sl_u8_t;
typedef signed char         sl_s8_t;
#ifdef INT_16BIT
typedef unsigned long       sl_u32_t;
typedef signed long         sl_s32_t;
typedef unsigned long       sl_size_t;
#else
typedef unsigned int        sl_u32_t;
typedef signed int          sl_s32_t;
typedef unsigned int        sl_size_t;
#endif

#ifndef NULL
#define NULL 0U
#endif

#endif

