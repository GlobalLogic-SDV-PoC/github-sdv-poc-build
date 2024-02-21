#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include "fw_img_lib.h"

#define SAIL_FW1 "sailhyp.elf"
#define SAIL_FW2 "sailsw1.elf"
#define SAIL_FW3 "sailsw2.elf"
#define SAIL_FW4 "sailsw3.elf"

#define SA9000_FW1  "fw1.bin"
#define SA9000_FW5  "fw5.bin"
#define SA9000_FW9  "fw9.bin"
#define SA9000_FW10 "fw10.bin"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

struct fwimg_parts sail_partitions_zipped[] = {
        {"SAIL_HYP", SAIL_FW1 ".gz", FWIMG_FILE_ZIPPED},
        {"SAIL_SW1", SAIL_FW2 ".gz", FWIMG_FILE_ZIPPED},
        {"SAIL_SW2", SAIL_FW3 ".gz", FWIMG_FILE_ZIPPED},
        {"SAIL_SW3", SAIL_FW4 ".gz", FWIMG_FILE_ZIPPED}
};


struct fwimg_parts md_partitions_zipped[] = {
        {"MD_ABL",         "abl_fastboot.elf.gz",    FWIMG_FILE_ZIPPED},
        {"MD_AOP",         "aop.mbn.gz",             FWIMG_FILE_ZIPPED},
        {"MD_BOOT",        "boot_qdrive.img.gz",     FWIMG_FILE_ZIPPED},
        {"MD_CPUCP",       "cpucp.elf.gz",           FWIMG_FILE_ZIPPED},
        {"MD_DDR",         "zeros_5sectors.bin.gz",  FWIMG_FILE_ZIPPED},
        {"MD_DEVCFG",      "devcfg.mbn.gz",          FWIMG_FILE_ZIPPED},
        {"MD_DSPFW",       "dspnonfusafw.bin.gz",    FWIMG_FILE_ZIPPED},
        {"MD_DSPLIB",      "dspnonfusalib.bin.gz",   FWIMG_FILE_ZIPPED},
        {"MD_HYP",         "mifs_hyp_qdrive.img.gz", FWIMG_FILE_ZIPPED},
        {"MD_IFS2",        "ifs2_qdrive.img.gz",     FWIMG_FILE_ZIPPED},
        {"MD_IMAGEFV",     "imagefv.elf.gz",         FWIMG_FILE_ZIPPED},
        {"MD_KEYMASTER",   "keymint.mbn.gz",         FWIMG_FILE_ZIPPED},
        {"MD_LOGFS",       "logfs_ufs_8mb.bin.gz",   FWIMG_FILE_ZIPPED},
        {"MD_MODEM",       "NON-HLOS.bin.gz",        FWIMG_FILE_ZIPPED},
        {"MD_MULTIIMGOEM", "multi_image.mbn.gz",     FWIMG_FILE_ZIPPED},
        {"MD_PERSIST",     "persist_qnx.img.gz",     FWIMG_FILE_ZIPPED},
        {"MD_SHRM",        "shrm.elf.gz",            FWIMG_FILE_ZIPPED},
        {"MD_SYSTEM",      "system_qdrive.img.gz",   FWIMG_FILE_ZIPPED},
        {"MD_TZ",          "tz.mbn.gz",              FWIMG_FILE_ZIPPED},
        {"MD_XBL",         "xbl.elf.gz",             FWIMG_FILE_ZIPPED},
        {"MD_XBL_CONFIG",  "xbl_config.elf.gz",      FWIMG_FILE_ZIPPED},
};

struct fwimg_parts sa9000_partitions_zipped[] = {
        {"SA9000_FW1",  SA9000_FW1  ".gz", FWIMG_FILE_ZIPPED},
        {"SA9000_FW5",  SA9000_FW5  ".gz", FWIMG_FILE_ZIPPED},
        {"SA9000_FW9",  SA9000_FW9  ".gz", FWIMG_FILE_ZIPPED},
        {"SA9000_FW10", SA9000_FW10 ".gz", FWIMG_FILE_ZIPPED},
};

#define SAIL_ZIPPED_IMAGE "ctx_sail_zipped.bin"
#define MD_ZIPPED_IMAGE "ctx_md_zipped.bin"
#define SA9000_ZIPPED_IMAGE "ctx_sa9000_zipped.bin"

int main(int argc, char **argv)
{
        int ret = 0;

        ret = fwimg_create_image(SAIL_ZIPPED_IMAGE, sail_partitions_zipped,
                                 ARRAY_SIZE(sail_partitions_zipped), NULL);
        if (ret != 0) {
                return ret;
        }

        ret = fwimg_create_image(MD_ZIPPED_IMAGE, md_partitions_zipped,
                                 ARRAY_SIZE(md_partitions_zipped), NULL);
        if (ret != 0) {
                return ret;
        }

        ret = fwimg_create_image(SA9000_ZIPPED_IMAGE, sa9000_partitions_zipped,
                                 ARRAY_SIZE(sa9000_partitions_zipped), NULL);
        if (ret != 0) {
                return ret;
        }

        ret = fwimg_extract_files(SA9000_ZIPPED_IMAGE, "./", NULL);
        if (ret != 0) {
                return ret;
        }

        ret = fwimg_extract_files(SAIL_ZIPPED_IMAGE, "./", NULL);
        if (ret != 0) {
                return ret;
        }

        ret = fwimg_extract_files(MD_ZIPPED_IMAGE, "./", NULL);

        return ret;
}

