/**
 **************************************************************************************************
 *  @file           : fw_img_lib.h
 *  @brief          : Firmware Image processing Library
 **************************************************************************************************
 *  @author     Vitaliy Vasylskyy
 *
 *  @description:
 *  Library supports building of firmware image consistinng of different file partitions,
 * as well as reversed operation of extracting file from the image
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 **************************************************************************************************
 **/
#pragma once

/* Maximum partition name size*/
#define FWIMG_MAX_PART_NAME 256

/* CTX image magic */
#define FWIMG_CTX_MAGIC (0xACEACEBABEDEAD)

/* Image files can be placed as is (RAW) or zipped */
enum FWIMG_FILE_ATTR {
        FWIMG_FILE_RAW = 1,
        FWIMG_FILE_ZIPPED,
};

/* Context of the particular image file */
struct fwimg_file {
        /* destination partition (real or virtual) */
        char partition_name[FWIMG_MAX_PART_NAME];

        /* offset of the particular file in the image */
        uint64_t offset;

        /* size of the particular file in the image */
        uint64_t size;

        /* attributes of the particular file in the image */
        enum FWIMG_FILE_ATTR attrs;

        /* crc32 sum of the all fields of this structure and the file itself */
        uint32_t crc32;
}
__attribute__ ((packed));

/* Context of the particular image file */
struct fwimg_ctx {
        /* Firmware image magic */
        uint64_t magic;

        /* Amount of files in the image*/
        uint32_t file_count;

        /* crc32 of all above stated fields of this stucture (magic, file_count) */
        uint32_t          crc32;
        struct fwimg_file *files;
}
__attribute__ ((packed));

/* Structure used as input to fwimg_create_image() to define the set of files and partitions for image creation */
struct fwimg_parts {
        /* destination partition (real or virtual) that copied to struct fwimg_file partition_name */
        const char *partition;

        /* file that corresponds to the partition */
        const char *filename;

        /* file attributes */
        enum FWIMG_FILE_ATTR attrs;
};

/**
 * @brief      Creates firmware image from the set of partition files.
 *
 * @param[in ]          ctx_file           File name for image to be created
 * @param[in ]          parts              Set of files and partitions
 * @param[in ]          parts_count   Amount of images in parts structure
 * @param[out ]        image_ctx     Created image context structure (can be NULL if not needed)
 * @return                 Returns 0 on success , negative value on failure.
 */
int fwimg_create_image(const char *ctx_file, struct fwimg_parts *parts,
        uint32_t parts_count, struct fwimg_ctx *image_ctx);

/**
 * @brief      Extracts files from the image and unzip them if needed
 *
 * @detail     Extracted file names are constructed from partition_name plus
 *                  ".bin" or ".gz" extention depending from file attributes
 *
 * @param[in ]          ctx_file             File name for image to be created
 * @param[in ]          extract_folder  Folder for files to extract
 * @param[out ]        image_ctx     Created image context structure (can be NULL if not needed)
 * @return                 Returns 0 on success , negative value on failure.
 */
int fwimg_extract_files(const char *ctx_file, const char *extract_folder, struct
        fwimg_ctx *image_ctx);

