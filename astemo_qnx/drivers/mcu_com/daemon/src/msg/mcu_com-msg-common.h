/**
 **************************************************************************************************
 *  @file           : mcu_com-msg-common.h
 **************************************************************************************************
 *  @author     Denys Sandrkin
 *
 *  @description:
 *      Common defines for message handling in MCU communication manager
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/

#ifndef __MCU_COM_MSG_COMMON__H__
#define __MCU_COM_MSG_COMMON__H__

#define MCU_COM_MESSAGE_LEN     16
#define MCU_COM_HEADER_LEN      4
#define MCU_COM_MSG_DATA_LEN    (MCU_COM_MESSAGE_LEN - MCU_COM_HEADER_LEN)

#endif /* __MCU_COM_MSG_COMMON__H__ */

