/**
 **************************************************************************************************
 *  @file           : mcu_com-read.h
 **************************************************************************************************
 *  @author     Denys Sandrkin
 *
 *  @description:
 *      MCU communication manager read module reads input messages from MCU and forwards them for
 *  processing
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/

#ifndef __MCU_COM_READ__H__
#define __MCU_COM_READ__H__

#include "mcu_com-error.h"

mcu_com_err_t start_mcu_read_thread(void);
mcu_com_err_t finish_mcu_read_thread(void);
mcu_com_err_t wait_for_mcu_read_thread_finish(void);

#endif /* __MCU_COM_READ__H__ */

