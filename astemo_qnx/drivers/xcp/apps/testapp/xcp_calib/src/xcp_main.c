#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "A2L.h"
#include "ecu.h"
#include "main_cfg.h"
#include "platform.h"
#include "util.h"
#include "xcpLite.h"
#include "xcpServer.h"
#include "xcp_lib.h"
#include "xcp-logger.h"

/* ***************************** Defines ************************************ */

#define A2L_FILE_NAME                  "/tmp/xcp_calib.a2l"
#define OPTION_ADDRESS                 NULL
#define OPTION_PORT                    5556
#define OPTION_TCP                     false

/* ************************************************************************** */

/* ********************** Typedefs and variables **************************** */


/* ************************************************************************** */

/* **************************** Functions *********************************** */

/* Create A2L file */

static BOOL createA2L()
{
        if (!A2lOpen(A2L_FILE_NAME, OPTION_A2L_PROJECT_NAME)) {
                return FALSE;
        }

        ecuCreateA2lDescription();
        A2lCreateParameterWithLimits(gDebugLevel, A2L_TYPE_UINT32,
                                     "Console output verbosity", "", 0, 100);
        A2lCreate_IF_DATA(OPTION_TCP, OPTION_ADDRESS, OPTION_PORT);
        A2lClose();

        return TRUE;
}

extern void ecuInit();

int main(int argc, char **argv)
{
        T_XCP_CONFIG config = {
                .PortNo = OPTION_PORT,
                .UseTcp = OPTION_TCP
        };

        /* Defines number of events in the above stated config */
        const uint32_t event_num = 0;

        /* Initialize XCP Server and Events */
        if (XcpLib_Init(&config, event_num)) {
                log_info("XcpLib_Init OK\n");
        } else {
                log_err("XcpLib_Init Error\n");
        }

        ecuInit();

        /* Create A2L file */
        if (createA2L()) {
                log_info("A2l file created\n");
        } else {
                log_err("A2l file creation failed\n");
        }

        tXcpThread t2;

        /* Cyclic task */
        create_thread(&t2, ecuTask);

        /* Loop */
        for (;;) {
                sleepMs(100);

                /* Check if the XCP server is running */
                if (!XcpServerStatus()) {
                        log_err("\nXCP Server failed\n");
                        break;
                }
        }

        cancel_thread(t2);
        XcpServerShutdown();
        socketCleanup();

        return 0;
}
