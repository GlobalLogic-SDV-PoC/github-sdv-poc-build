/**
 **************************************************************************************************
 *  @file           : enc-ctx.h
 *  @brief          : Encoder context
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder API
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __ENC_CTX__H__
#define __ENC_CTX__H__

#include "MMThread.h"

#include "enc-state-types.h"
#include "enc-vidc-headers.h"
#include "pfm-file.h"
#include "pfm-queue.h"
#include "pfm-types.h"
#include "utils.h"

#define BUILD_VERSION       "1.0"

typedef enum io_ctx {
        IO_INPUT_CTX  = 0,
        IO_OUTPUT_CTX = 1,
        IO_CTX_COUNT  = 2,
} io_ctx_t;

typedef struct pmem_buffers_ctx_st {
        size_t size;
        size_t count;
        void   **buffers;
        size_t **data_len;
} pmem_buffers_ctx_st_t;

typedef struct image_ctx_st {
        uint32_t width;
        uint32_t height;

        int32_t  stride_y;
        uint32_t height_y;

        int32_t  stride_uv;
        uint32_t height_uv;
} image_ctx_st_t;

typedef struct enc_config_st {
        uint32_t                    width;
        uint32_t                    height;
        uint32_t                    frame_rate;
        uint32_t                    encode_frames;
        uint32_t                    input_buffers;
        uint32_t                    output_buffers;

        vidc_idr_period_type        idr_period;
        vidc_profile_type           profile;
        vidc_level_type             level;
        vidc_entropy_control_type   entropy;
        vidc_db_control_type        db_control;
        vidc_iperiod_type           i_period;
        vidc_rate_control_mode_type rate_control;
        vidc_target_bitrate_type    bitrate;
        vidc_codec_type             codec;
} enc_config_st_t;

typedef struct io_ctx_st {
        uint32_t                 required_buffers;
        uint32_t                 buffer_size;
        vidc_buffer_info_type    **buffers_ctxs;
        vidc_frame_data_type     **frames_ctxs;
        vidc_buffer_reqmnts_type reqmnts;
} io_ctx_st_t;

typedef enum {
        INPUT_BUFFER  = 0,
        OUTPUT_BUFFER = 1,
} buffer_type_t;

typedef struct vidc_ctx_st {
        ioctl_session_t               *vidc_handle;
        vidc_session_codec_type       session_codec;
        vidc_frame_rate_type          frame_rate;
        vidc_color_format_config_type color_format;
        vidc_frame_size_type          frame_size;
        vidc_plane_def_type           plane_def_y;
        vidc_plane_def_type           plane_def_uv;
        vidc_spatial_transform_type   transform;
        vidc_session_qp_type          vidc_qp;
} vidc_ctx_st_t;

typedef struct enc_ctx_st {
        MM_HANDLE            input_lock;
        MM_HANDLE            input_signal;
        MM_HANDLE            input_signal_wait;
        struct queue_st      *input_queue;

        MM_HANDLE            output_lock;
        MM_HANDLE            output_signal;
        MM_HANDLE            output_signal_wait;
        struct queue_st      *output_queue;

        MM_HANDLE            status_signal;
        MM_HANDLE            status_signal_wait;
        MM_HANDLE            lock;
        state_t              state;
        status_t             status;

        bool                 input_eos_flag;
        bool                 output_eos_flag;

        int32_t              input_frame_count;
        int32_t              output_frame_count;
        int32_t              input_frame_obtained;
        int32_t              output_frame_obtained;

        uint32_t             processed_frames;
        int64_t              time_stamp_Lfile;
        int64_t              time_stamp_interval;

        struct io_ctx_st     io_ctxs[IO_CTX_COUNT];
        struct vidc_ctx_st   vidc_ctx;
        struct enc_config_st config;
} enc_ctx_st_t;

#endif /* __ENC_CTX__H__ */

