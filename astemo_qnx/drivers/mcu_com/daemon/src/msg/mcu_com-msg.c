/**
 **************************************************************************************************
 *  @file           : mcu_com-msg.c
 **************************************************************************************************
 *  @author     Denys Sandrkin
 *
 *  @description:
 *      MCU communication manager message module decodes\encodes MCU messages from\to raw format
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/

#include <string.h>

#include "crc8.h"
#include "mcu_com-logger.h"
#include "mcu_com-msg.h"

mcu_com_err_t mcu_com_msg_deserialize(const uint8_t *in_msg, mcu_com_msg_st_t *out_msg)
{
        error_type_crc err = SUCCESS;

        if (NULL == in_msg || NULL == out_msg) {
                log_err("Invalid input: in_msg = %p, out_msg = %p\n", in_msg, out_msg);

                return MCU_COM_INVALID_PARAMETER;
        }

        err = crc8_verify((char *)&in_msg[MCU_COM_CMD_FIELD], MCU_COM_MESSAGE_LEN - 1,
                          in_msg[MCU_COM_CRC_FIELD]);
        if (SUCCESS != err) {
                log_err("Failed to verify CRC for MCU message. Error = %d\n", err);

                return MCU_COM_COMMUNICATION_ERROR;
        }

        out_msg->app_type = TO_APP_TYPE(in_msg[MCU_COM_CMD_FIELD]);
        out_msg->cmd = TO_CMD(in_msg[MCU_COM_CMD_FIELD]);
        out_msg->ret_code = in_msg[MCU_COM_RET_CODE_FIELD];
        out_msg->data_len = in_msg[MCU_COM_LEN_FIELD];

        memcpy(&out_msg->data, &in_msg[MCU_COM_DATA_FIELD], MCU_COM_MSG_DATA_LEN * sizeof(uint8_t));

        return MCU_COM_SUCCESS;
}

mcu_com_err_t mcu_com_msg_serialize(const mcu_com_msg_st_t *in_msg, uint8_t *out_msg)
{
        uint8_t buff[MCU_COM_MESSAGE_LEN] = {0};
        error_type_crc err = SUCCESS;

        if (NULL == in_msg || NULL == out_msg) {
                log_err("Invalid input: in_msg = %p, out_msg = %p\n", in_msg, out_msg);

                return MCU_COM_INVALID_PARAMETER;
        }

        buff[MCU_COM_CMD_FIELD] = TO_CMD_FIELD(in_msg->app_type, in_msg->cmd);
        buff[MCU_COM_RET_CODE_FIELD] = in_msg->ret_code;
        buff[MCU_COM_LEN_FIELD] = in_msg->data_len;
        memcpy(&buff[MCU_COM_DATA_FIELD], in_msg->data, MCU_COM_MSG_DATA_LEN * sizeof(uint8_t));

        err = crc8_generate((char *)&buff[MCU_COM_CMD_FIELD], MCU_COM_MESSAGE_LEN - 1,
                            &buff[MCU_COM_CRC_FIELD]);
        if (SUCCESS != err) {
                log_err("Failed to generate CRC for MCU message. Error = %d\n", err);

                return MCU_COM_COMMUNICATION_ERROR;
        }

        memcpy(out_msg, buff, sizeof(uint8_t) * MCU_COM_MESSAGE_LEN);

        return MCU_COM_SUCCESS;
}

