/**
 **************************************************************************************************
 *  @file           : camflow.c
 *  @brief          : Implements camera data flow library API
 **************************************************************************************************
 *  @author     Roman Kovalivskyi
 *
 *  @description:
 *  Implementation of camera data flow library API, which purpose is to receive and process camera
 *  streams based on configured pipeline.
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

#include "cam-logger.h"
#include "camflow.h"

int cdf_init(void)
{
        int rc = EOK;

        rc = cam_log_init(APP_NAME);
        if (EOK != rc) {
                printf("Failed to initialize logger. Error: %d\n", rc);
        }

        return rc;
}

int cdf_deinit(void)
{
        return 0;
}

