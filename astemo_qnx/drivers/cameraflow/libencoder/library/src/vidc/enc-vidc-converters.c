/**
 **************************************************************************************************
 *  @file           : enc-vidc-converters.c
 *  @brief          : Encoder VIDC enums to sting converters API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder VIDC enums to sting converters API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "enc-logger.h"
#include "enc-vidc-headers.h"

const char *vidc_property_id2str(vidc_property_id_type property_id)
{
        switch (property_id) {
        case VIDC_I_COMMON_START_BASE:
                return "VIDC_I_COMMON_START_BASE";
        case VIDC_I_LIVE:
                return "VIDC_I_LIVE";
        case VIDC_I_PRIORITY:
                return "VIDC_I_PRIORITY";
        case VIDC_I_FRAME_SIZE:
                return "VIDC_I_FRAME_SIZE";
        case VIDC_I_METADATA_HEADER:
                return "VIDC_I_METADATA_HEADER";
        case VIDC_I_SESSION_CODEC:
                return "VIDC_I_SESSION_CODEC";
        case VIDC_I_PROFILE:
                return "VIDC_I_PROFILE";
        case VIDC_I_LEVEL:
                return "VIDC_I_LEVEL";
        case VIDC_I_COLOR_FORMAT:
                return "VIDC_I_COLOR_FORMAT";
        case VIDC_I_CAPABILITY_CODEC:
                return "VIDC_I_CAPABILITY_CODEC";
        case VIDC_I_CAPABILITY_COLOR_FORMAT:
                return "VIDC_I_CAPABILITY_COLOR_FORMAT";
        case VIDC_I_CAPABILITY_PROFILE_LEVEL:
                return "VIDC_I_CAPABILITY_PROFILE_LEVEL";
        case VIDC_I_CAPABILITY_FRAME_SIZE:
                return "VIDC_I_CAPABILITY_FRAME_SIZE";
        case VIDC_I_CAPABILITY_LTR_COUNT:
                return "VIDC_I_CAPABILITY_LTR_COUNT";
        case VIDC_I_BUFFER_REQUIREMENTS:
                return "VIDC_I_BUFFER_REQUIREMENTS";
        case VIDC_I_PLANE_DEF:
                return "VIDC_I_PLANE_DEF";
        case VIDC_I_CAPABILITY_SCAN_FORMAT:
                return "VIDC_I_CAPABILITY_SCAN_FORMAT";
        case VIDC_I_CAPABILITY_NAL_STREAM_FORMAT:
                return "VIDC_I_CAPABILITY_NAL_STREAM_FORMAT";
        case VIDC_I_NAL_STREAM_FORMAT:
                return "VIDC_I_NAL_STREAM_FORMAT";
        case VIDC_I_DIVX_FORMAT:
                return "VIDC_I_DIVX_FORMAT";
        case VIDC_I_FRAME_RATE:
                return "VIDC_I_FRAME_RATE";
        case VIDC_I_MAX_FRAME_RATE:
                return "VIDC_I_MAX_FRAME_RATE";
        case VIDC_I_MULTI_VIEW_FORMAT:
                return "VIDC_I_MULTI_VIEW_FORMAT";
        case VIDC_I_SEQUENCE_HEADER:
                return "VIDC_I_SEQUENCE_HEADER";
        case VIDC_I_TARGET_BITRATE:
                return "VIDC_I_TARGET_BITRATE";
        case VIDC_I_BUFFER_ALLOC_MODE:
                return "VIDC_I_BUFFER_ALLOC_MODE";
        case VIDC_I_MVC_BUFFER_LAYOUT:
                return "VIDC_I_MVC_BUFFER_LAYOUT";
        case VIDC_I_BIT_DEPTH:
                return "VIDC_I_BIT_DEPTH";
        case VIDC_I_CAPABILITY_MAX_FRAME_RATE:
                return "VIDC_I_CAPABILITY_MAX_FRAME_RATE";
        case VIDC_I_CAPABILITY_MAX_MACROBLOCKS:
                return "VIDC_I_CAPABILITY_MAX_MACROBLOCKS";
        case VIDC_I_CAPABILITY_MAX_TARGET_BITRATE:
                return "VIDC_I_CAPABILITY_MAX_TARGET_BITRATE";
        case VIDC_I_CONTENT_PROTECTION:
                return "VIDC_I_CONTENT_PROTECTION";
        case VIDC_I_SESSION_NAME:
                return "VIDC_I_SESSION_NAME";
        case VIDC_I_ENC_START_BASE:
                return "VIDC_I_ENC_START_BASE";
        case VIDC_I_ENC_MULTI_SLICE:
                return "VIDC_I_ENC_MULTI_SLICE";
        case VIDC_I_ENC_H264_ENTROPY_CTRL:
                return "VIDC_I_ENC_H264_ENTROPY_CTRL";
        case VIDC_I_ENC_H264_DEBLOCKING:
                return "VIDC_I_ENC_H264_DEBLOCKING";
        case VIDC_I_ENC_RATE_CONTROL:
                return "VIDC_I_ENC_RATE_CONTROL";
        case VIDC_I_ENC_SESSION_QP:
                return "VIDC_I_ENC_SESSION_QP";
        case VIDC_I_ENC_SESSION_QP_RANGE:
                return "VIDC_I_ENC_SESSION_QP_RANGE";
        case VIDC_I_ENC_INTRA_PERIOD:
                return "VIDC_I_ENC_INTRA_PERIOD";
        case VIDC_I_ENC_MPEG4_VOP_TIMING:
                return "VIDC_I_ENC_MPEG4_VOP_TIMING";
        case VIDC_I_ENC_MPEG4_SHORT_HEADER:
                return "VIDC_I_ENC_MPEG4_SHORT_HEADER";
        case VIDC_I_ENC_MPEG4_HEADER_EXTENSION:
                return "VIDC_I_ENC_MPEG4_HEADER_EXTENSION";
        case VIDC_I_ENC_MPEG4_ACPRED:
                return "VIDC_I_ENC_MPEG4_ACPRED";
        case VIDC_I_ENC_MAX_SEQUENCE_HEADER_SIZE:
                return "VIDC_I_ENC_MAX_SEQUENCE_HEADER_SIZE";
        case VIDC_I_ENC_INTRA_REFRESH:
                return "VIDC_I_ENC_INTRA_REFRESH";
        case VIDC_I_ENC_TIMESTAMP_SCALE:
                return "VIDC_I_ENC_TIMESTAMP_SCALE";
        case VIDC_I_ENC_TEMPORAL_SPATIAL_TRADEOFF:
                return "VIDC_I_ENC_TEMPORAL_SPATIAL_TRADEOFF";
        case VIDC_I_ENC_IDR_PERIOD:
                return "VIDC_I_ENC_IDR_PERIOD";
        case VIDC_I_ENC_REQUEST_SYNC_FRAME:
                return "VIDC_I_ENC_REQUEST_SYNC_FRAME";
        case VIDC_I_ENC_SLICE_DELIVERY_MODE:
                return "VIDC_I_ENC_SLICE_DELIVERY_MODE";
        case VIDC_I_ENC_SYNC_FRAME_SEQ_HDR:
                return "VIDC_I_ENC_SYNC_FRAME_SEQ_HDR";
        case VIDC_I_ENC_H264_IDR_S3D_FPA_NAL:
                return "VIDC_I_ENC_H264_IDR_S3D_FPA_NAL";
        case VIDC_I_ENC_GEN_AUDNAL:
                return "VIDC_I_ENC_GEN_AUDNAL";
        case VIDC_I_ENC_VUI_TIMING_INFO:
                return "VIDC_I_ENC_VUI_TIMING_INFO";
        case VIDC_I_ENC_BITSTREAM_RESTRC:
                return "VIDC_I_ENC_BITSTREAM_RESTRC";
        case VIDC_I_LOW_LATENCY_MODE:
                return "VIDC_I_LOW_LATENCY_MODE";
        case VIDC_I_ENC_MAX_BITRATE:
                return "VIDC_I_ENC_MAX_BITRATE";
        case VIDC_I_ENC_PRESERVE_TEXT_QUALITY:
                return "VIDC_I_ENC_PRESERVE_TEXT_QUALITY";
        case VIDC_I_ENC_MAX_NUM_B_FRAMES:
                return "VIDC_I_ENC_MAX_NUM_B_FRAMES";
        case VIDC_I_ENC_H264_8X8_TRANSFORM:
                return "VIDC_I_ENC_H264_8X8_TRANSFORM";
        case VIDC_I_ENC_LTR_MODE:
                return "VIDC_I_ENC_LTR_MODE";
        case VIDC_I_ENC_LTR_COUNT:
                return "VIDC_I_ENC_LTR_COUNT";
        case VIDC_I_ENC_USELTRFRAME:
                return "VIDC_I_ENC_USELTRFRAME";
        case VIDC_I_ENC_LTRPERIOD:
                return "VIDC_I_ENC_LTRPERIOD";
        case VIDC_I_ENC_VUI_VIDEO_SIGNAL_INFO:
                return "VIDC_I_ENC_VUI_VIDEO_SIGNAL_INFO";
        case VIDC_I_ENC_ROI_MODE_TYPE:
                return "VIDC_I_ENC_ROI_MODE_TYPE";
        case VIDC_I_ENC_ENABLE_GRID:
                return "VIDC_I_ENC_ENABLE_GRID";
        case VIDC_I_ENC_FRAME_QUALITY:
                return "VIDC_I_ENC_FRAME_QUALITY";
        case VIDC_I_ENC_CONTENT_ADAPTIVE_CODING:
                return "VIDC_I_ENC_CONTENT_ADAPTIVE_CODING";
        case VIDC_I_ENC_MARKLTRFRAME:
                return "VIDC_I_ENC_MARKLTRFRAME";
        case VIDC_I_ENC_HIER_B_MAX_NUM_ENH_LAYER:
                return "VIDC_I_ENC_HIER_B_MAX_NUM_ENH_LAYER";
        case VIDC_I_ENC_HIER_P_MAX_NUM_ENH_LAYER:
                return "VIDC_I_ENC_HIER_P_MAX_NUM_ENH_LAYER";
        case VIDC_I_ENC_HIER_P_HYBRID_MODE:
                return "VIDC_I_ENC_HIER_P_HYBRID_MODE";
        case VIDC_I_ENC_HIER_P_ENH_LAYER:
                return "VIDC_I_ENC_HIER_P_ENH_LAYER";
        case VIDC_I_CAPABILITY_MAX_NUM_BFRAMES:
                return "VIDC_I_CAPABILITY_MAX_NUM_BFRAMES";
        case VIDC_I_DEC_START_BASE:
                return "VIDC_I_DEC_START_BASE";
        case VIDC_I_DEC_PROGRESSIVE_ONLY:
                return "VIDC_I_DEC_PROGRESSIVE_ONLY";
        case VIDC_I_DEC_CONT_ON_RECONFIG:
                return "VIDC_I_DEC_CONT_ON_RECONFIG";
        case VIDC_I_DEC_OUTPUT_ORDER:
                return "VIDC_I_DEC_OUTPUT_ORDER";
        case VIDC_I_DEC_PICTYPE:
                return "VIDC_I_DEC_PICTYPE";
        case VIDC_I_DEC_MULTI_STREAM:
                return "VIDC_I_DEC_MULTI_STREAM";
        case VIDC_I_DEC_MB_ERROR_MAP_REPORTING:
                return "VIDC_I_DEC_MB_ERROR_MAP_REPORTING";
        case VIDC_I_DEC_MB_ERROR_MAP:
                return "VIDC_I_DEC_MB_ERROR_MAP";
        case VIDC_I_DEC_DISPLAY_PIC_BUFFER_COUNT:
                return "VIDC_I_DEC_DISPLAY_PIC_BUFFER_COUNT";
        case VIDC_I_DEC_OUTPUT2_KEEP_ASPECT_RATIO:
                return "VIDC_I_DEC_OUTPUT2_KEEP_ASPECT_RATIO";
        case VIDC_I_DEC_MULTI_VIEW_SELECT:
                return "VIDC_I_DEC_MULTI_VIEW_SELECT";
        case VIDC_I_DEC_THUMBNAIL_MODE:
                return "VIDC_I_DEC_THUMBNAIL_MODE";
        case VIDC_I_DEC_FRAME_ASSEMBLY:
                return "VIDC_I_DEC_FRAME_ASSEMBLY";
        case VIDC_I_DEC_SCS_THRESHOLD:
                return "VIDC_I_DEC_SCS_THRESHOLD";
        case VIDC_I_VPE_START_BASE:
                return "VIDC_I_VPE_START_BASE";
        case VIDC_I_VPE_DEINTERLACER:
                return "VIDC_I_VPE_DEINTERLACER";
        case VIDC_I_VPE_SPATIAL_TRANSFORM:
                return "VIDC_I_VPE_SPATIAL_TRANSFORM";
        case VIDC_I_VPE_CAPABILITY_SCALE:
                return "VIDC_I_VPE_CAPABILITY_SCALE";
        case VIDC_I_VPE_CSC:
                return "VIDC_I_VPE_CSC";
        case VIDC_I_VPE_BLUR_FILTER:
                return "VIDC_I_VPE_BLUR_FILTER";
        case VIDC_I_RESERVED_START_BASE:
                return "VIDC_I_RESERVED_START_BASE";
        default:
                log_err("Undefined property id: 0x%X (dec: %d)\n", property_id, property_id);

                return "UNDEFINED PROPERTY ID";
        }
}

const char *vidc_priority2str(vidc_priority_level_type priority)
{
        switch (priority) {
        case VIDC_PRIORITY_LOW:
                return "VIDC_PRIORITY_LOW";
        case VIDC_PRIORITY_MEDIUM:
                return "VIDC_PRIORITY_MEDIUM";
        case VIDC_PRIORITY_HIGH:
                return "VIDC_PRIORITY_HIGH";
        default:
                log_err("Undefined priority level: 0x%X (dec: %d)\n", priority, priority);

                return "UNDEFINED PRIORITY LEVEL";
        }
}

const char *vidc_session2str(vidc_session_type type)
{
        switch (type) {
        case VIDC_SESSION_ENCODE:
                return "VIDC_SESSION_ENCODE";
        case VIDC_SESSION_DECODE:
                return "VIDC_SESSION_DECODE";
        case VIDC_SESSION_UNUSED:
                return "VIDC_SESSION_UNUSED";
        default:
                log_err("Undefined session type: 0x%X (dec: %d)\n", type, type);

                return "UNDEFINED SESSION TYPE";
        }
}

const char *vidc_codec2str(vidc_codec_type type)
{
        switch (type) {
        case VIDC_CODEC_H264:
                return "VIDC_CODEC_H264";
        case VIDC_CODEC_MPEG2:
                return "VIDC_CODEC_MPEG2";
        case VIDC_CODEC_VP8:
                return "VIDC_CODEC_VP8";
        case VIDC_CODEC_HEVC:
                return "VIDC_CODEC_HEVC";
        case VIDC_CODEC_VP9:
                return "VIDC_CODEC_VP9";
        case VIDC_CODEC_TME:
                return "VIDC_CODEC_TME";
        case VIDC_CODEC_HEIC:
                return "VIDC_CODEC_HEIC";
        case VIDC_CODEC_UNUSED:
                return "VIDC_CODEC_UNUSED";
        default:
                log_err("Undefined codec type: 0x%X (dec: %d)\n", type, type);

                return "UNDEFINED CODEC TYPE";
        }
}

const char *vidc_buffer_type2str(vidc_buffer_type type)
{
        switch (type) {
        case VIDC_BUFFER_INPUT:
                return "VIDC_BUFFER_INPUT";
        case VIDC_BUFFER_OUTPUT:
                return "VIDC_BUFFER_OUTPUT";
        case VIDC_BUFFER_OUTPUT2:
                return "VIDC_BUFFER_OUTPUT2";
        case VIDC_BUFFER_METADATA_INPUT:
                return "VIDC_BUFFER_METADATA_INPUT";
        case VIDC_BUFFER_METADATA_OUTPUT:
                return "VIDC_BUFFER_METADATA_OUTPUT";
        case VIDC_BUFFER_METADATA_OUTPUT2:
                return "VIDC_BUFFER_METADATA_OUTPUT2";
        case VIDC_BUFFER_UNUSED:
                return "VIDC_BUFFER_UNUSED";
        default:
                log_err("Undefined buffer type: 0x%X (dec: %d)\n", type, type);

                return "UNDEFINED BUFFER TYPE";
        }
}

const char *vidc_buffer_mode2str(vidc_buffer_mode_type mode)
{
        switch (mode) {
        case VIDC_BUFFER_MODE_STATIC:
                return "VIDC_BUFFER_MODE_STATIC";
        case VIDC_BUFFER_MODE_RING:
                return "VIDC_BUFFER_MODE_RING";
        case VIDC_BUFFER_MODE_DYNAMIC:
                return "VIDC_BUFFER_MODE_DYNAMIC";
        case VIDC_BUFFER_MODE_UNUSED:
                return "VIDC_BUFFER_MODE_UNUSED";
        default:
                log_err("Undefined buffer mode: 0x%X (dec: %d)\n", mode, mode);

                return "UNDEFINED BUFFER MODE";
        }
}

const char *vidc_status2str(vidc_status_type status)
{
        switch (status) {
        case VIDC_ERR_NONE:
                return "VIDC_ERR_NONE";
        case VIDC_ERR_INDEX_NOMORE:
                return "VIDC_ERR_INDEX_NOMORE";
        case VIDC_ERR_FAIL:
                return "VIDC_ERR_FAIL";
        case VIDC_ERR_ALLOC_FAIL:
                return "VIDC_ERR_ALLOC_FAIL";
        case VIDC_ERR_ILLEGAL_OP:
                return "VIDC_ERR_ILLEGAL_OP";
        case VIDC_ERR_BAD_PARAM:
                return "VIDC_ERR_BAD_PARAM";
        case VIDC_ERR_BAD_HANDLE:
                return "VIDC_ERR_BAD_HANDLE";
        case VIDC_ERR_NOT_SUPPORTED:
                return "VIDC_ERR_NOT_SUPPORTED";
        case VIDC_ERR_BAD_STATE:
                return "VIDC_ERR_BAD_STATE";
        case VIDC_ERR_MAX_CLIENT:
                return "VIDC_ERR_MAX_CLIENT";
        case VIDC_ERR_IFRAME_EXPECTED:
                return "VIDC_ERR_IFRAME_EXPECTED";
        case VIDC_ERR_HW_FATAL:
                return "VIDC_ERR_HW_FATAL";
        case VIDC_ERR_BITSTREAM_ERR:
                return "VIDC_ERR_BITSTREAM_ERR";
        case VIDC_ERR_SEQHDR_PARSE_FAIL:
                return "VIDC_ERR_SEQHDR_PARSE_FAIL";
        case VIDC_ERR_INSUFFICIENT_BUFFER:
                return "VIDC_ERR_INSUFFICIENT_BUFFER";
        case VIDC_ERR_BAD_POWER_STATE:
                return "VIDC_ERR_BAD_POWER_STATE";
        case VIDC_ERR_NO_VALID_SESSION:
                return "VIDC_ERR_NO_VALID_SESSION";
        case VIDC_ERR_TIMEOUT:
                return "VIDC_ERR_TIMEOUT";
        case VIDC_ERR_CMDQFULL:
                return "VIDC_ERR_CMDQFULL";
        case VIDC_ERR_START_CODE_NOT_FOUND:
                return "VIDC_ERR_START_CODE_NOT_FOUND";
        case VIDC_ERR_UNSUPPORTED_STREAM:
                return "VIDC_ERR_UNSUPPORTED_STREAM";
        case VIDC_ERR_SESSION_PICTURE_DROPPED:
                return "VIDC_ERR_SESSION_PICTURE_DROPPED";
        case VIDC_ERR_CLIENTFATAL:
                return "VIDC_ERR_CLIENTFATAL";
        case VIDC_ERR_NONCOMPLIANT_STREAM:
                return "VIDC_ERR_NONCOMPLIANT_STREAM";
        case VIDC_ERR_SPURIOUS_INTERRUPT:
                return "VIDC_ERR_SPURIOUS_INTERRUPT";
        case VIDC_ERR_UNUSED:
                return "VIDC_ERR_UNUSED";
        default:
                log_err("Undefined status: 0x%X (dec: %d)\n", status, status);

                return "UNDEFINED STATUS";
        }
}

const char *vidc_event2str(vidc_event_type event)
{
        switch (event) {
        case VIDC_EVT_RESP_BASE:
                return "VIDC_EVT_RESP_BASE";
        case VIDC_EVT_RESP_START:
                return "VIDC_EVT_RESP_START";
        case VIDC_EVT_RESP_STOP:
                return "VIDC_EVT_RESP_STOP";
        case VIDC_EVT_RESP_PAUSE:
                return "VIDC_EVT_RESP_PAUSE";
        case VIDC_EVT_RESP_RESUME:
                return "VIDC_EVT_RESP_RESUME";
        case VIDC_EVT_RESP_FLUSH_INPUT_DONE:
                return "VIDC_EVT_RESP_FLUSH_INPUT_DONE";
        case VIDC_EVT_RESP_FLUSH_OUTPUT_DONE:
                return "VIDC_EVT_RESP_FLUSH_OUTPUT_DONE";
        case VIDC_EVT_RESP_FLUSH_OUTPUT2_DONE:
                return "VIDC_EVT_RESP_FLUSH_OUTPUT2_DONE";
        case VIDC_EVT_RESP_INPUT_DONE:
                return "VIDC_EVT_RESP_INPUT_DONE";
        case VIDC_EVT_RESP_OUTPUT_DONE:
                return "VIDC_EVT_RESP_OUTPUT_DONE";
        case VIDC_EVT_RESP_LOAD_RESOURCES:
                return "VIDC_EVT_RESP_LOAD_RESOURCES";
        case VIDC_EVT_RESP_RELEASE_RESOURCES:
                return "VIDC_EVT_RESP_RELEASE_RESOURCES";
        case VIDC_EVT_RESP_LTRUSE_FAILED:
                return "VIDC_EVT_RESP_LTRUSE_FAILED";
        case VIDC_EVT_RESP_DRAIN:
                return "VIDC_EVT_RESP_DRAIN";
        case VIDC_EVT_RESP_START_INPUT_DONE:
                return "VIDC_EVT_RESP_START_INPUT_DONE";
        case VIDC_EVT_RESP_START_OUTPUT_DONE:
                return "VIDC_EVT_RESP_START_OUTPUT_DONE";
        case VIDC_EVT_RESP_STOP_INPUT_DONE:
                return "VIDC_EVT_RESP_STOP_INPUT_DONE";
        case VIDC_EVT_RESP_STOP_OUTPUT_DONE:
                return "VIDC_EVT_RESP_STOP_OUTPUT_DONE";
        case VIDC_EVT_UNSOLICITED_BASE:
                return "VIDC_EVT_UNSOLICITED_BASE";
        case VIDC_EVT_INPUT_RECONFIG:
                return "VIDC_EVT_INPUT_RECONFIG";
        case VIDC_EVT_OUTPUT_RECONFIG:
                return "VIDC_EVT_OUTPUT_RECONFIG";
        case VIDC_EVT_ERR_HWFATAL:
                return "VIDC_EVT_ERR_HWFATAL";
        case VIDC_EVT_ERR_CLIENTFATAL:
                return "VIDC_EVT_ERR_CLIENTFATAL";
        case VIDC_EVT_RESOURCES_LOST:
                return "VIDC_EVT_RESOURCES_LOST";
        case VIDC_EVT_INFO_OUTPUT_RECONFIG:
                return "VIDC_EVT_INFO_OUTPUT_RECONFIG";
        case VIDC_EVT_PROPERTY_CHANGED:
                return "VIDC_EVT_PROPERTY_CHANGED";
        case VIDC_EVT_SESSION_ERR:
                return "VIDC_EVT_SESSION_ERR";
        case VIDC_EVT_RELEASE_BUFFER_REFERENCE:
                return "VIDC_EVT_RELEASE_BUFFER_REFERENCE";
        case VIDC_EVT_UNUSED:
                return "VIDC_EVT_UNUSED";
        default:
                log_err("Undefined event: 0x%X (dec: %d)\n", event, event);

                return "UNDEFINED EVENT";
        }
}

const char *vidc_ioctl2str(uint32_t ioctl)
{
        switch (ioctl) {
        case VIDC_IOCTL_SET_PROPERTY:
                return "VIDC_IOCTL_SET_PROPERTY";
        case VIDC_IOCTL_GET_PROPERTY:
                return "VIDC_IOCTL_GET_PROPERTY";
        case VIDC_IOCTL_ALLOCATE_BUFFER:
                return "VIDC_IOCTL_ALLOCATE_BUFFER";
        case VIDC_IOCTL_SET_BUFFER:
                return "VIDC_IOCTL_SET_BUFFER";
        case VIDC_IOCTL_FREE_BUFFER:
                return "VIDC_IOCTL_FREE_BUFFER";
        case VIDC_IOCTL_LOAD_RESOURCES:
                return "VIDC_IOCTL_LOAD_RESOURCES";
        case VIDC_IOCTL_RELEASE_RESOURCES:
                return "VIDC_IOCTL_RELEASE_RESOURCES";
        case VIDC_IOCTL_START:
                return "VIDC_IOCTL_START";
        case VIDC_IOCTL_PAUSE:
                return "VIDC_IOCTL_PAUSE";
        case VIDC_IOCTL_RESUME:
                return "VIDC_IOCTL_RESUME";
        case VIDC_IOCTL_STOP:
                return "VIDC_IOCTL_STOP";
        case VIDC_IOCTL_EMPTY_INPUT_BUFFER:
                return "VIDC_IOCTL_EMPTY_INPUT_BUFFER";
        case VIDC_IOCTL_FILL_OUTPUT_BUFFER:
                return "VIDC_IOCTL_FILL_OUTPUT_BUFFER";
        case VIDC_IOCTL_FLUSH:
                return "VIDC_IOCTL_FLUSH";
        case VIDC_IOCTL_DRAIN:
                return "VIDC_IOCTL_DRAIN";
        default:
                log_err("Undefined ioctl: 0x%X (dec: %d)\n", ioctl, ioctl);

                return "UNDEFINED IOCTL";
        }
}

const char *vidc_color_format2str(vidc_color_format_type format)
{
        switch (format) {
        case VIDC_COLOR_FORMAT_MONOCHROME:
                return "VIDC_COLOR_FORMAT_MONOCHROME";
        case VIDC_COLOR_FORMAT_NV12:
                return "VIDC_COLOR_FORMAT_NV12";
        case VIDC_COLOR_FORMAT_NV21:
                return "VIDC_COLOR_FORMAT_NV21";
        case VIDC_COLOR_FORMAT_NV12_4x4TILE:
                return "VIDC_COLOR_FORMAT_NV12_4x4TILE";
        case VIDC_COLOR_FORMAT_NV21_4x4TILE:
                return "VIDC_COLOR_FORMAT_NV21_4x4TILE";
        case VIDC_COLOR_FORMAT_YUYV:
                return "VIDC_COLOR_FORMAT_YUYV";
        case VIDC_COLOR_FORMAT_YVYU:
                return "VIDC_COLOR_FORMAT_YVYU";
        case VIDC_COLOR_FORMAT_UYVY:
                return "VIDC_COLOR_FORMAT_UYVY";
        case VIDC_COLOR_FORMAT_VYUY:
                return "VIDC_COLOR_FORMAT_VYUY";
        case VIDC_COLOR_FORMAT_RGB565:
                return "VIDC_COLOR_FORMAT_RGB565";
        case VIDC_COLOR_FORMAT_BGR565:
                return "VIDC_COLOR_FORMAT_BGR565";
        case VIDC_COLOR_FORMAT_RGB888:
                return "VIDC_COLOR_FORMAT_RGB888";
        case VIDC_COLOR_FORMAT_BGR888:
                return "VIDC_COLOR_FORMAT_BGR888";
        case VIDC_COLOR_FORMAT_YUV444:
                return "VIDC_COLOR_FORMAT_YUV444";
        case VIDC_COLOR_FORMAT_YV12:
                return "VIDC_COLOR_FORMAT_YV12";
        case VIDC_COLOR_FORMAT_RGBA8888:
                return "VIDC_COLOR_FORMAT_RGBA8888";
        default:
                log_err("Undefined color format: 0x%X (dec: %d)\n", format, format);

                return "UNDEFINED COLOR FORMAT";
        }
}

const char *vidc_h264_profile2str(vidc_h264_profile_type profile)
{
        switch (profile) {
        case VIDC_PROFILE_H264_BASELINE:
                return "VIDC_PROFILE_H264_BASELINE";
        case VIDC_PROFILE_H264_MAIN:
                return "VIDC_PROFILE_H264_MAIN";
        case VIDC_PROFILE_H264_HIGH:
                return "VIDC_PROFILE_H264_HIGH";
        case VIDC_PROFILE_H264_STEREO_HIGH:
                return "VIDC_PROFILE_H264_STEREO_HIGH";
        case VIDC_PROFILE_H264_MV_HIGH:
                return "VIDC_PROFILE_H264_MV_HIGH";
        case VIDC_PROFILE_H264_CONSTRAINED_BASE:
                return "VIDC_PROFILE_H264_CONSTRAINED_BASE";
        case VIDC_PROFILE_H264_UNUSED:
                return "VIDC_PROFILE_H264_UNUSED";
        default:
                log_err("Undefined color profile: 0x%X (dec: %d)\n", profile, profile);

                return "UNDEFINED COLOR PROFILE";
        }
}

const char *vidc_hevc_profile2str(vidc_hevc_profile_type profile)
{
        switch (profile) {
        case VIDC_PROFILE_HEVC_MAIN:
                return "VIDC_PROFILE_HEVC_MAIN";
        case VIDC_PROFILE_HEVC_MAIN10:
                return "VIDC_PROFILE_HEVC_MAIN10";
        case VIDC_PROFILE_HEVC_MAIN_STILL_PICTURE:
                return "VIDC_PROFILE_HEVC_MAIN_STILL_PICTURE";
        case VIDC_PROFILE_HEVC_MAIN10_STILL_PICTURE:
                return "VIDC_PROFILE_HEVC_MAIN10_STILL_PICTURE";
        case VIDC_PROFILE_HEVC_UNUSED:
                return "VIDC_PROFILE_HEVC_UNUSED";
        default:
                log_err("Undefined color profile: 0x%X (dec: %d)\n", profile, profile);

                return "UNDEFINED COLOR PROFILE";
        }
}

const char *vidc_h264_level2str(vidc_h264_level_type level)
{
        switch (level) {
        case VIDC_LEVEL_H264_1:
                return "VIDC_LEVEL_H264_1";
        case VIDC_LEVEL_H264_1b:
                return "VIDC_LEVEL_H264_1b";
        case VIDC_LEVEL_H264_1p1:
                return "VIDC_LEVEL_H264_1p1";
        case VIDC_LEVEL_H264_1p2:
                return "VIDC_LEVEL_H264_1p2";
        case VIDC_LEVEL_H264_1p3:
                return "VIDC_LEVEL_H264_1p3";
        case VIDC_LEVEL_H264_2:
                return "VIDC_LEVEL_H264_2";
        case VIDC_LEVEL_H264_2p1:
                return "VIDC_LEVEL_H264_2p1";
        case VIDC_LEVEL_H264_2p2:
                return "VIDC_LEVEL_H264_2p2";
        case VIDC_LEVEL_H264_3:
                return "VIDC_LEVEL_H264_3";
        case VIDC_LEVEL_H264_3p1:
                return "VIDC_LEVEL_H264_3p1";
        case VIDC_LEVEL_H264_3p2:
                return "VIDC_LEVEL_H264_3p2";
        case VIDC_LEVEL_H264_4:
                return "VIDC_LEVEL_H264_4";
        case VIDC_LEVEL_H264_4p1:
                return "VIDC_LEVEL_H264_4p1";
        case VIDC_LEVEL_H264_4p2:
                return "VIDC_LEVEL_H264_4p2";
        case VIDC_LEVEL_H264_5:
                return "VIDC_LEVEL_H264_5";
        case VIDC_LEVEL_H264_5p1:
                return "VIDC_LEVEL_H264_5p1";
        case VIDC_LEVEL_H264_5p2:
                return "VIDC_LEVEL_H264_5p2";
        case VIDC_LEVEL_H264_6:
                return "VIDC_LEVEL_H264_6";
        case VIDC_LEVEL_H264_6p1:
                return "VIDC_LEVEL_H264_6p1";
        case VIDC_LEVEL_H264_6p2:
                return "VIDC_LEVEL_H264_6p2";
        case VIDC_LEVEL_H264_UNUSED:
                return "VIDC_LEVEL_H264_UNUSED";
        default:
                log_err("Undefined H264 level: 0x%X (dec: %d)\n", level, level);

                return "UNDEFINED H264 LEVEL";
        }
}

const char *vidc_hevc_level2str(vidc_hevc_level_type level)
{
        switch (level) {
        case VIDC_LEVEL_HEVC_1:
                return "VIDC_LEVEL_HEVC_1";
        case VIDC_LEVEL_HEVC_2:
                return "VIDC_LEVEL_HEVC_2";
        case VIDC_LEVEL_HEVC_21:
                return "VIDC_LEVEL_HEVC_21";
        case VIDC_LEVEL_HEVC_3:
                return "VIDC_LEVEL_HEVC_3";
        case VIDC_LEVEL_HEVC_31:
                return "VIDC_LEVEL_HEVC_31";
        case VIDC_LEVEL_HEVC_4:
                return "VIDC_LEVEL_HEVC_4";
        case VIDC_LEVEL_HEVC_41:
                return "VIDC_LEVEL_HEVC_41";
        case VIDC_LEVEL_HEVC_5:
                return "VIDC_LEVEL_HEVC_5";
        case VIDC_LEVEL_HEVC_51:
                return "VIDC_LEVEL_HEVC_51";
        case VIDC_LEVEL_HEVC_52:
                return "VIDC_LEVEL_HEVC_52";
        case VIDC_LEVEL_HEVC_6:
                return "VIDC_LEVEL_HEVC_6";
        case VIDC_LEVEL_HEVC_61:
                return "VIDC_LEVEL_HEVC_61";
        case VIDC_LEVEL_HEVC_62:
                return "VIDC_LEVEL_HEVC_62";
        case VIDC_LEVEL_HEVC_UNUSED:
                return "VIDC_LEVEL_HEVC_UNUSED";
        default:
                log_err("Undefined HEVC level: 0x%X (dec: %d)\n", level, level);

                return "UNDEFINED HEVC LEVEL";
        }
}

const char *vidc_entropy_mode2str(vidc_entropy_mode_type mode)
{
        switch (mode) {
        case VIDC_ENTROPY_MODE_CAVLC:
                return "VIDC_ENTROPY_MODE_CAVLC";
        case VIDC_ENTROPY_MODE_CABAC:
                return "VIDC_ENTROPY_MODE_CABAC";
        case VIDC_ENTROPY_UNUSED:
                return "VIDC_ENTROPY_UNUSED";
        default:
                log_err("Undefined entropy mode: 0x%X (dec: %d)\n", mode, mode);

                return "UNDEFINED ENTROPY MODE";
        }
}

const char *vidc_rate_control_mode2str(vidc_rate_control_mode_type mode)
{
        switch (mode) {
        case VIDC_RATE_CONTROL_OFF:
                return "VIDC_RATE_CONTROL_OFF";
        case VIDC_RATE_CONTROL_VBR_VFR:
                return "VIDC_RATE_CONTROL_VBR_VFR";
        case VIDC_RATE_CONTROL_VBR_CFR:
                return "VIDC_RATE_CONTROL_VBR_CFR";
        case VIDC_RATE_CONTROL_CBR_VFR:
                return "VIDC_RATE_CONTROL_CBR_VFR";
        case VIDC_RATE_CONTROL_CBR_CFR:
                return "VIDC_RATE_CONTROL_CBR_CFR";
        case VIDC_RATE_CONTROL_MBR_CFR:
                return "VIDC_RATE_CONTROL_MBR_CFR";
        case VIDC_RATE_CONTROL_MBR_VFR:
                return "VIDC_RATE_CONTROL_MBR_VFR";
        case VIDC_RATE_CONTROL_CQ:
                return "VIDC_RATE_CONTROL_CQ";
        case VIDC_RATE_CONTROL_MAX:
                return "VIDC_RATE_CONTROL_MAX";
        case VIDC_RATE_CONTROL_UNUSED:
                return "VIDC_RATE_CONTROL_UNUSED";
        default:
                log_err("Undefined rate control mode: 0x%X (dec: %d)\n", mode, mode);

                return "UNDEFINED RATE CONTROL MODE";
        }
}

const char *vidc_deblock_mode2str(vidc_db_mode_type mode)
{
        switch (mode) {
        case VIDC_DB_DISABLE:
                return "VIDC_DB_DISABLE";
        case VIDC_DB_SKIP_SLICE_BOUNDARY:
                return "VIDC_DB_SKIP_SLICE_BOUNDARY";
        case VIDC_DB_ALL_BLOCKING_BOUNDARY:
                return "VIDC_DB_ALL_BLOCKING_BOUNDARY";
        case VIDC_DB_MAX:
                return "VIDC_DB_MAX";
        case VIDC_DB_UNUSED:
                return "VIDC_DB_UNUSED";
        default:
                log_err("Undefined deblocking mode: 0x%X (dec: %d)\n", mode, mode);

                return "UNDEFINED DEBLOCKING MODE";
        }
}

const char *vidc_rotation2str(vidc_rotation_type rotation)
{
        switch (rotation) {
        case VIDC_ROTATE_NONE:
                return "VIDC_ROTATE_NONE";
        case VIDC_ROTATE_90:
                return "VIDC_ROTATE_90";
        case VIDC_ROTATE_180:
                return "VIDC_ROTATE_180";
        case VIDC_ROTATE_270:
                return "VIDC_ROTATE_270";
        case VIDC_ROTATE_MAX:
                return "VIDC_ROTATE_MAX";
        case VIDC_ROTATE_UNUSED:
                return "VIDC_ROTATE_UNUSED";
        default:
                log_err("Undefined rotation mode: 0x%X (dec: %d)\n", rotation, rotation);

                return "UNDEFINED ROTATION MODE";
        }
}

const char *vidc_flit_type2str(vidc_flip_type type)
{
        switch (type) {
        case VIDC_FLIP_NONE:
                return "VIDC_FLIP_NONE";
        case VIDC_FLIP_HORIZ:
                return "VIDC_FLIP_HORIZ";
        case VIDC_FLIP_VERT:
                return "VIDC_FLIP_VERT";
        case VIDC_FLIP_BOTH:
                return "VIDC_FLIP_BOTH";
        case VIDC_FLIP_MAX:
                return "VIDC_FLIP_MAX";
        case VIDC_FLIP_UNUSED:
                return "VIDC_FLIP_UNUSED";
        default:
                log_err("Undefined flip type: 0x%X (dec: %d)\n", type, type);

                return "UNDEFINED FLIP TYPE";
        }
}

const char *vidc_video_format2str(vidc_video_format_type format)
{
        switch (format) {
        case VIDC_VIDEO_FORMAT_COMPONENT:
                return "VIDC_VIDEO_FORMAT_COMPONENT";
        case VIDC_VIDEO_FORMAT_PAL:
                return "VIDC_VIDEO_FORMAT_PAL";
        case VIDC_VIDEO_FORMAT_NTSC:
                return "VIDC_VIDEO_FORMAT_NTSC";
        case VIDC_VIDEO_FORMAT_SECAM:
                return "VIDC_VIDEO_FORMAT_SECAM";
        case VIDC_VIDEO_FORMAT_MAC:
                return "VIDC_VIDEO_FORMAT_MAC";
        case VIDC_VIDEO_FORMAT_UNSPECIFIED:
                return "VIDC_VIDEO_FORMAT_UNSPECIFIED";
        case VIDC_VIDEO_FORMAT_MAX:
                return "VIDC_VIDEO_FORMAT_MAX";
        default:
                log_err("Undefined video format type: 0x%X (dec: %d)\n", format, format);

                return "UNDEFINED VIDEO FORMAT TYPE";
        }
}

const char *vidc_frame_type2str(vidc_frame_type type)
{
        switch (type) {
        case VIDC_FRAME_I:
                return "VIDC_FRAME_I";
        case VIDC_FRAME_P:
                return "VIDC_FRAME_P";
        case VIDC_FRAME_B:
                return "VIDC_FRAME_B";
        case VIDC_FRAME_IDR:
                return "VIDC_FRAME_IDR";
        case VIDC_FRAME_NOTCODED:
                return "VIDC_FRAME_NOTCODED";
        case VIDC_FRAME_YUV:
                return "VIDC_FRAME_YUV";
        case VIDC_FRAME_UNUSED:
                return "VIDC_FRAME_UNUSED";
        default:
                if (0 == type) {
                        return "UNSETTED FRAME TYPE";
                }

                log_err("Undefined frame type: 0x%X (dec: %d)\n", type, type);

                return "UNDEFINED FRAME TYPE";
        }
}

const char *vidc_flag2str(int flag)
{
        switch (flag) {
        case VIDC_FRAME_FLAG_EOS:
                return "VIDC_FRAME_FLAG_EOS";
        case VIDC_FRAME_FLAG_STARTTIME:
                return "VIDC_FRAME_FLAG_STARTTIME";
        case VIDC_FRAME_FLAG_DECODEONLY:
                return "VIDC_FRAME_FLAG_DECODEONLY";
        case VIDC_FRAME_FLAG_DATACORRUPT:
                return "VIDC_FRAME_FLAG_DATACORRUPT";
        case VIDC_FRAME_FLAG_ENDOFFRAME:
                return "VIDC_FRAME_FLAG_ENDOFFRAME";
        case VIDC_FRAME_FLAG_SYNCFRAME:
                return "VIDC_FRAME_FLAG_SYNCFRAME";
        case VIDC_FRAME_FLAG_METADATA:
                return "VIDC_FRAME_FLAG_METADATA";
        case VIDC_FRAME_FLAG_CODECCONFIG:
                return "VIDC_FRAME_FLAG_CODECCONFIG";
        case VIDC_FRAME_FLAG_TIMESTAMPINVALID:
                return "VIDC_FRAME_FLAG_TIMESTAMPINVALID";
        case VIDC_FRAME_FLAG_READONLY:
                return "VIDC_FRAME_FLAG_READONLY";
        case VIDC_FRAME_FLAG_ENDOFSUBFRAME:
                return "VIDC_FRAME_FLAG_ENDOFSUBFRAME";
        case VIDC_FRAME_FLAG_PFRAME:
                return "VIDC_FRAME_FLAG_PFRAME";
        case VIDC_FRAME_FLAG_BFRAME:
                return "VIDC_FRAME_FLAG_BFRAME";
        case VIDC_FRAME_FLAG_OVERFLOW:
                return "VIDC_FRAME_FLAG_OVERFLOW";
        case VIDC_FRAME_FLAG_ERROR:
                return "VIDC_FRAME_FLAG_ERROR";
        case VIDC_FRAME_FLAG_LAST:
                return "VIDC_FRAME_FLAG_LAST";
        case VIDC_FRAME_FLAG_EOSEQ:
                return "VIDC_FRAME_FLAG_EOSEQ";
        case VIDC_FRAME_FLAG_DROP_FRAME:
                return "VIDC_FRAME_FLAG_DROP_FRAME";
        case VIDC_FRAME_FLAG_DISCONTINUITY:
                return "VIDC_FRAME_FLAG_DISCONTINUITY";
        case VIDC_FRAME_FLAG_TEI:
                return "VIDC_FRAME_FLAG_TEI";
        default:
                log_err("Undefined flag: 0x%X (dec: %d)\n", flag, flag);

                return "UNDEFINED FLAG";
        }
}

