/**
 **************************************************************************************************
 *  @file           : camctl.c
 *  @brief          : Camera data flow control application sources
 **************************************************************************************************
 *  @author     Roman Kovalivskyi
 *
 *  @description:
 *  Application for processing streams from camera inputs based on config.
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 */

#include <stdlib.h>

#include "camflow.h"

int main(int argc, char **argv)
{
    cdf_init();

    cdf_deinit();

    return EXIT_SUCCESS;
}
