/**
 **************************************************************************************************
 *  @file           : client-settings.c
 *  @brief          : Printing client settings
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Printing client settings
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "client-ctx.h"
#include "enc-logger.h"
#include "enc-vidc-converters.h"
#include "enc-vidc-headers.h"
#include "pfm-string.h"

void set_default_settings(client_ctx_st_t *ctx)
{
        pfm_memset(&ctx->config, 0, sizeof(enc_config_st_t));

        ctx->config.width = DEFAULT_WIDTH;
        ctx->config.height = DEFAULT_HEIGHT;
        ctx->config.frame_rate = DEFAULT_FRAME_RATE;
        ctx->config.encode_frames = DEFAULT_NUM_FRAMES_TO_ENCODE;
        ctx->config.rate_control = DEFAULT_RATE_CONTROL;
        ctx->config.bitrate.target_bitrate = DEFAULT_TARTGET_BITRATE;
        ctx->config.codec = DEFAULT_CODEC;
        ctx->config.i_period.p_frames = DEFAULT_NUM_P_BET_2I;
        ctx->config.i_period.b_frames = DEFAULT_NUM_B_BET_2I;
        ctx->config.idr_period.idr_period = DEFAULT_IDR_PERIOD;
        ctx->config.profile.profile = DEFAULT_H265_PROFILE;
        ctx->config.level.level = DEFAULT_H265_LEVEL;
        ctx->config.entropy.entropy_mode = DEFAULT_ENTROPY_MODE;
        ctx->config.entropy.cabac_model = DEFAULT_CABAC_MODEL;
        ctx->config.db_control.db_mode = DEFAULT_DEBLOCKING_MODE;
        ctx->config.db_control.slice_alpha_offset = DEFAULT_SLICE_ALPHA_OFFSET;
        ctx->config.db_control.slice_beta_offset = DEFAULT_SLICE_BETA_OFFSET;
        ctx->config.input_buffers = DEFAULT_INPUT_BUFFER_REQ;
        ctx->config.output_buffers = DEFAULT_OUTPUT_BUFFER_REQ;
}

void print_settings(client_ctx_st_t *ctx)
{
        log_info("Input file      (-i) : %s\n", ctx->files[INPUT_FILE].name);
        log_info("Output file     (-o) : %s\n", ctx->files[OUTPUT_FILE].name);
        log_info("Frame width     (-w) : %d\n", ctx->config.width);
        log_info("Frame height    (-h) : %d\n", ctx->config.height);
        log_info("Frames count    (-n) : %d [0 means all]\n", ctx->config.encode_frames);
        log_info("Input FPS       (-f) : %d\n", ctx->config.frame_rate);
        log_info("Rate control    (-c) : %s\n",
                 vidc_rate_control_mode2str(ctx->config.rate_control));
        log_info("Bit rate        (-r) : %d\n", ctx->config.bitrate.target_bitrate);
        log_info("Number P frames (-p) : %d\n", ctx->config.i_period.p_frames);
        log_info("Number B frames (-b) : %d\n", ctx->config.i_period.b_frames);
        log_info("Input buffers   (-x) : %d [0 means minimum]\n",
                 ctx->config.input_buffers);
        log_info("Output buffers  (-y) : %d [0 means minimum]\n",
                 ctx->config.output_buffers);
        log_info("Idr period           : %d\n", ctx->config.idr_period.idr_period);
        log_info("Entropy Mode         : %s\n",
                vidc_entropy_mode2str(ctx->config.entropy.entropy_mode));

        if (ctx->config.entropy.entropy_mode == VIDC_ENTROPY_MODE_CABAC) {
                log_info("Cabac context model  : 0x%x\n",
                         ctx->config.entropy.cabac_model);
        }

        log_info("Deblocking mode      : %s\n",
                 vidc_deblock_mode2str(ctx->config.db_control.db_mode));
        log_info("Slice Alpha Offset   : %d\n",
                 ctx->config.db_control.slice_alpha_offset);
        log_info("Slice Beta Offset    : %d\n",
                 ctx->config.db_control.slice_beta_offset);

        switch (ctx->config.codec) {
        case VIDC_CODEC_H264:
                log_info("Codec           (-t) : H264\n");
                log_info("Profile              : %s\n",
                         vidc_h264_profile2str(ctx->config.profile.profile));
                log_info("Level                : %s\n",
                         vidc_h264_level2str(ctx->config.level.level));
                break;
        case VIDC_CODEC_HEVC:
                log_info("Codec           (-t) : H265\n");
                log_info("Profile              : %s\n",
                         vidc_hevc_profile2str(ctx->config.profile.profile));
                log_info("Level                : %s\n",
                         vidc_hevc_level2str(ctx->config.level.level));
                break;
        default:
                log_info("Codec           (-t) : Unknown 0x%X\n", ctx->config.codec);
                log_info("Profile              : 0x%X\n", ctx->config.profile.profile);
                log_info("Level                : 0x%X\n", ctx->config.level.level);
        }
}

