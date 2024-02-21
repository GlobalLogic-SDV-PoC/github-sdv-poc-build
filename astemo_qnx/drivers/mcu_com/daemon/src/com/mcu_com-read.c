/**
 **************************************************************************************************
 *  @file           : mcu_com-read.c
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

#include <pthread.h>

#include "mcu_com-logger.h"
#include "mcu_com-mem.h"
#include "mcu_com-msg.h"
#include "mcu_com-msg-handler.h"
#include "mcu_com-read.h"
#include "mcu_com-uart.h"

typedef struct read_ctx {
        pthread_t thread;
} read_ctx_st_t;

static
read_ctx_st_t mcu_read_ctx = {0};

static
void *read_thead(void *thread_data)
{
        mcu_com_err_t rc = MCU_COM_SUCCESS;
        uint8_t input_buff[MCU_COM_MESSAGE_LEN] = {0};
        mcu_com_msg_st_t *msg = NULL;
        int err = EOK;
        pthread_t thread = {0};

        (void)thread_data;

        while (1) {
                rc = mcu_com_uart_read(input_buff, MCU_COM_MESSAGE_LEN);
                if (MCU_COM_SUCCESS != rc) {
                        log_err("Failed to read message from MCU. Error: %s\n",
                                mcu_com_strerror(rc));

                        continue;
                }

                msg = alloc_data(1, mcu_com_msg_st_t);
                if (NULL == msg) {
                        log_err("Failed to allocate memory for input message\n");

                        continue;
                }

                rc = mcu_com_msg_deserialize(input_buff, msg);
                if (MCU_COM_SUCCESS != rc) {
                        log_err("Failed to decode message. Error: %s\n", mcu_com_strerror(rc));

                        clear_data(&msg);

                        continue;
                }

                /* memory for msg will be released in mcu_com_msg_handler thread */
                err = pthread_create(&thread, NULL, mcu_com_msg_handler, msg);
                if (EOK != err) {
                        log_err("Failed to start handler thread. Error: %s\n", strerror(errno));

                        clear_data(&msg);

                        continue;
                }

                err = pthread_detach(thread);
                if (EOK != err) {
                        log_err("Failed to detach handler thread. Error: %s\n", strerror(errno));

                        continue;
                }
        }

        return NULL;
}

mcu_com_err_t start_mcu_read_thread(void)
{
        mcu_com_err_t rc = MCU_COM_SUCCESS;
        int err = EOK;

        if (0 != mcu_read_ctx.thread) {
                log_err("Read thread already spawned\n");

                return rc;
        }

        err = pthread_create(&mcu_read_ctx.thread, NULL, read_thead, NULL);
        if (EOK != err) {
                log_err("Failed to start read thread. Error: %s\n", strerror(errno));

                return MCU_COM_INIT_FAILED;
        }

        log_info("MCU read thread spawned\n");

        return rc;
}

mcu_com_err_t finish_mcu_read_thread(void)
{
        int err = EOK;

        if (0 == mcu_read_ctx.thread) {
                log_err("Read thread already finished\n");

                return MCU_COM_SUCCESS;
        }

        err = pthread_cancel(mcu_read_ctx.thread);
        if (EOK != err) {
                log_err("Failed to cancel MCU read thread. Error: %s\n", strerror(errno));

                return MCU_COM_SYNC_ERROR;
        }

        return MCU_COM_SUCCESS;
}

mcu_com_err_t wait_for_mcu_read_thread_finish(void)
{
        int err = EOK;

        if (0 == mcu_read_ctx.thread) {
                log_err("Read thread already finished\n");

                return MCU_COM_SUCCESS;
        }

        err = pthread_join(mcu_read_ctx.thread, NULL);
        if (EOK != err) {
                log_err("Failed to join MCU read thread. Error: %s\n", strerror(errno));

                return MCU_COM_SYNC_ERROR;
        }

        mcu_read_ctx.thread = 0;

        log_info("MCU read thread joined\n");

        return MCU_COM_SUCCESS;
}

