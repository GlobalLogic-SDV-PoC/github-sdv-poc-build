/**********************************************************************/
/* Copyright (C) 2022 by Hitachi Astemo, Ltd Japan                    */
/* All rights reserved.                                               */
/**********************************************************************/

/***********************************************************************
 * MODULE   : xcp.c
 * REMARKS  :
 * HISTORY  :
 * ID -- DATE ---- NAME ---- NOTE ------------------
 * [00]  22.04.15  T.Takami  Created
 * [01]  23.08.23  V.Vasylskyy  Ported to QC BSP
 **********************************************************************/

/**********************************************************************/
/* Include Files                                                      */
/**********************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "platform.h"
#include "xcp.h"
#include "xcpLite.h"
#include "xcpServer.h"
#include "xcp_lib.h"
#include "xcp-logger.h"

/**********************************************************************/
/* Macro Definition                                                   */
/**********************************************************************/
#define CLOCK_TICKS_PER_MS 1000000


/**********************************************************************/
/* Private Variable Definition                                        */
/**********************************************************************/
static uint16_t XcpEventList[MAX_XCP_EVENT_NUM];

/**
 * @brief Initialize XCP server
 *
 * @param [in] config Configuration parameters
 *
 * @param [in] event_num Number of events to be created
 *
 * @return true on success, false otherwise.
 */
bool XcpLib_Init(const T_XCP_CONFIG *config, uint8_t event_num)
{
        bool result = OK;
        xcp_err_t rc = XCP_SUCCESS;

        rc = xcp_logger_init(__progname);
        if (XCP_SUCCESS != rc) {
                /* Should we treat this as fatal error ? Perhaps no, just put the warning */
                fprintf(stderr,
                        "Warning! Could not register buffer for app: %s\n", __progname);
        }
        log_info("Log was initialized for application: %s\n", __progname);
        if (event_num < MAX_XCP_EVENT_NUM) {
                (void)clockInit();
                (void)XcpServerInit(NULL, config->PortNo, config->UseTcp);

                for (int32_t i = 0; i < event_num; i++) {
                        XcpEventList[i] = XcpCreateEvent(
                                                         config->Events[i].Name,
                                                         config->Events[i].CycleTimeMs *
                                                         CLOCK_TICKS_PER_MS,
                                                         config->Events[i].Priority, 0, 0);
                }
        } else {
                log_err("Event number (%d) exceeds maximum(%d)\n",
                        event_num, MAX_XCP_EVENT_NUM);
                (void)xcp_logger_deinit(__progname);
                result = NG;
        }

        return result;
}

/**
 * @brief Deinitialize XCP server
 *
 * @return true on success, false otherwise.
 */
bool XcpLib_Deinit(void)
{
        int ret = XCP_SUCCESS;

        ret = xcp_logger_deinit(__progname);
        if (XCP_SUCCESS != ret) {
                fprintf(stderr, "Could not deinit logger: %s\n", __progname);
        }

        return XcpServerShutdown();
}

/**
 * @brief Register XCP Event
 *
 * @param [in] event Event ID
 *
 * @return true on success, false otherwise.
 */
bool XcpLib_Event(uint8_t event)
{
        bool result = OK;

        if (event < MAX_XCP_EVENT_NUM) {
                XcpEvent(XcpEventList[event]);
        } else {
                result = NG;
        }

        return result;
}

T_CMD_HANDLER custom_cmd_handler = NULL;

/**
 * @brief Register pointer to XCP command handler
 *
 * @param [in] handler Function pointer to command handler
 *
 * @return true on success, false otherwise.
 */
bool XcpRegisterCommandHandler(T_CMD_HANDLER handler)
{
        if (handler != NULL) {
                custom_cmd_handler = handler;

                return TRUE;
        }

        log_err("Handler registration failed\n");

        return FALSE;
}

/**
 * @brief Unregister pointer to XCP command handler
 *
 * @param [in] handler Function pointer to command handler
 *
 * @return true on success, false otherwise.
 */
bool XcpUnregisterCommandHandler(T_CMD_HANDLER handler)
{
        if (handler == custom_cmd_handler) {
                custom_cmd_handler = NULL;

                return TRUE;
        }

        log_err("Handler unregister failed\n");

        return FALSE;
}

