/**********************************************************************/
/* Copyright (C) 2022 by Hitachi Astemo, Ltd Japan                    */
/* All rights reserved.                                               */
/**********************************************************************/

/***********************************************************************
 * MODULE   : xcp_lib.h
 * REMARKS  :
 * HISTORY  :
 * ID -- DATE ---- NAME ---- NOTE ------------------
 * [00]  22.04.15  T.Takami  Created
 * [01]  23.08.23  V.Vasylskyy  Ported to QC BSP
 **********************************************************************/
#pragma once

#include <stdbool.h>

/**********************************************************************/
/* Macro Definition                                                   */
/**********************************************************************/
#define MAX_XCP_EVENT_NAME 20
#define MAX_XCP_EVENT_NUM  40
#define NG false
#define OK true

/* Custom Command Return Error Code */
#define CMD_NOT_SUPPORTED 255

/**********************************************************************/
/* Struct Definition                                                  */
/**********************************************************************/
typedef struct {
        uint16_t PortNo; /* Port Number */
        bool     UseTcp; /* TRUE:TCP, FALSE:UDP */
        struct {
                const char Name[MAX_XCP_EVENT_NAME];
                uint16_t   CycleTimeMs;
                uint8_t    Priority; /*0:Lowest, 255:Highest */
        } Events[MAX_XCP_EVENT_NUM];
} T_XCP_CONFIG;

typedef struct {
        char *name;
        uint32_t startAddr;
        uint32_t size;
}XCP_REPRO_SEGMENT;

/* Function pointer for custom command handler */
typedef uint8_t (*T_CMD_HANDLER)(const uint8_t *cmd, uint16_t cmd_len,
        uint32_t addr, uint8_t *reply, uint8_t *reply_len);

/**********************************************************************/
/* Prototype Declaration                                              */
/**********************************************************************/
bool XcpLib_Init(const T_XCP_CONFIG *config, uint8_t event_num);
bool XcpLib_Event(uint8_t event);
bool XcpRegisterCommandHandler(T_CMD_HANDLER handler);
bool XcpUnregisterCommandHandler(T_CMD_HANDLER handler);
void A2lCreate_REPRO_PAR(const XCP_REPRO_SEGMENT *segments, uint32_t segNum);
