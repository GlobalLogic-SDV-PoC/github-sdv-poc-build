/**
 **************************************************************************************************
 *  @file           : enc-vidc-headers.h
 *  @brief          : VIDC driver headers
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      VIDC driver headers and defines
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_VIDC_HEADERS__H__
#define __ENC_VIDC_HEADERS__H__

#include "comdef.h"
#include "ioctlClient.h"
#include "vidc_ioctl.h"
#include "vidc_types.h"

#define DEFAULT_H264_PROFILE            VIDC_PROFILE_H264_MAIN
#define DEFAULT_H265_PROFILE            VIDC_PROFILE_HEVC_MAIN

#define DEFAULT_H264_LEVEL              VIDC_LEVEL_H264_1p1
#define DEFAULT_H265_LEVEL              VIDC_LEVEL_HEVC_51

#define DEFAULT_ENTROPY_MODE            VIDC_ENTROPY_MODE_CAVLC
#define DEFAULT_CABAC_MODEL             VIDC_CABAC_MODEL_UNUSED
#define DEFAULT_DEBLOCKING_MODE         VIDC_DB_ALL_BLOCKING_BOUNDARY
#define DEFAULT_SLICE_ALPHA_OFFSET      0
#define DEFAULT_SLICE_BETA_OFFSET       0

#define DEFAULT_INPUT_BUFFER_REQ        5
#define DEFAULT_OUTPUT_BUFFER_REQ       4
#define DEFAULT_NUM_FRAMES_TO_ENCODE    10
#define DEFAULT_WIDTH                   3840
#define DEFAULT_HEIGHT                  2160
#define DEFAULT_FRAME_RATE              30
#define DEFAULT_NUM_P_BET_2I            30
#define DEFAULT_NUM_B_BET_2I            0
#define DEFAULT_IDR_PERIOD              0
#define DEFAULT_TARTGET_BITRATE         64000
#define DEFAULT_CODEC                   VIDC_CODEC_HEVC
#define DEFAULT_RATE_CONTROL            VIDC_RATE_CONTROL_CBR_VFR
#define DEFAULT_QUANTIZATION_PARAM      20

#define ONE                             1
#define ONE_MILIION                     1000000
#define TIMEOUT_CNT                     50000
#define H264_START_CODE                 0x00000001

#define WAIT_TIMEOUT_1_SEC              1000
#define WAIT_TIMEOUT_10_SEC             (10 * WAIT_TIMEOUT_1_SEC)
#define WAIT_TIMEOUT_3_SEC              (3 * WAIT_TIMEOUT_1_SEC)

#define MAX_DEV_MSG_BUFF_SIZE           256
#define MAX_IOCTL_BUFFER_SIZE           256

#define NALU_TYPE_SPS                   7
#define NALU_TYPE_PPS                   8
#define NALU_TYPE_SEI                   6
#define NALU_TYPE_IDR                   5
#define NALU_TYPE_NON_IDR               1

#define VIDC_Y_PLANE                    1
#define VIDC_UV_PLANE                   2
#define VIDC_FPS_DENOMINATOR            1

#define MAX_OUT_BUFFER_SIZE             0x100000
#define ALIGN_4K(x)                     ((x + 0xfff) & (~0xfff))

#define TIMESTAMP_L_FILE                0
#define TIMESTAMP_INTERVAL              33333

#endif /* __ENC_VIDC_HEADERS__H__ */

