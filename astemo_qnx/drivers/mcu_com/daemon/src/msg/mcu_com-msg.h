/**
 **************************************************************************************************
 *  @file           : mcu_com-msg.h
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

#ifndef __MCU_COM_MSG__H__
#define __MCU_COM_MSG__H__

#include <stdint.h>

#include "mcu_com-error.h"
#include "mcu_com-msg-common.h"

#define MCU_COM_CRC_FIELD       0
#define MCU_COM_CMD_FIELD       1
#define MCU_COM_RET_CODE_FIELD  2
#define MCU_COM_LEN_FIELD       3
#define MCU_COM_DATA_FIELD      4

#define TO_APP_TYPE(x)          ((x) >> 4)
#define TO_CMD(x)               ((x) & 0x0F)
#define TO_CMD_FIELD(app, cmd)  (((app) << 4) | (cmd))

typedef enum mcu_com_app_type {
        STARTUP_AND_SHUTDOWN        = 0x01,
        VEHICLE_INFORMATION_STORAGE = 0x02,
} mcu_com_app_type_t;

typedef enum mcu_com_sas_cmd { /* sas is for app type STARTUP_AND_SHUTDOWN */
        SER_CONFIG_CHANGE_REQ    = 0x01,
        SER_CONFIG_CHANGE_RESP   = 0x01,
        DESER_CONFIG_CHANGE_REQ  = 0x03,
        DESER_CONFIG_CHANGE_RESP = 0x04,
        SHUTDOWN_REQ             = 0x05,
        SHUTDOWN_RESP            = 0x06,
        CAM_STARTUP_CONFIRM_REQ  = 0x07,
        CAM_STARTUP_CONFIRM_RESP = 0x08,
} mcu_com_sas_cmd_t;

typedef enum mcu_com_vis_cmd { /* vis is for app type VEHICLE_INFORMATION_STORAGE */
        MBU_INF_REQ  = 0x01,
        MBU_INF_RESP = 0x02,
        EDR_INF_REQ  = 0x03,
        EDR_IFN_RESP = 0x04,
} mcu_com_vis_cmd_t;

typedef enum mcu_com_ret {
        MCU_RET_SUCCESS = 0x00,
        MCU_RET_ERROR   = 0x01,
} mcu_com_ret_t;

typedef struct mcu_com_msg {
        uint8_t app_type;
        uint8_t cmd;
        uint8_t ret_code;
        uint8_t data_len;
        uint8_t data[MCU_COM_MSG_DATA_LEN];
} mcu_com_msg_st_t;

mcu_com_err_t mcu_com_msg_deserialize(const uint8_t *in_msg, mcu_com_msg_st_t *out_msg);
mcu_com_err_t mcu_com_msg_serialize(const mcu_com_msg_st_t *in_msg, uint8_t *out_msg);

#endif /* __MCU_COM_MSG__H__ */

