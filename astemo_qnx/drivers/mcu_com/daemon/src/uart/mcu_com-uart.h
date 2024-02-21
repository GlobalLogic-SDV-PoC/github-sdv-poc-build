/**
 **************************************************************************************************
 *  @file           : mcu_com-uart.h
 **************************************************************************************************
 *  @author     Denys Sandrkin
 *
 *  @description:
 *      MCU communication manager UART interface API
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/

#ifndef __MCU_COM_UART__H__
#define __MCU_COM_UART__H__

#include <stdint.h>

#include "mcu_com-error.h"

int mcu_com_uart_open(char *dev_name);
mcu_com_err_t mcu_com_uart_close(void);

mcu_com_err_t mcu_com_uart_read(uint8_t *buf, uint32_t len);
mcu_com_err_t mcu_com_uart_write(uint8_t *buf, uint32_t len);

#endif /* __MCU_COM_UART__H__ */

