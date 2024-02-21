/**
 **************************************************************************************************
 *  @file           : conversion.c
 *  @brief          : Implementation of pixel format conversions API
 **************************************************************************************************
 *  @author     Roman Hakh
 *
 *  @description:
 *      Implementation of pixel format conversions API which is based on C2D library.
 *  The purpose is to convert the source pixel format to the destination pixel format.
 *  All the work done on the GPU. The callers shall allocate pmem-buffers and
 *  properly fill in the buffer descriptor before calling the conversion itself.
 *  The conversion functions are blocking.
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 * @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

#include "cam-logger.h"
#include "conversion.h"

static
C2D_STATUS create_host_yuv_surface(uint32_t *surface_id, uint32_t bits,
        C2D_YUV_SURFACE_DEF *surf_def)
{
        C2D_STATUS status = C2D_STATUS_ERROR;

        status = c2dCreateSurface(surface_id, bits,
                                  C2D_SURFACE_YUV_HOST | C2D_SURFACE_WITH_PHYS,
                                  surf_def);
        if (C2D_STATUS_OK != status) {
                log_err("Failed to create YUV surface. Error: %d\n", status);
        }

        return status;
}

static
C2D_STATUS create_host_rgb_surface(uint32_t *surface_id, uint32_t bits,
        C2D_RGB_SURFACE_DEF *surf_def)
{
        C2D_STATUS status = C2D_STATUS_ERROR;

        status = c2dCreateSurface(surface_id, bits,
                                  (C2D_SURFACE_TYPE)(C2D_SURFACE_RGB_HOST | C2D_SURFACE_WITH_PHYS),
                                  surf_def);
        if (C2D_STATUS_OK != status) {
                log_err("Failed to create RGB surface. Error: %d\n", status);
        }

        return status;
}

static
C2D_STATUS convert_pixel_format(uint32_t src_surface_id, uint32_t dst_surface_id)
{
        C2D_STATUS status = C2D_STATUS_ERROR;
        C2D_OBJECT c2dObject = {0};
        C2D_RECT *target_scissor = NULL;
        uint32_t target_mask_id = 0;
        uint32_t target_color_key = 0;

        /* Do the color conversion */
        c2dObject.surface_id = src_surface_id;
        status = c2dDraw(dst_surface_id, C2D_TARGET_ROTATE_0, target_scissor, target_mask_id,
                         target_color_key, &c2dObject, 1);
        if (C2D_STATUS_OK != status) {
                log_err("Failed to convert formats (src_id = %d, dst_id = %d). Error: %d",
                        src_surface_id, dst_surface_id, status);

                return status;
        }

        /* Wait for operation to finish */
        status = c2dFinish(dst_surface_id);
        if (C2D_STATUS_OK != status) {
                log_err("Failed to finish conversion job (src_id = %d, dst_id = %d). Error: %d",
                        src_surface_id, dst_surface_id, status);
        }

        return status;
}

static
C2D_STATUS destroy_surface(uint32_t surface_id)
{
        C2D_STATUS status = C2D_STATUS_ERROR;

        status = c2dDestroySurface(surface_id);
        if (C2D_STATUS_OK != status) {
                log_err("Failed to destroy surface id = %d. Error: %d\n", surface_id, status);
        }

        return status;
}

C2D_STATUS convert_yuv_to_yuv(C2D_YUV_SURFACE_DEF *src_surf_def, C2D_YUV_SURFACE_DEF *dst_surf_def)
{
        C2D_STATUS status = C2D_STATUS_ERROR;
        uint32_t src_id = 0, dst_id = 0;

        status = create_host_yuv_surface(&src_id, C2D_SOURCE, src_surf_def);
        if (C2D_STATUS_OK != status) {
                log_err("Failed to create YUV src surface. Error: %d\n", status);

                return status;
        }

        status = create_host_yuv_surface(&dst_id, C2D_TARGET, dst_surf_def);
        if (C2D_STATUS_OK != status) {
                log_err("Failed to create YUV dst surface. Error: %d\n", status);
                destroy_surface(src_id);

                return status;
        }

        log_info("Created src_surf: %d(%d-pix fmt), dst_surf: %d(%d-pix fmt)\n",
                 src_id, src_surf_def->format, dst_id, dst_surf_def->format, status);

        /* Do the color conversion */
        status = convert_pixel_format(src_id, dst_id);
        if (C2D_STATUS_OK != status) {
                log_err("Failed to convert from %d to %d format. Error: %d\n",
                        src_surf_def->format, dst_surf_def->format, status);
        }

        destroy_surface(dst_id);
        destroy_surface(src_id);

        log_info("Conversion succeeded\n");

        return status;
}

C2D_STATUS convert_rgb_to_yuv(C2D_RGB_SURFACE_DEF *src_surf_def, C2D_YUV_SURFACE_DEF *dst_surf_def)
{
        C2D_STATUS status = C2D_STATUS_ERROR;
        uint32_t src_id, dst_id;

        status = create_host_rgb_surface(&src_id, C2D_SOURCE, src_surf_def);
        if (C2D_STATUS_OK != status) {
                log_err("Failed to create RGB src surface. Error: %d\n", status);

                return status;
        }

        status = create_host_yuv_surface(&dst_id, C2D_TARGET, dst_surf_def);
        if (C2D_STATUS_OK != status) {
                log_err("Failed to create YUV dst surface. Error: %d\n", status);
                destroy_surface(src_id);

                return status;
        }

        log_info("Created src_surf: %d(%d-pix fmt), dst_surf: %d(%d-pix fmt)\n",
                 src_id, src_surf_def->format, dst_id, dst_surf_def->format, status);

        /* Do the color conversion */
        status = convert_pixel_format(src_id, dst_id);
        if (C2D_STATUS_OK != status) {
                log_err("Failed to convert from %d to %d format. Error: %d\n",
                        src_surf_def->format, dst_surf_def->format, status);
        }

        destroy_surface(dst_id);
        destroy_surface(src_id);

        log_info("Conversion succeeded\n");

        return status;
}

