/**
 **************************************************************************************************
 *  @file           : mcu_com-msg-handler.h
 **************************************************************************************************
 *  @author     Denys Sandrkin
 *
 *  @description:
 *      MCU communication manager message handler module invoke needed routines in accordance with
 *  message command from MCU and form responses to MCU
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/

#ifndef __MCU_COM_MSG_HANDLER__H__
#define __MCU_COM_MSG_HANDLER__H__

#include "mcu_com-error.h"

void *mcu_com_msg_handler(void *thread_data);

#endif /* __MCU_COM_MSG_HANDLER__H__ */

