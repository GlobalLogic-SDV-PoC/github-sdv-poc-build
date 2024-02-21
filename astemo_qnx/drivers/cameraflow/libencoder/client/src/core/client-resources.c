/**
 **************************************************************************************************
 *  @file           : client-resources.c
 *  @brief          : Client resources API
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Allocation client resources: PMEM buffers, files.
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "client-ctx.h"
#include "enc-logger.h"
#include "pfm-pmem.h"
#include "pfm-stdlib.h"

static
int pfm_open_files(client_ctx_st_t *ctx)
{
        int rc = EOK;

        log_dbg("Try to open files\n");

        rc = pfm_create_file(&ctx->files[INPUT_FILE]);
        if (EOK != rc) {
                log_err("Failed to create file '%s'. Error: %d", ctx->files[INPUT_FILE].name, rc);

                return rc;
        }

        rc = pfm_create_file(&ctx->files[OUTPUT_FILE]);
        if (EOK != rc) {
                log_err("Failed to create file '%s'. Error: %d", ctx->files[OUTPUT_FILE].name, rc);

                return rc;
        }

        log_dbg("Successfully opened files\n");

        return rc;
}

static
void pfm_release_files(client_ctx_st_t *ctx)
{
        int rc = EOK;

        log_dbg("Try to release files\n");

        rc = pfm_release_file(&ctx->files[INPUT_FILE]);
        if (EOK != rc) {
                log_err("Failed to release file '%s'. Error: %d", ctx->files[INPUT_FILE].name, rc);
        }

        rc = pfm_release_file(&ctx->files[OUTPUT_FILE]);
        if (EOK != rc) {
                log_err("Failed to release file '%s'. Error: %d", ctx->files[OUTPUT_FILE].name, rc);
        }

        log_dbg("Successfully released files\n");
}

int pfm_resourses_init(client_ctx_st_t *ctx)
{
        int rc = EOK;

        log_dbg("Try to initialize client resources\n");

        rc = pfm_open_files(ctx);
        if (EOK != rc) {
                log_err("Failed to open files. Error: %d\n", rc);

                return rc;
        }

        rc = pfm_pmem_init();
        if (EOK != rc) {
                log_err("Failed to initialize PMEM. Error: %d\n", rc);

                return rc;
        }

        log_dbg("Successfully initialized client resources\n");

        return rc;
}

void pfm_resourses_deinit(client_ctx_st_t *ctx)
{
        log_dbg("Try to de initialize client resources\n");

        pfm_release_files(ctx);

        pfm_pmem_deinit();

        log_dbg("Successfully de initialized client resources\n");
}

static
int pmem_allocate_buffers(pmem_buffers_ctx_st_t *buffers_ctx)
{
        int i = 0;
        const size_t ptr_size = sizeof(void *);

        log_dbg("Try to allocate [%d] buffers, size [%d] bytes\n", buffers_ctx->count,
                buffers_ctx->size);

        buffers_ctx->buffers = pfm_calloc(1, ptr_size * buffers_ctx->count);
        if (NULL == buffers_ctx->buffers) {
                log_err("Failed to allocate buffer pointers array\n");

                return ENOMEM;
        }

        buffers_ctx->data_len = (size_t **)pfm_calloc(1, sizeof(size_t) * buffers_ctx->count);
        if (NULL == buffers_ctx->data_len) {
                log_err("Failed to allocate buffers payload parameters\n");

                return ENOMEM;
        }

        for (i = 0; i < buffers_ctx->count; i++) {
                buffers_ctx->buffers[i] = pfm_pmem_malloc_ext(buffers_ctx->size,
                                                              PMEM_VIDEO_ID,
                                                              PMEM_FLAGS_PHYS_NON_CONTIG,
                                                              PMEM_ALIGNMENT_4K);

                if (NULL == buffers_ctx->buffers[i]) {
                        log_err("Failed to allocate buffer [%d]\n", i);

                        return ENOMEM;
                }

                log_dbg("Successfully allocated buffer [%d]\n", i);
        }

        log_dbg("Successfully allocated buffers\n");

        return EOK;
}

static
void pmem_free_buffers(pmem_buffers_ctx_st_t *buffers_ctx)
{
        int i = 0;

        log_dbg("Try to free [%d] PMEM buffers\n", buffers_ctx->count);

        for (i = 0; i < buffers_ctx->count; i++) {
                pfm_pmem_free(buffers_ctx->buffers[i]);

                log_dbg("Successfully freed PMEM buffer [%d]\n", i);
        }

        pfm_free(buffers_ctx->data_len);
        pfm_free(buffers_ctx->buffers);

        log_dbg("Successfully freed PMEM buffers\n");
}

int pfm_allocate_pmem_buffers(client_ctx_st_t *ctx)
{
        int rc = EOK;

        rc = pmem_allocate_buffers(&ctx->pmem_buffers_ctxs[IO_INPUT_CTX]);
        if (EOK != rc) {
                log_err("Failed to allocate input buffers. Error: %d\n", rc);

                return rc;
        }

        rc = pmem_allocate_buffers(&ctx->pmem_buffers_ctxs[IO_OUTPUT_CTX]);
        if (EOK != rc) {
                log_err("Failed to allocate output buffers. Error: %d\n", rc);
        }

        return rc;
}

void pfm_free_pmem_buffers(client_ctx_st_t *ctx)
{
        pmem_free_buffers(&ctx->pmem_buffers_ctxs[IO_INPUT_CTX]);
        pmem_free_buffers(&ctx->pmem_buffers_ctxs[IO_OUTPUT_CTX]);
}

