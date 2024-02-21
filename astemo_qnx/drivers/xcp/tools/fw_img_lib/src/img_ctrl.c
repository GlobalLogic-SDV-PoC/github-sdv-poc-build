#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include "fw_img_lib.h"
#include "minigzip.h"
#include "zlib.h"

#ifdef TARGET_X86_BUILD
#include "logger-x86.h"
#else
#include "xcp-logger.h"
#endif



static
uint64_t get_file_size(const char *filename)
{
        struct stat buf = {0};
        int ret = 0;

        ret = stat(filename, &buf);
        if (0 != ret) {
                log_err("Can't stat the fle %s!\n", filename);

                return 0;
        }

        return buf.st_size;
}

static
int fwrite_and_update_crc(uint32_t *crc, const void *buf, uint32_t size, FILE *file)
{
        int ret = 0;

        ret = fwrite(buf, 1, size, file);
        if (ret != size) {
                log_err("File write error\n");

                return -EFAULT;
        }

        *crc = crc32(*crc, buf, size);

        return 0;
}

static
int fread_and_update_crc(uint32_t *crc, void *buf, uint32_t size, FILE *file)
{
        int ret = 0;

        ret = fread(buf, 1, size, file);
        if (ret != size) {
                log_err("File read error\n");

                return -EFAULT;
        }

        *crc = crc32(*crc, buf, size);

        return 0;
}

#define TMP_BUFSIZE (16 * 1048576)
static
int calc_file_crc(const char *filename, uint32_t *crc32)
{
        uint64_t size = 0;
        FILE *file = fopen(filename, "rb");
        static uint8_t buf[TMP_BUFSIZE];
        uint64_t read_size = 0;
        uint32_t crc = *crc32;
        int ret = 0;

        if (NULL == file) {
                log_err("failed to open file for reading\n");

                return -EFAULT;
        }

        size = get_file_size(filename);
        if (0 == size) {
                fclose(file);

                return -ENOENT;
        }

        do {
                read_size = sizeof(buf) <= size ? sizeof(buf) : size;
                if (0 == read_size) {
                        break;
                }

                ret = fread_and_update_crc(&crc, buf, read_size, file);
                if (ret < 0) {
                        fclose(file);

                        return ret;
                }

                size -= read_size;
                ret = feof(file);
        } while (0 == ret);

        *crc32 = crc;
        fclose(file);

        return 0;
}

static
uint32_t calc_fwfile_crc(const struct fwimg_file *file_ctx)
{
        uint32_t crc = 0;

        crc = crc32(crc, (const void *)file_ctx->partition_name, sizeof(file_ctx->partition_name));
        crc = crc32(crc, (const void *)&file_ctx->offset, sizeof(file_ctx->offset));
        crc = crc32(crc, (const void *)&file_ctx->size, sizeof(file_ctx->size));
        crc = crc32(crc, (const void *)&file_ctx->attrs, sizeof(file_ctx->attrs));

        return crc;
}

static
int create_file_ctx(struct fwimg_file *file_ctx, const char *partition, const char *filename,
        enum FWIMG_FILE_ATTR attrs, uint64_t offset)
{
        int ret = 0;
        uint32_t crc = 0;

        ret = strlen(partition);
        if (sizeof(file_ctx->partition_name) <= ret) {
                log_err("Partition name is too long (%d)\n", ret);

                return -EINVAL;
        }

        file_ctx->size = get_file_size(filename);
        if (0 == file_ctx->size) {
                log_err("File size is 0\n");

                return -ENOENT;
        }

        (void)strcpy(file_ctx->partition_name, partition);
        file_ctx->offset = offset;
        file_ctx->attrs = attrs;
        crc = calc_fwfile_crc(file_ctx);
        ret = calc_file_crc(filename, &crc);
        if (ret < 0) {
                return ret;
        }

        file_ctx->crc32 = crc;

        return 0;
}

static
int add_file_to_image(FILE *image, struct fwimg_file *file_ctx, const char *filename)
{
        FILE *file = fopen(filename, "rb");
        static uint8_t buf[TMP_BUFSIZE];
        uint64_t write_size = 0, size = 0;
        uint32_t crc = 0;
        int ret = 0;

        if (NULL == file) {
                log_err("failed to open file for reading\n");

                return -EFAULT;
        }

        crc = calc_fwfile_crc(file_ctx);
        size = file_ctx->size;

        do {
                write_size = sizeof(buf) <= size ? sizeof(buf) : size;
                if (0 == write_size) {
                        break;
                }

                ret = fread(buf, 1, write_size, file);
                if (ret != write_size) {
                        log_err("File read error\n");
                        fclose(file);

                        return -EFAULT;
                }

                ret = fwrite_and_update_crc(&crc, buf, write_size, image);
                if (ret < 0) {
                        fclose(file);

                        return ret;
                }

                size -= write_size;
                ret = feof(file);
        } while (0 == ret);

        if (size > 0) {
                log_err("Error: Partial file write due to EOF\n");
                ret = -EFAULT;
        }

        if (file_ctx->crc32 != crc) {
                log_err("CRC error: calculated 0x%x, original: 0x%x\n", crc, file_ctx->crc32);
                ret = -EFAULT;
        }

        fclose(file);

        return ret;
}

