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

#include <pthread.h>

#include "lcm-control.h"

#include "mcu_com-logger.h"
#include "mcu_com-mem.h"
#include "mcu_com-msg.h"
#include "mcu_com-msg-handler.h"
#include "mcu_com-write.h"

#define MCU_COM_MAX_HANDLER_PRIORITY 255

static
mcu_com_err_t shutdown_req(void)
{
        pthread_t self = {0};
        struct sched_param param = {0};
        int policy = 0;
        int old_sched_priority = 0;
        int fd = 0;
        lcm_err_t lcm_rc = LCM_SUCCESS;
        mcu_com_err_t mcu_com_rc = MCU_COM_SUCCESS;

        self = pthread_self();

        pthread_getschedparam(self, &policy, &param);
        log_dbg("Current request handler priority: %d\n", param.sched_priority);
        old_sched_priority = param.sched_priority;
        param.sched_priority = SCHED_PRIO_LIMIT_SATURATE(MCU_COM_MAX_HANDLER_PRIORITY);
        pthread_setschedparam(self, policy, &param);

        pthread_getschedparam(self, &policy, &param);
        log_dbg("Increased request handler priority: %d\n", param.sched_priority);

        fd = lcm_control_open();
        if (fd < 0) {
                log_err("Failed to open LCM control interface\n");

                mcu_com_rc = MCU_COM_INIT_FAILED;

                goto exit_shutdown_req;
        }

        lcm_rc = lcm_control_shutdown(fd);
        if (LCM_SUCCESS != lcm_rc) {
                log_err("Failed to send shutdown signal to LCM\n");

                mcu_com_rc = MCU_COM_COMMUNICATION_ERROR;

                goto exit_shutdown_req;
        }

        lcm_rc = lcm_control_close(fd);
        if (LCM_SUCCESS != lcm_rc) {
                log_err("Failed to close LCM control interface\n");

                mcu_com_rc = MCU_COM_INIT_FAILED;

                goto exit_shutdown_req;
        }

        log_dbg("shutdown_req invoked\n");

exit_shutdown_req:
        param.sched_priority = old_sched_priority;
        pthread_setschedparam(self, policy, &param);

        pthread_getschedparam(self, &policy, &param);
        log_dbg("Returned back request handler priority: %d\n", param.sched_priority);

        return mcu_com_rc;
}

static
mcu_com_err_t process_startup_and_shutdown_msg(const mcu_com_msg_st_t *req_msg,
        mcu_com_msg_st_t *resp_msg)
{
        int rc = MCU_COM_SUCCESS;

        if (NULL == req_msg || NULL == resp_msg) {
                log_err("Invalid input: req_msg = %p, resp_msg = %p\n", req_msg, resp_msg);

                return MCU_COM_INVALID_PARAMETER;
        }

        resp_msg->data_len = 0;
        resp_msg->ret_code = MCU_RET_SUCCESS;
        resp_msg->app_type = STARTUP_AND_SHUTDOWN;

        switch (req_msg->cmd) {
        case SHUTDOWN_REQ:
                rc = shutdown_req();
                if (MCU_COM_SUCCESS != rc) {
                        log_err("Failed to process shutdown request. Error: %s\n",
                                mcu_com_strerror(rc));

                        resp_msg->ret_code = MCU_RET_ERROR;
                }

                resp_msg->cmd = SHUTDOWN_RESP;

                break;

        default:
                log_err("Invalid startup and shutdown command = %u\n", req_msg->cmd);

                rc = MCU_COM_COMMUNICATION_ERROR;
        }

        return rc;
}

void *mcu_com_msg_handler(void *thread_data)
{
        mcu_com_msg_st_t *request = NULL;
        mcu_com_msg_st_t response = {0};
        mcu_com_err_t rc = MCU_COM_SUCCESS;

        if (NULL == thread_data) {
                log_err("Invalid input: thread_data = %p\n", thread_data);

                return NULL;
        }

        request = (mcu_com_msg_st_t *)thread_data;

        switch (request->app_type) {
        case STARTUP_AND_SHUTDOWN:
                rc = process_startup_and_shutdown_msg(request, &response);
                if (MCU_COM_SUCCESS != rc) {
                        log_err("Failed to process startup and shutdown application type. "
                                "Error: %s\n", mcu_com_strerror(rc));
                }

                break;
        default:
                log_err("Invalid application type = %u\n", request->app_type);

                rc = MCU_COM_COMMUNICATION_ERROR;
        }

        if (MCU_COM_COMMUNICATION_ERROR == rc) {
                goto msg_handler_exit;
        }

        rc = mcu_write(&response);
        if (MCU_COM_SUCCESS != rc) {
                log_err("Failed to send message for MCU. Error: %s\n",
                        mcu_com_strerror(rc));

                goto msg_handler_exit;
        }

msg_handler_exit:
        clear_data(&request);

        return NULL;
}

