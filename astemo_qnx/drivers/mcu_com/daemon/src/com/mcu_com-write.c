/**
 **************************************************************************************************
 *  @file           : mcu_com-uart-write.c
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

#include <errno.h>
#include <mqueue.h>
#include <pthread.h>
#include <string.h>

#include "mcu_com-error.h"
#include "mcu_com-logger.h"
#include "mcu_com-msg.h"
#include "mcu_com-uart.h"
#include "mcu_com-write.h"

#define MCU_COM_MQ_FOR_WRITE            "/mcu_com_write_mq"
#define MCU_COM_MQ_MAX_MSGS             256

#define MCU_COM_MQ_DEFAULT_PRIORITY     1

typedef struct write_ctx {
        pthread_t thread;
        mqd_t     mq;
} write_ctx_st_t;

static
write_ctx_st_t mcu_write_ctx = {0};

static
void *write_thread(void *thread_data)
{
        uint8_t received_msg[MCU_COM_MESSAGE_LEN] = {0};
        int ret = 0;
        mcu_com_err_t rc = MCU_COM_SUCCESS;

        (void)thread_data;

        while (1) {
                ret = mq_receive(mcu_write_ctx.mq, (char *)received_msg, MCU_COM_MESSAGE_LEN, NULL);
                if (-1 == ret) {
                        log_err("Failed to read message from message queue. Error: %s\n",
                                strerror(errno));

                        continue;
                }

                rc = mcu_com_uart_write(received_msg, MCU_COM_MESSAGE_LEN);
                if (MCU_COM_SUCCESS != rc) {
                        log_err("Failed to send message to MCU. Error: %s\n", mcu_com_strerror(rc));
                }

                memset(received_msg, 0, sizeof(uint8_t) * MCU_COM_MESSAGE_LEN);
        }

        return NULL;
}

mcu_com_err_t mcu_write(const mcu_com_msg_st_t *msg)
{
        int ret = 0;
        mcu_com_err_t rc = MCU_COM_SUCCESS;
        uint8_t serialized_msg[MCU_COM_MESSAGE_LEN] = {0};

        if (NULL == msg) {
                log_err("Invalid input: msg = %p\n", msg);

                return MCU_COM_INVALID_PARAMETER;
        }

        rc = mcu_com_msg_serialize(msg, serialized_msg);
        if (MCU_COM_SUCCESS != rc) {
                log_err("Failed to serialize message for MCU. Error: %s\n",
                        mcu_com_strerror(rc));

                return MCU_COM_COMMUNICATION_ERROR;
        }

        ret = mq_send(mcu_write_ctx.mq, (char *)serialized_msg, MCU_COM_MESSAGE_LEN,
                      MCU_COM_MQ_DEFAULT_PRIORITY);
        if (-1 == ret) {
                log_err("Failed to write message to message queue. Error: %s\n", strerror(errno));

                return MCU_COM_COMMUNICATION_ERROR;
        }

        return MCU_COM_SUCCESS;
}

mcu_com_err_t start_mcu_write_thread(void)
{
        mcu_com_err_t rc = MCU_COM_SUCCESS;
        int err = EOK;
        struct mq_attr attrs = {0};

        if (0 != mcu_write_ctx.thread) {
                log_err("Write thread already spawned\n");

                return rc;
        }

        attrs.mq_maxmsg = MCU_COM_MQ_MAX_MSGS;
        attrs.mq_msgsize = MCU_COM_MESSAGE_LEN;

        mcu_write_ctx.mq = mq_open(MCU_COM_MQ_FOR_WRITE, O_RDWR | O_CREAT,
                                   S_IRUSR | S_IWUSR, &attrs);
        if (-1 == mcu_write_ctx.mq) {
                log_err("Failed to create message queue. Error: %s\n", strerror(errno));

                return MCU_COM_INIT_FAILED;
        }

        err = pthread_create(&mcu_write_ctx.thread, NULL, write_thread, NULL);
        if (EOK != err) {
                log_err("Failed to start write thread. Error: %s\n", strerror(errno));

                err = mq_close(mcu_write_ctx.mq);
                if (-1 == err) {
                        log_err("Failed to close message queue. Error: %s\n", strerror(errno));
                }

                return MCU_COM_INIT_FAILED;
        }

        log_info("MCU write thread spawned\n");

        return rc;
}

mcu_com_err_t finish_mcu_write_thread(void)
{
        int err = EOK;

        err = pthread_cancel(mcu_write_ctx.thread);
        if (EOK != err) {
                log_err("Failed to cancel MCU write thread. Error: %s\n", strerror(errno));

                return MCU_COM_SYNC_ERROR;
        }

        return MCU_COM_SUCCESS;
}

mcu_com_err_t wait_for_mcu_write_thread_finish(void)
{
        int err = EOK;
        mcu_com_err_t rc = MCU_COM_SUCCESS;

        err = pthread_join(mcu_write_ctx.thread, NULL);
        if (EOK != err) {
                log_err("Failed to join MCU write thread. Error: %s\n", strerror(errno));

                rc = MCU_COM_SYNC_ERROR;
        }

        err = mq_close(mcu_write_ctx.mq);
        if (-1 == err) {
                log_err("Failed to close message queue. Error: %s\n", strerror(errno));

                rc = MCU_COM_INIT_FAILED;
        }

        mcu_write_ctx.thread = 0;
        mcu_write_ctx.mq = 0;

        if (MCU_COM_SUCCESS != rc) {
                return rc;
        }

        log_info("MCU write thread joined successfully\n");

        return rc;
}