int fwimg_create_image(const char *ctx_file, struct fwimg_parts *parts, uint32_t parts_count,
        struct fwimg_ctx *image_ctx)
{
        int ret = 0;
        FILE *file = NULL;
        int i = 0;
        struct fwimg_ctx ctx = {0};
        uint32_t crc = 0;

        /* Offset for filst file is size of ctx minus ctx->files as pointer is not stored in the file */
        uint64_t offset = sizeof(ctx) - sizeof(ctx.files) + parts_count * sizeof(*ctx.files);

        if (NULL == ctx_file) {
                log_err("ctx file name undefined\n");

                return -EINVAL;
        }

        if (NULL == parts || 0 == parts_count) {
                log_err("Image parameters error\n");

                return -EINVAL;
        }

        log_info("Create image file %s...\n", ctx_file);

        ret = access(ctx_file, F_OK);
        if (0 != ret) {
                /*No ctx file, let's create it */
                file = fopen(ctx_file, "wb");
                if (NULL == file) {
                        log_err("failed to open file for writing\n");

                        return -EINVAL;
                }
        } else {
                log_err("File exist, and updating is not supported at the moment\n");

                return -EINVAL;
        }

        ctx.magic = FWIMG_CTX_MAGIC;
        ctx.file_count = parts_count;

        ret = fwrite_and_update_crc(&crc, (void *)&ctx.magic, sizeof(ctx.magic), file);
        if (ret < 0) {
                fclose(file);

                return ret;
        }

        ret = fwrite_and_update_crc(&crc, (void *)&ctx.file_count, sizeof(ctx.file_count), file);
        if (ret < 0) {
                fclose(file);

                return ret;
        }

        ret = fwrite((void *)&crc, 1, sizeof(crc), file);
        if (ret != sizeof(ctx.crc32)) {
                log_err("File write error\n");
                fclose(file);

                return -EFAULT;
        }

        ctx.files = calloc(parts_count, sizeof(*ctx.files));
        if (NULL == ctx.files) {
                log_err("Memory allocation error\n");
                fclose(file);

                return -ENOMEM;
        }

        for (i = 0; i < parts_count; i++) {
                ret = create_file_ctx(&ctx.files[i], parts[i].partition, parts[i].filename,
                                      parts[i].attrs, offset);
                if (ret < 0) {
                        fclose(file);
                        free(ctx.files);

                        return ret;
                }

                ret = fwrite(&ctx.files[i], 1, sizeof(*ctx.files), file);
                if (ret != sizeof(*ctx.files)) {
                        log_err("File write error\n");

                        return -EFAULT;
                }

                offset += ctx.files[i].size;
        }

        for (i = 0; i < parts_count; i++) {
                ret = add_file_to_image(file, &ctx.files[i], parts[i].filename);
                if (ret < 0) {
                        fclose(file);
                        free(ctx.files);

                        return ret;
                }
        }

        fclose(file);
        if (NULL != image_ctx) {
                *image_ctx = ctx;
        } else {
                free(ctx.files);
        }

        log_info("Success\n");

        return 0;
}

static
int get_file_from_image(FILE *image, const char *filename, uint64_t size, uint32_t *crc)
{
        FILE *file = fopen(filename, "wb");
        static uint8_t buf[TMP_BUFSIZE];
        uint64_t read_size = 0;
        int ret = 0;

        if (NULL == file) {
                log_err("failed to open file for writing\n");

                return -EFAULT;
        }

        do {
                read_size = sizeof(buf) <= size ? sizeof(buf) : size;
                if (0 == read_size) {
                        break;
                }

                ret = fread(buf, 1, read_size, image);
                if (ret != read_size) {
                        log_err("File read error\n");
                        fclose(file);

                        return -EFAULT;
                }

                ret = fwrite_and_update_crc(crc, buf, read_size, file);
                if (ret < 0) {
                        fclose(file);

                        return ret;
                }

                size -= read_size;
                ret = feof(image);
        } while (0 == ret);

        if (size > 0) {
                log_err("Error: Partial file read due to EOF\n");
                ret = -EFAULT;
        }

        fclose(file);

        return ret;
}

static
char *build_zipped_fname(const char *partition, const char *extract_folder)
{
        const char *gz_ext = ".gz";
        char *fname = NULL;
        uint32_t alloc_size = 0;

        alloc_size = strlen(partition) + strlen(gz_ext) + strlen(extract_folder) + 1;
        fname = calloc(1, alloc_size);
        (void)strncpy(fname, extract_folder, alloc_size);
        (void)strncat(fname, partition, alloc_size);
        (void)strncat(fname, gz_ext, alloc_size);

        return fname;
}

