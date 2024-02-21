/*====================================================================
* File: crc8.h
* Project: FW for VIP
* Function: CRC8 API and data structure
*====================================================================*/
/*
 *  Copyright (c) 2017, 2020-2022 Qualcomm Technologies, Inc and/or its subsidiaries.
 *  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc and/or its subsidiaries.
 */


#ifndef _CRC8_H
#define _CRC8_H

#include "crc.h"

/**
 * crc8_generate() -  Calculate CRC value
 * @param[in] buf:    Input data buffer pointer
 * @param[in] len:    length of the data buffer
 * @param[out] crc:   OUTPUT parameter that will contain the value of generated CRC result
 *
 * Used to generate a CRC value for specific data and length.
 *
 * @return:
 * @retval SUCCESS:   generate CRC successfully
 * @retval INVALID_PARAMETER:  parameter invalid
 */
error_type_crc crc8_generate(const char *buf, sl_size_t len, sl_u8_t *crc);

/**
 * crc8_verify() -  Verify CRC value
 * @param[in] buf:    Input data buffer pointer
 * @param[in] len:    Length of the data buffer
 * @param[in] crc:    The CRC that to be verified
 *
 * Used to verify the CRC value for specific data and length.
 *
 * @return:
 * @retval SUCCESS:   verify CRC successfully
 * @retval INVALID_PARAMETER:  parameter invalid
 * @retval CRC_ERROR:  Recalculated CRC mismatch with received CRC
 */
error_type_crc crc8_verify(const char *buf, sl_size_t len, sl_u8_t correct_crc);

#endif

