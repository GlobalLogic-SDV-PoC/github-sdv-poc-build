/**
 **************************************************************************************************
 *  @file           : enc-state-types.h
 *  @brief          : Encoder state types
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder state types
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_STATE_TYPES__H__
#define __ENC_STATE_TYPES__H__

/*
   DEINIT    ( open  -> / <- close )   LOADED
   LOADED    ( load  -> / <- release ) IDLE
   IDLE      ( start -> / <- stop )    EXECUTING
   EXECUTING ( pause -> / <- resume )  PAUSE
   PAUSE     ( stop  -> / <- pause )   IDLE
 */
typedef enum {
        STATE_DEINIT    = 0x00,
        STATE_LOADED    = 0x01,
        STATE_IDLE      = 0x02,
        STATE_EXECUTING = 0x03,
        STATE_PAUSE     = 0x04,
        STATE_UNUSED    = 0xFF,
} state_t;

typedef enum {
        STATUS_GOOD                   = 0x00,
        STATUS_PORT_SETTING_CHANGE    = 0x01,
        STATUS_OUTPUT_PORT_FLUSHING   = 0x02,
        STATUS_OUTPUT_PORT_FLUSH_DONE = 0x04,
        STATUS_INPUT_PORT_FLUSHING    = 0x08,
        STATUS_INPUT_PORT_FLUSH_DONE  = 0x10,
        STATUS_ERROR                  = 0xFF,
} status_t;

#endif /* __ENC_STATE_TYPES__H__ */

