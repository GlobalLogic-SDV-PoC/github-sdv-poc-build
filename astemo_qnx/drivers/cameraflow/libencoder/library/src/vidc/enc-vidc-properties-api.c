/**
 **************************************************************************************************
 *  @file           : enc-vidc-properties-api.c
 *  @brief          : Encoder VIDC properties API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder VIDC properties API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "enc-logger.h"
#include "enc-vidc-contexts-api.h"
#include "enc-vidc-converters.h"
#include "enc-vidc-headers.h"
#include "enc-vidc-ioctl.h"
#include "enc-vidc-printing-api.h"
#include "pfm-types.h"

static
int vidc_get_common_properties(enc_ctx_st_t *ctx)
{
        int rc = EOK;
        vidc_property_id_type id = VIDC_I_COMMON_START_BASE;
        size_t size = 0;
        uint8_t *property = NULL;

        log_dbg("Try to get common properties\n");

        id = VIDC_I_FRAME_SIZE;
        size = sizeof(vidc_frame_size_type);
        ctx->vidc_ctx.frame_size.buf_type = VIDC_BUFFER_INPUT;
        property = (uint8_t *)&ctx->vidc_ctx.frame_size;

        log_dbg("Get '%s' property\n", vidc_property_id2str(id));

        rc = vidc_get_property(ctx, id, size, property);
        if (EOK != rc) {
                log_err("Failed to get '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_FRAME_RATE;
        size = sizeof(vidc_frame_rate_type);
        ctx->vidc_ctx.frame_rate.buf_type = VIDC_BUFFER_INPUT;
        property = (uint8_t *)&ctx->vidc_ctx.frame_rate;

        log_dbg("Get '%s' property\n", vidc_property_id2str(id));

        rc = vidc_get_property(ctx, id, size, property);
        if (EOK != rc) {
                log_err("Failed to get '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_COLOR_FORMAT;
        size = sizeof(vidc_color_format_config_type);
        ctx->vidc_ctx.color_format.buf_type = VIDC_BUFFER_INPUT;
        property = (uint8_t *)&ctx->vidc_ctx.color_format;

        log_dbg("Get '%s' property\n", vidc_property_id2str(id));

        rc = vidc_get_property(ctx, id, size, property);
        if (EOK != rc) {
                log_err("Failed to get '%s' property. Error: %d\n",
                        vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_PLANE_DEF;
        size = sizeof(vidc_plane_def_type);
        ctx->vidc_ctx.plane_def_y.buf_type = VIDC_BUFFER_INPUT;
        ctx->vidc_ctx.plane_def_y.plane_index = VIDC_Y_PLANE;
        property = (uint8_t *)&ctx->vidc_ctx.plane_def_y;

        log_dbg("Get '%s' property\n", vidc_property_id2str(id));

        rc = vidc_get_property(ctx, id, size, property);
        if (EOK != rc) {
                log_err("Failed to get '%s' Y property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_PLANE_DEF;
        size = sizeof(vidc_plane_def_type);
        ctx->vidc_ctx.plane_def_uv.buf_type = VIDC_BUFFER_INPUT;
        ctx->vidc_ctx.plane_def_uv.plane_index = VIDC_UV_PLANE;
        property = (uint8_t *)&ctx->vidc_ctx.plane_def_uv;

        log_dbg("Get '%s' property\n", vidc_property_id2str(id));

        rc = vidc_get_property(ctx, id, size, property);
        if (EOK != rc) {
                log_err("Failed to get '%s' UV property. Error: %d\n", vidc_property_id2str(id),
                        rc);

                return rc;
        }

        log_dbg("Successfully got common properties\n");

        return rc;
}

static
int vidc_get_buffer_req(enc_ctx_st_t *ctx, vidc_buffer_type type)
{
        int rc = EOK;
        vidc_property_id_type id = VIDC_I_BUFFER_REQUIREMENTS;
        int io_ctx = buffer_type2ctx(type);
        const size_t size = sizeof(vidc_buffer_reqmnts_type);
        vidc_buffer_reqmnts_type *property = &ctx->io_ctxs[io_ctx].reqmnts;

        log_dbg("Try to get '%s' buffer requirements\n", vidc_buffer_type2str(type));

        property->buf_type = type;
        rc = vidc_get_property(ctx, id, size, (uint8_t *)property);
        if (EOK != rc) {
                log_err("Failed to get '%s' property. Error: %d\n",
                        vidc_property_id2str(id), rc);

                return rc;
        }

        if (property->actual_count < ctx->io_ctxs[io_ctx].required_buffers) {
                property->actual_count = ctx->io_ctxs[io_ctx].required_buffers;
        }

        ctx->io_ctxs[io_ctx].required_buffers = property->actual_count;
        ctx->io_ctxs[io_ctx].buffer_size = property->size;

        rc = vidc_set_property(ctx, id, size, (uint8_t *)property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        rc = vidc_get_property(ctx, id, size, (uint8_t *)property);
        if (EOK != rc) {
                log_err("Failed to get '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        log_dbg("Successfully got buffer requirements\n");

        return rc;
}

int vidc_get_properties(enc_ctx_st_t *ctx)
{
        int rc = EOK;

        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        log_dbg("Try to get properties\n");

        rc = vidc_get_common_properties(ctx);
        if (EOK != rc) {
                log_err("Failed to get properties\n");

                return rc;
        }

        ctx->io_ctxs[IO_INPUT_CTX].required_buffers = ctx->config.input_buffers;

        rc = vidc_get_buffer_req(ctx, VIDC_BUFFER_INPUT);
        if (EOK != rc) {
                log_err("Failed to get output buffer requirements\n");

                return rc;
        }

        ctx->io_ctxs[IO_OUTPUT_CTX].required_buffers = ctx->config.output_buffers;

        rc = vidc_get_buffer_req(ctx, VIDC_BUFFER_OUTPUT);
        if (EOK != rc) {
                log_err("Failed to get input buffer requirements\n");

                return rc;
        }

        log_dbg("Successfully got properties\n");

        return rc;
}

/* TODO template function for future purpose */
static
int vidc_set_hevc_properties(enc_ctx_st_t *ctx)
{
        log_dbg("Try to set HEVC properties\n");

        log_dbg("Successfully set HEVC properties\n");

        return EOK;
}

