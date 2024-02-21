/**
 **************************************************************************************************
 *  @file           : mcu_com-write.h
 **************************************************************************************************
 *  @author     Denys Sandrkin
 *
 *  @description:
 *      MCU communication manager write module gathers response messages from different
 *  applications and sends them to MCU
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/

#ifndef __MCU_COM_WRITE__H__
#define __MCU_COM_WRITE__H__

#include "mcu_com-error.h"
#include "mcu_com-msg.h"

mcu_com_err_t mcu_write(const mcu_com_msg_st_t *msg);

mcu_com_err_t start_mcu_write_thread(void);
mcu_com_err_t finish_mcu_write_thread(void);
mcu_com_err_t wait_for_mcu_write_thread_finish(void);

#endif /* __MCU_COM_WRITE__H__ */

