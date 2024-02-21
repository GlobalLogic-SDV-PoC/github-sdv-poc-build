/**
 **************************************************************************************************
 *  @file           : utils.c
 *  @brief          : Utils API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Utils API for parsing command line, printing hex dump
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include <stdbool.h>
#include <string.h>

#include "enc-logger.h"
#include "pfm-stdlib.h"
#include "pfm-string.h"
#include "pfm-types.h"

#define BYTES_PER_LINE     16

/* Template for one byte in hex dump '0xFF '*/
#define CHARS_FOR_ONE_BYTE 5

static
char *skip_leading_blank(char *str)
{
        char *p = str;

        while ((*p == ' ') || (*p == '\t')) {
                p++;
        }

        return p;
}

static
void trim_blank(char *str)
{
        char *p = str;

        while ((*p != ' ') && (*p != '\t') && (*p != '\0')) {
                p++;
        }

        *p = '\0';
}

static
void make_lower_case(char *str)
{
        while (*str) {
                if (('A' <= *str) && (*str <= 'Z')) {
                        *str = 'a' + (*str - 'A');
                }

                str++;
        }
}

bool same_key(char *str, const char *key)
{
        char *p = NULL;

        p = skip_leading_blank(str);
        trim_blank(p);

        if (strlen(p) != strlen(key)) {
                return false;
        }

        make_lower_case(p);

        while (*p) {
                if (*p != *key) {
                        return false;
                }

                p++;
                key++;
        }

        return true;
}

static
char *find_delimiter(char *line, char delimiter)
{
        char *p = line;

        while (*p) {
                if (*p == delimiter) {
                        return p;
                }

                p++;
        }

        return NULL;
}

int get_key_value_pair(char **key, char **value, char *line)
{
        int rc = ERROR;
        char *p = NULL;

        p = find_delimiter(line, '=');
        if (NULL != p) {
                *p = '\0';
                *key = line;
                *value = skip_leading_blank(p + 1);
                trim_blank(*value);
                rc = EOK;
        }

        return rc;
}

int get_next_command(int argc, char **argv, int *position)
{
        char rc = 0;
        int i = *position;

        while (i < argc) {
                if (argv[i][0] == '-') {
                        rc = argv[i][1];

                        i++;

                        break;
                }

                i++;
        }

        if (i >= argc) {
                rc = 0;
                i = 0;
        }

        *position = i;

        return rc;
}

void log_hex_dump(char *data, int count)
{
        char *line = NULL;
        char *line_ptr = NULL;
        char byte = 0;

        /* Always be one first line at 0 position */
        int lines = count / BYTES_PER_LINE + 1;

        /* ASCIZ string. 16 bytes per line aka '0xFF '*/
        int line_size = BYTES_PER_LINE * CHARS_FOR_ONE_BYTE + 1;

        log_dbg("Hex dump:\n");

        line = pfm_calloc(1, line_size);
        if (NULL == line) {
                log_err("Failed to allocate line\n");

                return;
        }

        for (int j = 0; j < lines; j++) {
                pfm_memset(line, 0, line_size);

                for (int i = 0; i < BYTES_PER_LINE && j * BYTES_PER_LINE + i < count; i++) {
                        line_ptr = &line[i * CHARS_FOR_ONE_BYTE];
                        byte = data[BYTES_PER_LINE * j + i];
                        sprintf(line_ptr, "0x%02X ", byte);
                }

                log_dbg("'%s'\n", line);
        }

        pfm_free(line);
}

