/**
 **************************************************************************************************
 *  @file           : mcu_com-uart.c
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

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>

#include "mcu_com-logger.h"
#include "mcu_com-mem.h"
#include "mcu_com-msg-common.h"
#include "mcu_com-uart.h"

#define MCU_COM_BAUD_RATE       115200
#define HEX_NUM_STR_FMT         "0x%x "
#define INVALID_FD              -1

typedef struct mcu_uart_ctx {
        int fd;
} uart_ctx_st_t;

static uart_ctx_st_t uart_ctx = {
        .fd = INVALID_FD,
};

static
void uart_print_dbg_msg(char *prefix, uint8_t *msg, int len)
{
        char buff[sizeof(HEX_NUM_STR_FMT)] = {0};
        int i = 0;
        char *log_print_buff = NULL;
        int print_buff_size = len * sizeof(HEX_NUM_STR_FMT);

        if (NULL == prefix || NULL == msg) {
                log_err("Invalid input: prefix = %p, msg = %p\n", prefix, msg);

                return;
        }

        log_print_buff = alloc_data(print_buff_size, char);
        if (NULL == log_print_buff) {
                log_err("Failed to allocate log_print_buff memory. Error: %s\n", strerror(errno));

                return;
        }

        for (i = 0; i < len; i++) {
                snprintf(buff, sizeof(HEX_NUM_STR_FMT), HEX_NUM_STR_FMT, msg[i]);
                strncat(log_print_buff,
                        buff, print_buff_size - (i * sizeof(HEX_NUM_STR_FMT)));
        }

        log_dbg("%s %s\n", prefix, log_print_buff);

        clear_data(&log_print_buff);
}

static
mcu_com_err_t uart_init(int fd)
{
        mcu_com_err_t rc = MCU_COM_SUCCESS;
        struct termios options = {0};
        speed_t baud = MCU_COM_BAUD_RATE;
        int err = EOK;

        err = fcntl(fd, F_SETFL, 0);
        if (err < 0) {
                log_err("Failed to reset file status flags, [fd = %d]. Error: %s\n", fd,
                        strerror(errno));

                return MCU_COM_INIT_FAILED;
        }

        err = tcgetattr(fd, &options);
        if (err < 0) {
                log_err("Failed to get MCU communication device attributes. Error: %s\n",
                        strerror(errno));

                return MCU_COM_INIT_FAILED;
        }

        options.c_cc[VMIN] = MCU_COM_MESSAGE_LEN; /* blocking until MCU_COM_MESSAGE_LEN received */
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= (CS8 | CLOCAL | CREAD);
        options.c_iflag &= IGNPAR;
        options.c_oflag = 0;
        options.c_lflag = 0;

        err = cfsetospeed(&options, baud);
        if (err < 0) {
                log_err("Failed to set MCU communication device output speed. Error: %s\n",
                        strerror(errno));

                return MCU_COM_INIT_FAILED;
        }

        err = cfsetispeed(&options, baud);
        if (err < 0) {
                log_err("Failed to set MCU communication device input speed. Error: %s\n",
                        strerror(errno));

                return MCU_COM_INIT_FAILED;
        }

        err = tcsetattr(fd, TCSANOW, &options);
        if (err < 0) {
                log_err("Failed to set MCU communication device attributes. Error: %s\n",
                        strerror(errno));

                return MCU_COM_INIT_FAILED;
        }

        return rc;
}

mcu_com_err_t mcu_com_uart_open(char *dev_name)
{
        mcu_com_err_t rc = MCU_COM_SUCCESS;
        int fd = 0;

        if (NULL == dev_name) {
                log_err("Invalid input: dev_name = %p\n", dev_name);

                return MCU_COM_INVALID_PARAMETER;
        }

        if (INVALID_FD != uart_ctx.fd) {
                log_info("MCU communication device already opened\n");

                return MCU_COM_SUCCESS;
        }

        fd = open(dev_name, O_RDWR | O_NOCTTY);
        if (INVALID_FD == fd) {
                log_err("Failed to open MCU communication device = %s. Error: %s\n", dev_name,
                        strerror(errno));

                return MCU_COM_INIT_FAILED;
        }

        rc = uart_init(fd);
        if (MCU_COM_SUCCESS != rc) {
                log_err("Failed to setup MCU communication device = %s. Error: %s\n", dev_name,
                        mcu_com_strerror(rc));

                close(fd);

                return rc;
        }

        uart_ctx.fd = fd;

        log_info("Opened MCU communication device = %s, fd = %d\n", dev_name, uart_ctx.fd);

        return rc;
}

mcu_com_err_t mcu_com_uart_close(void)
{
        mcu_com_err_t rc = MCU_COM_SUCCESS;
        int err = EOK;

        if (INVALID_FD != uart_ctx.fd) {
                log_info("MCU communication device already closed\n");

                return MCU_COM_SUCCESS;
        }

        err = close(uart_ctx.fd);
        if (err < 0) {
                log_err("Failed to close MCU communication device. Error: %s\n", strerror(errno));

                rc = MCU_COM_INIT_FAILED;
        }

        uart_ctx.fd = INVALID_FD;

        return rc;
}

mcu_com_err_t mcu_com_uart_read(uint8_t *buf, uint32_t len)
{
        mcu_com_err_t rc = MCU_COM_SUCCESS;
        int read_bytes = 0;

        if (NULL == buf || 0 == len) {
                log_err("Invalid input: buf = %p, len = %u\n", buf, len);

                return MCU_COM_INVALID_PARAMETER;
        }

        if (INVALID_FD == uart_ctx.fd) {
                log_err("MCU device is not initialized\n");

                return MCU_COM_INVALID_PARAMETER;
        }

        read_bytes = read(uart_ctx.fd, buf, len);
        if (read_bytes < len) {
                log_err("Failed to read from MCU. Error: %s. Expected amount of bytes = %d, "
                        "actually read = %d\n", strerror(errno), len, read_bytes);

                return MCU_COM_COMMUNICATION_ERROR;
        }

        uart_print_dbg_msg("Received:", buf, len);

        return rc;
}

mcu_com_err_t mcu_com_uart_write(uint8_t *buf, uint32_t len)
{
        mcu_com_err_t rc = MCU_COM_SUCCESS;
        int written_bytes = 0;

        if (NULL == buf) {
                log_err("Invalid input: buf = %p\n", buf);

                return MCU_COM_INVALID_PARAMETER;
        }

        if (INVALID_FD == uart_ctx.fd) {
                log_err("MCU device is not initialized\n");

                return MCU_COM_INVALID_PARAMETER;
        }

        written_bytes = write(uart_ctx.fd, buf, len);
        if (written_bytes != len) {
                log_err("Failed to write needed amount of bytes to MCU. "
                        "Expected = %d, actually written = %d \n", len, rc);

                return MCU_COM_COMMUNICATION_ERROR;
        }

        uart_print_dbg_msg("Sent:", buf, len);

        return rc;
}

