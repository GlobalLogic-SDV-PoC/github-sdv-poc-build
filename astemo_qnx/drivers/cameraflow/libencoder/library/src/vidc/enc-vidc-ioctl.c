/**
 **************************************************************************************************
 *  @file           : enc-vidc-ioctl.c
 *  @brief          : Encoder VIDC IOCTL operations implementation
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Encoder VIDC IOCTL operations implementation
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "enc-ctx.h"
#include "enc-logger.h"
#include "enc-vidc-converters.h"
#include "enc-vidc-headers.h"
#include "enc-vidc-printing-api.h"
#include "pfm-types.h"

#define VIDC_IOCTL_NODE "VideoCore/vidc_drv"

int vidc_open(enc_ctx_st_t *ctx, callback_handler_t callback)
{
        ioctl_callback_t vidc_callback = {0};

        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        vidc_callback.handler = callback;
        vidc_callback.data = (void *)ctx;

        log_dbg("Try open VIDC device\n");

        ctx->vidc_ctx.vidc_handle = device_open(VIDC_IOCTL_NODE, &vidc_callback);
        if (NULL == ctx->vidc_ctx.vidc_handle) {
                log_err("Failed to open VIDC device\n");

                return ERROR;
        }

        return EOK;
}

void vidc_close(enc_ctx_st_t *ctx)
{
        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return;
        }

        if (NULL == ctx->vidc_ctx.vidc_handle) {
                log_err("Failed to close VIDC driver. Error: handle is NULL\n");

                return;
        }

        device_close(ctx->vidc_ctx.vidc_handle);
}

int vidc_start(enc_ctx_st_t *ctx)
{
        int rc = VIDC_ERR_NONE;
        const uint32_t ioctl = VIDC_IOCTL_START;

        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        log_dbg("Try to start. Send ioctl cmd: '%s'\n", vidc_ioctl2str(ioctl));

        rc = device_ioctl(ctx->vidc_ctx.vidc_handle, ioctl, NULL, 0, NULL, 0);
        if (VIDC_ERR_NONE != rc) {
                log_err("Failed to start VIDC interaction. Error: %s\n", vidc_status2str(rc));

                return ERROR;
        }

        return EOK;
}

int vidc_stop(enc_ctx_st_t *ctx)
{
        int rc = VIDC_ERR_NONE;
        const uint32_t ioctl = VIDC_IOCTL_STOP;

        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        log_dbg("Try to stop. Send ioctl cmd: '%s'\n", vidc_ioctl2str(ioctl));

        rc = device_ioctl(ctx->vidc_ctx.vidc_handle, ioctl, NULL, 0, NULL, 0);
        if (VIDC_ERR_NONE != rc) {
                log_err("Failed to stop VIDC interaction. Error: %s\n", vidc_status2str(rc));

                return ERROR;
        }

        return EOK;
}

int vidc_set_buffer(enc_ctx_st_t *ctx, uint8_t *buffer)
{
        int rc = VIDC_ERR_NONE;
        const uint32_t ioctl = VIDC_IOCTL_SET_BUFFER;
        const size_t str_size = sizeof(vidc_buffer_info_type);

        if (NULL == ctx || NULL == buffer) {
                log_err("Invalid input: ctx = %p, buffer = %p\n", ctx, buffer);

                return EINVAL;
        }

        log_dbg("Try to set buffer. Send ioctl cmd: '%s'\n", vidc_ioctl2str(ioctl));

        rc = device_ioctl(ctx->vidc_ctx.vidc_handle, ioctl, buffer, str_size, NULL, 0);
        if (VIDC_ERR_NONE != rc) {
                log_err("Failed to set buffer. Error: %s\n", vidc_status2str(rc));

                return ERROR;
        }

        return EOK;
}

int vidc_free_buffer(enc_ctx_st_t *ctx, uint8_t *buffer)
{
        int rc = VIDC_ERR_NONE;
        const uint32_t ioctl = VIDC_IOCTL_FREE_BUFFER;
        const size_t str_size = sizeof(vidc_buffer_info_type);

        if (NULL == ctx || NULL == buffer) {
                log_err("Invalid input: ctx = %p, buffer = %p\n", ctx, buffer);

                return EINVAL;
        }

        log_dbg("Try to free buffer. Send ioctl cmd: '%s'\n", vidc_ioctl2str(ioctl));

        rc = device_ioctl(ctx->vidc_ctx.vidc_handle, ioctl, buffer, str_size, NULL, 0);
        if (VIDC_ERR_NONE != rc) {
                log_err("Failed to free buffer. Error: %s\n", vidc_status2str(rc));

                return ERROR;
        }

        return EOK;
}

int vidc_fill_frame(enc_ctx_st_t *ctx, vidc_frame_data_type *frame_ctx)
{
        int rc = VIDC_ERR_NONE;
        const uint32_t ioctl = VIDC_IOCTL_FILL_OUTPUT_BUFFER;
        const size_t str_size = sizeof(vidc_frame_data_type);

        if (NULL == ctx || NULL == frame_ctx) {
                log_err("Invalid input: ctx = %p, frame_ctx = %p\n", ctx, frame_ctx);

                return EINVAL;
        }

        log_dbg("Try to fill frame. Send ioctl cmd: '%s'\n", vidc_ioctl2str(ioctl));

        print_frame_ctx(frame_ctx);

        rc = device_ioctl(ctx->vidc_ctx.vidc_handle, ioctl, (uint8 *)frame_ctx, str_size, NULL, 0);
        if (VIDC_ERR_NONE != rc) {
                log_err("Failed to fill frame. Error: %s\n", vidc_status2str(rc));

                return ERROR;
        }

        return EOK;
}

int vidc_empty_frame(enc_ctx_st_t *ctx, vidc_frame_data_type *frame_ctx)
{
        int rc = VIDC_ERR_NONE;
        const uint32_t ioctl = VIDC_IOCTL_EMPTY_INPUT_BUFFER;
        const size_t str_size = sizeof(vidc_frame_data_type);

        if (NULL == ctx || NULL == frame_ctx) {
                log_err("Invalid input: ctx = %p, frame_ctx = %p\n", ctx, frame_ctx);

                return EINVAL;
        }

        log_dbg("Try to empty frame. Send ioctl cmd: '%s'\n", vidc_ioctl2str(ioctl));

        print_frame_ctx(frame_ctx);

        rc = device_ioctl(ctx->vidc_ctx.vidc_handle, ioctl, (uint8 *)frame_ctx, str_size, NULL, 0);
        if (VIDC_ERR_NONE != rc) {
                log_err("Failed to empty frame. Error: %s\n", vidc_status2str(rc));

                return ERROR;
        }

        return EOK;
}

int vidc_load_resources(enc_ctx_st_t *ctx)
{
        int rc = VIDC_ERR_NONE;
        const uint32_t ioctl = VIDC_IOCTL_LOAD_RESOURCES;

        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        log_dbg("Try to load resources. Send ioctl cmd: '%s'\n", vidc_ioctl2str(ioctl));

        rc = device_ioctl(ctx->vidc_ctx.vidc_handle, ioctl, NULL, 0, NULL, 0);
        if (VIDC_ERR_NONE != rc) {
                log_err("Failed to load resources. Error: %s\n", vidc_status2str(rc));

                return ERROR;
        }

        return EOK;
}

int vidc_release_resourses(enc_ctx_st_t *ctx)
{
        int rc = VIDC_ERR_NONE;
        const uint32_t ioctl = VIDC_IOCTL_RELEASE_RESOURCES;

        if (NULL == ctx) {
                log_err("Invalid input: ctx = %p\n", ctx);

                return EINVAL;
        }

        log_dbg("Try release resources. Send ioctl cmd: '%s'\n", vidc_ioctl2str(ioctl));

        rc = device_ioctl(ctx->vidc_ctx.vidc_handle, ioctl, NULL, 0, NULL, 0);
        if (VIDC_ERR_NONE != rc) {
                log_err("Failed to release resources. Error: %s\n", vidc_status2str(rc));

                return ERROR;
        }

        return EOK;
}

int vidc_get_property(enc_ctx_st_t *ctx, vidc_property_id_type id, size_t size, uint8_t *property)
{
        int rc = VIDC_ERR_NONE;
        const uint32_t ioctl = VIDC_IOCTL_GET_PROPERTY;
        uint8 buffer[MAX_IOCTL_BUFFER_SIZE] = {0};
        vidc_drv_property_type *ioctl_prop = (vidc_drv_property_type *)buffer;
        uint32 msg_size = (uint32)(sizeof(vidc_property_hdr_type) + size);

        if (NULL == ctx || NULL == property) {
                log_err("Invalid input: ctx = %p, property = %p\n", ctx, property);

                return EINVAL;
        }

        log_dbg("Try to get '%s' property. Send ioctl cmd: '%s'\n", vidc_property_id2str(id),
                vidc_ioctl2str(ioctl));

        memcpy(ioctl_prop->payload, property, size);

        ioctl_prop->prop_hdr.size = (uint32)size;
        ioctl_prop->prop_hdr.prop_id = id;

        rc = device_ioctl(ctx->vidc_ctx.vidc_handle, ioctl, buffer, msg_size, property, size);
        if (VIDC_ERR_NONE != rc) {
                log_err("Failed to get '%s' property. Error: %s\n",
                        vidc_property_id2str(id), vidc_status2str(rc));

                return ERROR;
        }

        print_property(id, (void *)property);

        return EOK;
}

int vidc_set_property(enc_ctx_st_t *ctx, vidc_property_id_type id, size_t size, uint8_t *property)
{
        int rc = VIDC_ERR_NONE;
        const uint32_t ioctl = VIDC_IOCTL_SET_PROPERTY;
        uint8 ioctl_buffer[MAX_IOCTL_BUFFER_SIZE] = {0};
        vidc_drv_property_type *ioctl_prop = (vidc_drv_property_type *)ioctl_buffer;
        uint32 msg_size = (uint32)(sizeof(vidc_property_hdr_type) + size);

        if (NULL == ctx || NULL == property) {
                log_err("Invalid input: ctx = %p, property = %p\n", ctx, property);

                return EINVAL;
        }

        log_dbg("Try to set '%s' property. Send ioctl cmd: '%s'\n", vidc_property_id2str(id),
                vidc_ioctl2str(ioctl));

        memcpy(ioctl_prop->payload, property, size);

        print_property(id, (void *)property);

        ioctl_prop->prop_hdr.size = (uint32)size;
        ioctl_prop->prop_hdr.prop_id = id;

        rc = device_ioctl(ctx->vidc_ctx.vidc_handle, ioctl, ioctl_buffer, msg_size, NULL, 0);
        if (VIDC_ERR_NONE != rc) {
                log_err("Failed to set '%s' property. Error: %s\n",
                        vidc_property_id2str(id), vidc_status2str(rc));

                return ERROR;
        }

        return EOK;
}

