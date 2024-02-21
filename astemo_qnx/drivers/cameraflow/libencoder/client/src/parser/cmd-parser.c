/**
 **************************************************************************************************
 *  @file           : cmd-parser.c
 *  @brief          : Client application command line parser
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Client application command line parser
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include <stdlib.h>

#include "client-ctx.h"
#include "enc-ctx.h"
#include "enc-logger.h"
#include "enc-vidc-headers.h"
#include "pfm-types.h"

#define RATECONTROL_OFF         0
#define RATECONTROL_CBR_CFR     1
#define RATECONTROL_CBR_VFR     2
#define RATECONTROL_VBR_CFR     3
#define RATECONTROL_VBR_VFR     4

static
int parse_arg(char *key, char *value, client_ctx_st_t *ctx)
{
        /* TODO change to getopt */
        if (true == same_key(key, "w")) {
                ctx->config.width = atoi(value);

                log_dbg("width = %d\n", ctx->config.width);
        } else if (true == same_key(key, "h")) {
                ctx->config.height = atoi(value);

                log_dbg("height = %d\n", ctx->config.height);
        } else if (true == same_key(key, "f")) {
                ctx->config.frame_rate = atoi(value);

                log_dbg("Frame rate = %d\n", ctx->config.frame_rate);
        } else if (true == same_key(key, "c")) {
                int value_tmp = atoi(value);

                log_dbg("Rate control = %d\n", value_tmp);

                switch (value_tmp) {
                case RATECONTROL_OFF:
                        ctx->config.rate_control = VIDC_RATE_CONTROL_OFF;
                        break;
                case RATECONTROL_CBR_CFR:
                        ctx->config.rate_control = VIDC_RATE_CONTROL_CBR_CFR;
                        break;
                case RATECONTROL_CBR_VFR:
                        ctx->config.rate_control = VIDC_RATE_CONTROL_CBR_VFR;
                        break;
                case RATECONTROL_VBR_CFR:
                        ctx->config.rate_control = VIDC_RATE_CONTROL_VBR_CFR;
                        break;
                case RATECONTROL_VBR_VFR:
                        ctx->config.rate_control = VIDC_RATE_CONTROL_VBR_VFR;
                        break;
                default:
                        log_err("Invalid rate control = %d\n", value_tmp);

                        return EINVAL;
                }
        } else if (true == same_key(key, "r")) {
                ctx->config.bitrate.target_bitrate = atoi(value);

                log_dbg("bitrate = %d\n", ctx->config.bitrate.target_bitrate);
        } else if (true == same_key(key, "n")) {
                ctx->config.encode_frames = atoi(value);

                log_dbg("Num frames to encode = %d\n", ctx->config.encode_frames);
        } else if (true == same_key(key, "t")) {
                if (same_key(value, "h264")) {
                        ctx->config.codec = VIDC_CODEC_H264;
                } else if (same_key(value, "h265")) {
                        ctx->config.codec = VIDC_CODEC_HEVC;
                } else {
                        log_err("Invalid codec '%s', not supported\n", SAFE_STR(value));

                        return EINVAL;
                }
        } else if (true == same_key(key, "i")) {
                if (strlen(value) >= MAX_FILENAME) {
                        log_err("Invalid input file name '%s'\n", SAFE_STR(value));

                        return EINVAL;
                }

                log_dbg("Input file file name '%s'\n", SAFE_STR(value));

                if (value[0] == '\"' && value[strlen(value) - 1] == '\"') {
                        value[strlen(value) - 1] = 0;
                        value = &value[1];
                }

                std_strlcpy(ctx->files[INPUT_FILE].name, value, (int)strlen(value) + 1);

                ctx->files[INPUT_FILE].flags = MM_FILE_CREATE_R;
        } else if (true == same_key(key, "o")) {
                if (strlen(value) >= MAX_FILENAME) {
                        log_err("Invalid output file name '%s'\n", SAFE_STR(value));

                        return EINVAL;
                }

                log_dbg("Output file file name '%s'\n", SAFE_STR(value));

                if (value[0] == '\"' && value[strlen(value) - 1] == '\"') {
                        value[strlen(value) - 1] = 0;
                        value = &value[1];
                }

                std_strlcpy(ctx->files[OUTPUT_FILE].name, value, (int)strlen(value) + 1);

                ctx->files[OUTPUT_FILE].flags = MM_FILE_CREATE_W_PLUS;
        } else if (true == same_key(key, "p")) {
                ctx->config.i_period.p_frames = atoi(value);

                log_dbg("Number of P frames between two I frames = %d\n",
                        ctx->config.i_period.p_frames);
        } else if (true == same_key(key, "b")) {
                ctx->config.i_period.b_frames = atoi(value);

                log_dbg("Number of B frames between two I frames = %d\n",
                        ctx->config.i_period.b_frames);
        } else if (true == same_key(key, "x")) {
                ctx->config.input_buffers = atoi(value);

                log_dbg("Count input buffers: %d\n", ctx->config.input_buffers);
        } else if (true == same_key(key, "y")) {
                ctx->config.output_buffers = atoi(value);

                log_dbg("Count output buffers: %d\n", ctx->config.output_buffers);
        } else {
                printf("Unrecognized command line key '%s' and value '%s'\n", key, value);

                return EINVAL;
        }

        return EOK;
}

int parse_args(int argc, char **argv, client_ctx_st_t *ctx)
{
        int rc = EOK;
        int position = 0;
        char cmd = '\0';
        char param[2] = {cmd, 0};

        log_dbg("Parse command line arguments");

        cmd = get_next_command(argc, argv, &position);
        while (0 != cmd) {
                param[0] = cmd;
                param[1] = 0;

                rc = parse_arg(param, argv[position], ctx);
                if (EOK != rc) {
                        printf("Failed to parse parameter. Error: %d\n", rc);

                        return rc;
                }

                position++;

                cmd = get_next_command(argc, argv, &position);
        }

        log_dbg("Successfully parsed command line arguments");

        return EOK;
}

void print_usage(char *name)
{
        printf("%s args...\n", name);
        printf("   -w width   <default 3840>\n");
        printf("   -h height  <default 2160>\n");
        printf("   -f fps     <default 30>\n");
        printf("   -c ratecontrol 0=off, 1=CBR_CFR, 2=CBR_VFR, 3=VBR_CBR, 4=VBR_VFR <default 1>\n");
        printf("   -r bitrate <default 64000>\n");
        printf("   -n number of frames to encode <default 0 = all>\n");
        printf("   -t codec (h264, h265 <default h265>)\n");
        printf("   -i input NV12 file\n");
        printf("   -o output file\n");
        printf("   -p number of P frames between two I frames <default 30>\n");
        printf("   -b number of B frames between two I frames <default 0>\n");
        printf("   -x number of input buffer <default 0 = use the minimum requirement>\n");
        printf("   -y number of output buffer <default 0 = use the minimum requirement>\n");
}

