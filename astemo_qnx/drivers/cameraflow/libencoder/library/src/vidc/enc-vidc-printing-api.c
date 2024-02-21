/**
 **************************************************************************************************
 *  @file           : enc-vidc-printing-api.c
 *  @brief          : Encoder VIDC printing API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder VIDC printing API for print VIDC structures
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "enc-logger.h"
#include "enc-vidc-converters.h"
#include "enc-vidc-headers.h"
#include "pfm-types.h"

static
void print_property_session(vidc_session_codec_type *property)
{
        log_dbg("session type : '%s'\n", vidc_session2str(property->session));
        log_dbg("codec type   : '%s'\n", vidc_codec2str(property->codec));
}

static
void print_property_alloc_mode(vidc_buffer_alloc_mode_type *property)
{
        log_dbg("buf type : '%s'\n", vidc_buffer_type2str(property->buf_type));
        log_dbg("buf mode : '%s'\n", vidc_buffer_mode2str(property->buf_mode));
}

static
void print_property_intra_period(vidc_iperiod_type *property)
{
        log_dbg("b frames : %d\n", property->b_frames);
        log_dbg("p frames : %d\n", property->p_frames);
}

static
void print_property_spetial_transform(vidc_spatial_transform_type *property)
{
        log_dbg("rotation  : '%s'\n", vidc_rotation2str(property->rotate));
        log_dbg("flip type : '%s'\n", vidc_flit_type2str(property->flip));
}

static
void print_property_signal_info(vidc_vui_video_signal_info_type *property)
{
        log_dbg("enable metadata          : '%s'\n", BOOL_STR(property->enable));
        log_dbg("video format             : '%s'\n", vidc_video_format2str(property->video_format));
        log_dbg("full range flag          : %d\n", property->video_full_Range_flag);
        log_dbg("color description flag   : %d\n", property->color_description_flag);
        log_dbg("colour primaries         : %d\n", property->colour_primaries);
        log_dbg("transfer characteristics : %d\n", property->transfer_characteristics);
        log_dbg("matrix coeffs            : %d\n", property->matrix_coeffs);
}

static
void print_property_vpe_csc(vidc_vpe_csc_type *property)
{
        int i = 0;

        log_dbg("colour primaries : %d\n", property->colour_primaries);
        log_dbg("matrix enabled   : %X\n", property->custom_matrix_enabled);

        for (i = 0; i < VIDC_MAX_MATRIX_COEFFS; i++) {
                log_dbg("csc matrix [%d]  : %d\n", i, property->csc_matrix[i]);
        }

        for (i = 0; i < VIDC_MAX_BIAS_COEFFS; i++) {
                log_dbg("csc bias [%d]    : %d\n", i, property->csc_bias[i]);
        }

        for (i = 0; i < VIDC_MAX_LIMIT_COEFFS; i++) {
                log_dbg("csc limit [%d]   : %d\n", i, property->csc_limit[i]);
        }
}

static
void print_property_frame_size(vidc_frame_size_type *property)
{
        log_dbg("buf type : '%s'\n", vidc_buffer_type2str(property->buf_type));
        log_dbg("width    : %d\n", property->width);
        log_dbg("width    : %d\n", property->height);
}

static
void print_property_frame_rate(vidc_frame_rate_type *property)
{
        log_dbg("buf type        : '%s'\n", vidc_buffer_type2str(property->buf_type));
        log_dbg("fps denominator : %d\n", property->fps_denominator);
        log_dbg("fps numerator   : %d\n", property->fps_numerator);
}

static
void print_property_color_format(vidc_color_format_config_type *property)
{
        log_dbg("buf type     : '%s'\n", vidc_buffer_type2str(property->buf_type));
        log_dbg("color format : '%s'\n", vidc_color_format2str(property->color_format));
}

static
void print_property_plane(vidc_plane_def_type *property)
{
        log_dbg("buf type                      : '%s'\n", vidc_buffer_type2str(property->buf_type));
        log_dbg("plane_index                   : %d\n", property->plane_index);
        log_dbg("min stride                    : %d\n", property->min_stride);
        log_dbg("max stride                    : %d\n", property->max_stride);
        log_dbg("stride multiples              : %d\n", property->stride_multiples);
        log_dbg("min plane buf height multiple : %d\n", property->min_plane_buf_height_multiple);
        log_dbg("buf alignment                 : %d\n", property->buf_alignment);
        log_dbg("min plane buf height          : %d\n", property->min_plane_buf_height);
        log_dbg("actual stride                 : %d\n", property->actual_stride);
        log_dbg("actual plane buf height       : %d\n", property->actual_plane_buf_height);
}

static
void print_property_buffer_requirements(vidc_buffer_reqmnts_type *property)
{
        log_dbg("buf type     : '%s'\n", vidc_buffer_type2str(property->buf_type));
        log_dbg("actual count : %d\n", property->actual_count);
        log_dbg("max count    : %d\n", property->max_count);
        log_dbg("min count    : %d\n", property->min_count);
        log_dbg("size         : 0x%08X (dec: %d)\n", property->size, property->size);
        log_dbg("hold count   : %d\n", property->hold_count);
}

static
void print_property_idr_period(vidc_idr_period_type *property)
{
        log_dbg("idr period   : %d\n", property->idr_period);
}

static
void print_property_target_bitrate(vidc_target_bitrate_type *property)
{
        log_dbg("target bitrate   : %d\n", property->target_bitrate);
}

static
void print_property_session_qp(vidc_session_qp_type *property)
{
        log_dbg("i frame qp   : %d\n", property->i_frame_qp);
        log_dbg("p frame qp   : %d\n", property->p_frame_qp);
        log_dbg("b frame qp   : %d\n", property->b_frame_qp);
}

static
void print_property_rate_control(vidc_rate_control_type *property)
{
        log_dbg("rate control: '%s'\n", vidc_rate_control_mode2str(property->rate_control));
}

static
void print_property_i_profile(vidc_profile_type *property)
{
        log_dbg("i profile: %d\n", property->profile);
        log_dbg("i h264 profile: '%s'\n",
                vidc_h264_profile2str((vidc_h264_profile_type)property->profile));
        log_dbg("i hevc profile: '%s'\n",
                vidc_hevc_profile2str((vidc_hevc_profile_type)property->profile));
}

static
void print_property_i_level(vidc_level_type *property)
{
        log_dbg("i level: %d\n", property->level);
        log_dbg("i h264 level: '%s'\n", vidc_h264_level2str((vidc_h264_level_type)property->level));
        log_dbg("i hevc level: '%s'\n", vidc_hevc_level2str((vidc_hevc_level_type)property->level));
}

static
void print_property_enable(vidc_enable_type *property)
{
        log_dbg("enable: '%s'\n", BOOL_STR(property->enable));
}

static
void print_property_i_priority(vidc_priority_type *property)
{
        log_dbg("i priority: '%s'\n", vidc_priority2str(property->priority));
}

static
void print_flags(int flags)
{
        log_dbg("flags         : 0x%08X\n", flags);

        for (int flag = VIDC_FRAME_FLAG_EOS; flag <= VIDC_FRAME_FLAG_LAST; flag = flag << 1) {
                if (flag & flags) {
                        log_dbg("flag          : '%s'\n", vidc_flag2str(flag));
                }
        }

        if (VIDC_FRAME_FLAG_EOSEQ & flags) {
                log_dbg("flag          : '%s'\n", vidc_flag2str(VIDC_FRAME_FLAG_EOSEQ));
        }

        if (VIDC_FRAME_FLAG_DROP_FRAME & flags) {
                log_dbg("flag          : '%s'\n", vidc_flag2str(VIDC_FRAME_FLAG_DROP_FRAME));
        }

        if (VIDC_FRAME_FLAG_DISCONTINUITY & flags) {
                log_dbg("flag          : '%s'\n", vidc_flag2str(VIDC_FRAME_FLAG_DISCONTINUITY));
        }

        if (VIDC_FRAME_FLAG_TEI & flags) {
                log_dbg("flag          : '%s'\n", vidc_flag2str(VIDC_FRAME_FLAG_TEI));
        }
}

void print_property(vidc_property_id_type id, void *property)
{
        log_dbg("Property '%s':\n", vidc_property_id2str(id));

        switch (id) {
        case VIDC_I_PLANE_DEF:
                print_property_plane((vidc_plane_def_type *)property);
                break;
        case VIDC_I_FRAME_SIZE:
                print_property_frame_size((vidc_frame_size_type *)property);
                break;
        case VIDC_I_FRAME_RATE:
                print_property_frame_rate((vidc_frame_rate_type *)property);
                break;
        case VIDC_I_COLOR_FORMAT:
                print_property_color_format((vidc_color_format_config_type *)property);
                break;
        case VIDC_I_BUFFER_REQUIREMENTS:
                print_property_buffer_requirements((vidc_buffer_reqmnts_type *)property);
                break;
        case VIDC_I_SESSION_CODEC:
                print_property_session((vidc_session_codec_type *)property);
                break;
        case VIDC_I_ENC_INTRA_PERIOD:
                print_property_intra_period((vidc_iperiod_type *)property);
                break;
        case VIDC_I_ENC_IDR_PERIOD:
                print_property_idr_period((vidc_idr_period_type *)property);
                break;
        case VIDC_I_VPE_CSC:
                print_property_vpe_csc((vidc_vpe_csc_type *)property);
                break;
        case VIDC_I_ENC_VUI_VIDEO_SIGNAL_INFO:
                print_property_signal_info((vidc_vui_video_signal_info_type *)property);
                break;
        case VIDC_I_VPE_SPATIAL_TRANSFORM:
                print_property_spetial_transform((vidc_spatial_transform_type *)property);
                break;
        case VIDC_I_TARGET_BITRATE:
                print_property_target_bitrate((vidc_target_bitrate_type *)property);
                break;
        case VIDC_I_BUFFER_ALLOC_MODE:
                print_property_alloc_mode((vidc_buffer_alloc_mode_type *)property);
                break;
        case VIDC_I_ENC_SESSION_QP:
                print_property_session_qp((vidc_session_qp_type *)property);
                break;
        case VIDC_I_ENC_RATE_CONTROL:
                print_property_rate_control((vidc_rate_control_type *)property);
                break;
        case VIDC_I_PROFILE:
                print_property_i_profile((vidc_profile_type *)property);
                break;
        case VIDC_I_LEVEL:
                print_property_i_level((vidc_level_type *)property);
                break;
        case VIDC_I_ENC_SYNC_FRAME_SEQ_HDR:
                print_property_enable((vidc_enable_type *)property);
                break;
        case VIDC_I_ENC_CONTENT_ADAPTIVE_CODING:
                print_property_enable((vidc_enable_type *)property);
                break;
        case VIDC_I_LIVE:
                print_property_enable((vidc_enable_type *)property);
                break;
        case VIDC_I_PRIORITY:
                print_property_i_priority((vidc_priority_type *)property);
                break;
        default:
                log_err("Don't have printer for '%s' propery id\n",
                        vidc_property_id2str(id));
        }
}

void print_buffer_ctx(vidc_buffer_info_type *ctx)
{
        log_dbg("Buffer ctx :\n");
        log_dbg("buf type       : '%s'\n", vidc_buffer_type2str(ctx->buf_type));
        log_dbg("contiguous     : '%s'\n", BOOL_STR(ctx->contiguous));
        log_dbg("buf size       : %d\n", ctx->buf_size);
        log_dbg("buf addr       : %p\n", ctx->buf_addr);
        log_dbg("extra buf size : %d\n", ctx->extradata_buf_size);
        log_dbg("extra buf addr : %p\n", ctx->extradata_buf_addr);
        log_dbg("pid            : %d\n", ctx->pid);
        log_dbg("buf handle     : %p\n", ctx->buf_handle);
}

void print_frame_ctx(vidc_frame_data_type *ctx)
{
        log_dbg("Frame ctx :\n");
        log_dbg("frame addr    : %p\n", ctx->frame_addr);
        log_dbg("alloc len     : %d\n", ctx->alloc_len);
        log_dbg("data len      : %d\n", ctx->data_len);
        log_dbg("offset        : %d\n", ctx->offset);
        log_dbg("timestamp     : %llu\n", ctx->timestamp);
        print_flags(ctx->flags);
        log_dbg("frm clnt data : %d\n", ctx->frm_clnt_data);
        log_dbg("frame type    : '%s'\n", vidc_frame_type2str(ctx->frame_type));
        log_dbg("buffer type   : '%s'\n", vidc_buffer_type2str(ctx->buf_type));
        log_dbg("frame handle  : %p\n", ctx->frame_handle);
}