static
char *build_raw_fname(const char *partition, const char *extract_folder)
{
        const char *raw_ext = ".bin";
        char *fname = NULL;
        uint32_t alloc_size = 0;

        alloc_size = strlen(partition) + strlen(raw_ext) + strlen(extract_folder) + 1;
        fname = calloc(1, alloc_size);
        if (NULL == fname) {
                log_err("Memory allocation error\n");

                return NULL;
        }

        (void)strncpy(fname, extract_folder, alloc_size);
        (void)strncat(fname, partition, alloc_size);
        (void)strncat(fname, raw_ext, alloc_size);

        return fname;
}

static
char *build_image_fname(const struct fwimg_file *file_ctx, const char *extract_folder)
{
        char *fname = NULL;

        if (FWIMG_FILE_RAW == file_ctx->attrs) {
                fname = build_raw_fname(file_ctx->partition_name, extract_folder);
        } else {
                fname = build_zipped_fname(file_ctx->partition_name, extract_folder);
        }

        return fname;
}

static
int unzip_fw_image(const char *zipped_file, const char *unzipped_file)
{
        int ret = 0;

        log_info("Zipped file = %s, unzipped file = %s\n", zipped_file, unzipped_file);
        ret = access(zipped_file, F_OK);
        if (0 == ret) {
                ret = file_uncompress(zipped_file, unzipped_file);
                if (Z_OK != ret) {
                        log_err("File uncompress error (%s, %s)\n", zipped_file, unzipped_file);

                        return -EFAULT;
                }
        } else {
                log_err("file not found(%s)\n", zipped_file);

                return -ENOENT;
        }

        return 0;
}

static
int extract_fw_image(const struct fwimg_file *file_ctx, FILE *file, const char *extract_folder)
{
        int ret = 0;
        char *fname = NULL, *raw_fname = NULL;
        uint32_t crc = 0;

        ret = fseek(file, file_ctx->offset, SEEK_SET);
        if (0 != ret) {
                log_err("file seek error\n");

                return -EFAULT;
        }

        fname = build_image_fname(file_ctx, extract_folder);
        log_info("Extract file %s...\n", fname);
        crc = calc_fwfile_crc(file_ctx);
        ret = get_file_from_image(file, fname, file_ctx->size, &crc);
        if (file_ctx->crc32 != crc) {
                log_err("CRC error: calculated 0x%x, original: 0x%x\n", crc, file_ctx->crc32);
                ret = -EINVAL;
        }

        if (FWIMG_FILE_ZIPPED == file_ctx->attrs) {
                raw_fname = build_raw_fname(file_ctx->partition_name, extract_folder);
                ret = unzip_fw_image(fname, raw_fname);
        }

        free(fname);
        free(raw_fname);
        if (0 == ret) {
                log_info("Success\n");
        }

        return ret;
}

int fwimg_extract_files(const char *ctx_file, const char *extract_folder, struct
        fwimg_ctx *image_ctx)
{
        int ret = 0;
        int i = 0;
        uint32_t crc = 0;
        struct fwimg_ctx ctx = {0};
        FILE *file = fopen(ctx_file, "rb");

#ifndef TARGET_X86_BUILD
        (void)xcp_logger_init("fw_img_lib");
#endif
        if (NULL == file) {
                log_err("failed to open file for reading\n");

                return -EFAULT;
        }

        ret = fread_and_update_crc(&crc, (void *)&ctx.magic, sizeof(ctx.magic), file);
        if (ret < 0) {
                fclose(file);

                return ret;
        }

        log_info("magic = 0x%lx\n", ctx.magic);
        if (ctx.magic != FWIMG_CTX_MAGIC) {
                log_err("CTX magic error (0x%lx)\n", ctx.magic);
                fclose(file);

                return -EFAULT;
        }

        ret = fread_and_update_crc(&crc, (void *)&ctx.file_count, sizeof(ctx.file_count), file);
        if (ret < 0) {
                fclose(file);

                return ret;
        }

        log_info("Image consist of %d files..\n", ctx.file_count);
        ret = fread(&ctx.crc32, 1, sizeof(ctx.crc32), file);
        if (ret != sizeof(ctx.crc32)) {
                log_err("File read error\n");
                fclose(file);

                return -EFAULT;
        }

        if (crc != ctx.crc32) {
                log_err("CRC error: calculated 0x%x, original: 0x%x\n", crc, ctx.crc32);
                fclose(file);
        }

        ctx.files = calloc(ctx.file_count, sizeof(*ctx.files));
        if (NULL == ctx.files) {
                log_err("Memory allocation error\n");
                fclose(file);

                return -ENOMEM;
        }

        for (i = 0; i < ctx.file_count; i++) {
                ret = fread(&ctx.files[i], 1, sizeof(*ctx.files), file);
                if (ret != sizeof(*ctx.files)) {
                        log_err("File read error\n");
                        fclose(file);
                        free(ctx.files);

                        return -EFAULT;
                }
        }

        for (i = 0; i < ctx.file_count; i++) {
                ret = extract_fw_image(&ctx.files[i], file, extract_folder);
                if (ret < 0) {
                        fclose(file);
                        free(ctx.files);

                        return ret;
                }
        }

        fclose(file);
        if (NULL != image_ctx) {
                *image_ctx = ctx;
        } else {
                free(ctx.files);
        }
        log_info("Successfully unpacked");
        return 0;
}

