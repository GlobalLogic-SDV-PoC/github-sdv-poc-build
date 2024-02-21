/**
 **************************************************************************************************
 *  @file           : enc-vidc-converters.h
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

#ifndef __ENC_VIDC_CONVERTERS__H__
#define __ENC_VIDC_CONVERTERS__H__

#include "enc-vidc-headers.h"

const char *vidc_property_id2str(vidc_property_id_type property);
const char *vidc_priority2str(vidc_priority_level_type priority);
const char *vidc_session2str(vidc_session_type type);
const char *vidc_codec2str(vidc_codec_type type);
const char *vidc_buffer_type2str(vidc_buffer_type type);
const char *vidc_buffer_mode2str(vidc_buffer_mode_type mode);
const char *vidc_status2str(vidc_status_type error);
const char *vidc_event2str(vidc_event_type event);
const char *vidc_ioctl2str(uint32_t ioctl);
const char *vidc_color_format2str(vidc_color_format_type type);
const char *vidc_h264_profile2str(vidc_h264_profile_type profile);
const char *vidc_hevc_profile2str(vidc_hevc_profile_type profile);
const char *vidc_h264_level2str(vidc_h264_level_type level);
const char *vidc_hevc_level2str(vidc_hevc_level_type level);
const char *vidc_entropy_mode2str(vidc_entropy_mode_type mode);
const char *vidc_rate_control_mode2str(vidc_rate_control_mode_type mode);
const char *vidc_deblock_mode2str(vidc_db_mode_type mode);
const char *vidc_rotation2str(vidc_rotation_type rotation);
const char *vidc_flit_type2str(vidc_flip_type type);
const char *vidc_video_format2str(vidc_video_format_type format);
const char *vidc_frame_type2str(vidc_frame_type type);
const char *vidc_flag2str(int flag);

#endif /* __ENC_VIDC_CONVERTERS__H__ */

