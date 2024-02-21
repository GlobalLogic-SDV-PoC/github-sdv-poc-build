/*====================================================================
* File: crc.h
* Project: FW for VIP
* Function: CRC common data structure
*====================================================================*/
/*
 *  Copyright (c) 2017, 2020-2022 Qualcomm Technologies, Inc and/or its subsidiaries.
 *  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc and/or its subsidiaries.
 */


#ifndef _CRC_H
#define _CRC_H

#include "sail_libs_types.h"

#ifndef DEBUG_PRINTF
#define DEBUG_PRINTF(...)
#endif

typedef enum {
    SUCCESS = 0x0,
    INVALID_PARAMETER1 = 0x111,
    CRC_ERROR = 0x222,
    SEQ_ERROR = 0x444,
    BOTH_CRC_SEQ_ERROR = 0x666
} error_type_crc;

#endif

