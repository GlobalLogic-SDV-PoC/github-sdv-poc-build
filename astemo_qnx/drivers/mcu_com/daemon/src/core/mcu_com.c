/**
 **************************************************************************************************
 *  @file           : mcu_com.c
 *  @brief          : MCU communication manager main routine
 **************************************************************************************************
 *  @author     Denys Sandrkin
 *
 *  @description:
 *    The main process initializes necessary MCU communication manager resources and starts message
 *  handling thread(s)
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/

#include <errno.h>
#include <getopt.h>
#include <stdint.h>
#include <string.h>
#include <sys/procmgr.h>

#include "mcu_com-logger.h"
#include "mcu_com-read.h"
#include "mcu_com-uart.h"
#include "mcu_com-write.h"

#define DEVICE_NAME_LONG   "dev"

#define DEVICE_NAME_SHORT  'd'

#define DEFAULT_SERIAL_DEVICE "/dev/ser3"

typedef struct param_ctx {
        char device_name[UINT8_MAX];
} param_ctx_st_t;

static
struct option longopts[] = {
        {DEVICE_NAME_LONG, required_argument, NULL, DEVICE_NAME_SHORT},
        {NULL,                             0, NULL,                 0}
};

static
mcu_com_err_t process_cmdline(param_ctx_st_t *ctx, int argc, char **argv)
{
        int opt = -1;
        int longindex = 0;

        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return MCU_COM_INVALID_PARAMETER;
        }

        while ((opt = getopt_long(argc, argv, "d:", longopts, &longindex)) != -1) {
                switch (opt) {
                case DEVICE_NAME_SHORT:
                        strcpy(ctx->device_name, optarg);
                        break;
                default:
                        log_err("Invalid input parameter = %c\n", opt);

                        return MCU_COM_INVALID_PARAMETER;
                }
        }

        return MCU_COM_SUCCESS;
}

int main(int argc, char *argv[])
{
        mcu_com_err_t rc = MCU_COM_SUCCESS;
        int err = EOK;
        param_ctx_st_t input_params = {
                .device_name = DEFAULT_SERIAL_DEVICE,
        };

        rc = mcu_com_logger_init(APP_NAME);
        if (MCU_COM_SUCCESS != rc) {
                return rc;
        }

        log_info("mcu_com started\n");

        rc = process_cmdline(&input_params, argc, argv);
        if (MCU_COM_SUCCESS != rc) {
                log_err("Failed to parse input parameters. Error: %s\n", mcu_com_strerror(rc));

                goto daemon_exit;
        }

        err = procmgr_daemon(0, PROCMGR_DAEMON_NODEVNULL);
        if (-1 == err) {
                log_err("Failed to daemonize. Error: %s\n", strerror(errno));

                rc = MCU_COM_INIT_FAILED;

                goto daemon_exit;
        }

        log_info("mcu_com daemonized\n");

        rc = mcu_com_uart_open(input_params.device_name);
        if (MCU_COM_SUCCESS != rc) {
                log_err("Failed to open serial device. Error: %s\n", mcu_com_strerror(rc));

                goto daemon_exit;
        }

        rc = start_mcu_read_thread();
        if (MCU_COM_SUCCESS != rc) {
                log_err("Failed to start read thread. Error: %s\n", mcu_com_strerror(rc));

                goto close_uart_and_exit;
        }

        rc = start_mcu_write_thread();
        if (MCU_COM_SUCCESS != rc) {
                log_err("Failed to start write thread. Error: %s\n", mcu_com_strerror(rc));

                goto close_read_and_exit;
        }

        rc = wait_for_mcu_write_thread_finish();
        if (MCU_COM_SUCCESS != rc) {
                log_err("Failed to finish write thread. Error: %s\n", mcu_com_strerror(rc));

                goto close_read_and_exit;
        }

close_read_and_exit:
        rc = wait_for_mcu_read_thread_finish();
        if (MCU_COM_SUCCESS != rc) {
                log_err("Failed to finish read thread. Error: %s\n", mcu_com_strerror(rc));

                goto close_uart_and_exit;
        }

close_uart_and_exit:
        rc = mcu_com_uart_close();
        if (MCU_COM_SUCCESS != rc) {
                log_err("Failed to close serial device. Error: %s\n", mcu_com_strerror(rc));

                goto daemon_exit;
        }

daemon_exit:
        rc = mcu_com_logger_deinit(APP_NAME);
        if (MCU_COM_SUCCESS != rc) {
                return rc;
        }

        return rc;
}