static
int vidc_set_h264_properties(enc_ctx_st_t *ctx)
{
        int rc = EOK;
        size_t str_size = 0;
        uint8_t *property = NULL;
        vidc_property_id_type id = VIDC_I_COMMON_START_BASE;

        log_dbg("Try to set H264 properties\n");

        id = VIDC_I_ENC_H264_ENTROPY_CTRL;
        str_size = sizeof(vidc_entropy_control_type);
        property = (uint8_t *)&ctx->config.entropy;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_ENC_H264_DEBLOCKING;
        str_size = sizeof(vidc_db_control_type);
        property = (uint8_t *)&ctx->config.db_control;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        log_dbg("Successfully set H264 properties\n");

        return rc;
}

int vidc_set_properties(enc_ctx_st_t *ctx)
{
        int rc = EOK;
        size_t str_size = 0;
        uint8_t *property = NULL;
        vidc_property_id_type id = VIDC_I_COMMON_START_BASE;

        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        log_dbg("Try to set properties\n");

        id = VIDC_I_SESSION_CODEC;
        str_size = sizeof(vidc_session_codec_type);
        property = (uint8_t *)&ctx->vidc_ctx.session_codec;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n",
                        vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_FRAME_RATE;
        str_size = sizeof(vidc_frame_rate_type);
        ctx->vidc_ctx.frame_rate.buf_type = VIDC_BUFFER_OUTPUT;
        ctx->vidc_ctx.frame_rate.fps_numerator = ctx->config.frame_rate;
        ctx->vidc_ctx.frame_rate.fps_denominator = VIDC_FPS_DENOMINATOR;
        property = (uint8_t *)&ctx->vidc_ctx.frame_rate;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_FRAME_RATE;
        str_size = sizeof(vidc_frame_rate_type);
        ctx->vidc_ctx.frame_rate.buf_type = VIDC_BUFFER_INPUT;
        ctx->vidc_ctx.frame_rate.fps_numerator = ctx->config.frame_rate;
        ctx->vidc_ctx.frame_rate.fps_denominator = VIDC_FPS_DENOMINATOR;
        property = (uint8_t *)&ctx->vidc_ctx.frame_rate;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_COLOR_FORMAT;
        str_size = sizeof(vidc_color_format_config_type);
        ctx->vidc_ctx.color_format.buf_type = VIDC_BUFFER_INPUT;
        ctx->vidc_ctx.color_format.color_format = VIDC_COLOR_FORMAT_NV12;
        property = (uint8_t *)&ctx->vidc_ctx.color_format;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_FRAME_SIZE;
        str_size = sizeof(vidc_frame_size_type);
        ctx->vidc_ctx.frame_size.buf_type = VIDC_BUFFER_INPUT;
        ctx->vidc_ctx.frame_size.width = ctx->config.width;
        ctx->vidc_ctx.frame_size.height = ctx->config.height;
        property = (uint8_t *)&ctx->vidc_ctx.frame_size;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_FRAME_SIZE;
        str_size = sizeof(vidc_frame_size_type);
        ctx->vidc_ctx.frame_size.buf_type = VIDC_BUFFER_OUTPUT;
        ctx->vidc_ctx.frame_size.width = ctx->config.width;
        ctx->vidc_ctx.frame_size.height = ctx->config.height;
        property = (uint8_t *)&ctx->vidc_ctx.frame_size;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_ENC_INTRA_PERIOD;
        str_size = sizeof(vidc_iperiod_type);
        property = (uint8_t *)&ctx->config.i_period;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_ENC_IDR_PERIOD;
        str_size = sizeof(vidc_idr_period_type);
        property = (uint8_t *)&ctx->config.idr_period;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_ENC_RATE_CONTROL;
        str_size = sizeof(vidc_rate_control_type);
        property = (uint8_t *)&ctx->config.rate_control;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_TARGET_BITRATE;
        str_size = sizeof(vidc_target_bitrate_type);
        property = (uint8_t *)&ctx->config.bitrate;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_PROFILE;
        str_size = sizeof(vidc_profile_type);
        property = (uint8_t *)&ctx->config.profile;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_LEVEL;
        str_size = sizeof(vidc_level_type);
        property = (uint8_t *)&ctx->config.level;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        if (VIDC_CODEC_H264 == ctx->config.codec) {
                rc = vidc_set_h264_properties(ctx);
        } else if (VIDC_CODEC_HEVC == ctx->config.codec) {
                rc = vidc_set_hevc_properties(ctx);
        } else {
                log_err("Incorrect codec type '%s'", vidc_codec2str(ctx->config.codec));

                return EINVAL;
        }

        if (EOK != rc) {
                log_err("Failed to set codec properties. Error: %d\n", rc);

                return rc;
        }

        id = VIDC_I_VPE_SPATIAL_TRANSFORM;
        str_size = sizeof(vidc_spatial_transform_type);
        ctx->vidc_ctx.transform.rotate = VIDC_ROTATE_NONE;
        ctx->vidc_ctx.transform.flip = VIDC_FLIP_NONE;
        property = (uint8_t *)&ctx->vidc_ctx.transform;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        id = VIDC_I_ENC_SESSION_QP;
        str_size = sizeof(vidc_session_qp_type);
        ctx->vidc_ctx.vidc_qp.i_frame_qp = DEFAULT_QUANTIZATION_PARAM;
        ctx->vidc_ctx.vidc_qp.p_frame_qp = DEFAULT_QUANTIZATION_PARAM;
        ctx->vidc_ctx.vidc_qp.b_frame_qp = DEFAULT_QUANTIZATION_PARAM;
        property = (uint8_t *)&ctx->vidc_ctx.vidc_qp;

        log_dbg("Set '%s' property\n", vidc_property_id2str(id));

        rc = vidc_set_property(ctx, id, str_size, property);
        if (EOK != rc) {
                log_err("Failed to set '%s' property. Error: %d\n", vidc_property_id2str(id), rc);

                return rc;
        }

        log_dbg("Successfully set properties\n");

        return rc;
}

