/**
 **************************************************************************************************
 *  @file           : conversion.h
 *  @brief          : Pixel format conversions API header
 **************************************************************************************************
 *  @author     Roman Hakh
 *
 *  @description:
 *      Pixel format conversions API based on C2D library
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 * @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 */

#ifndef __CONVERSION__H__
#define __CONVERSION__H__

#include "c2d2.h"

/**
 * @brief Converts YUV format to another YUV format
 *
 * @param [in] src_surf_def source surface definition to convert
 * @param [in] dst_surf_def destination surface definition to convert
 *
 * @return C2D_STATUS_OK if the conversion succeeded, any other in case of failure.
 */
C2D_STATUS convert_yuv_to_yuv(C2D_YUV_SURFACE_DEF *src_surf_def,
        C2D_YUV_SURFACE_DEF *dst_surf_def);

/**
 * @brief Converts RGB format to YUV format
 *
 * @param [in] src_surf_def source surface definition to convert
 * @param [in] dst_surf_def destination surface definition to convert
 *
 * @return C2D_STATUS_OK if the conversion succeeded, any other in case of failure.
 */
C2D_STATUS convert_rgb_to_yuv(C2D_RGB_SURFACE_DEF *src_surf_def,
        C2D_YUV_SURFACE_DEF *dst_surf_def);

#endif /* __CONVERSION__H__ */

