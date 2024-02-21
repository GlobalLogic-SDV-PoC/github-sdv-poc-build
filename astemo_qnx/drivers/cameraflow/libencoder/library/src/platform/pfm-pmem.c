/**
 **************************************************************************************************
 *  @file           : pfm-pmem.c
 *  @brief          : Platform PMEM wrappers
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Platform PMEM wrappers
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include <stdint.h>

#include "pmem.h"

#include "enc-logger.h"
#include "pfm-types.h"

int pfm_pmem_init(void)
{
        int rc = EOK;

        rc = pmem_init();
        if (EOK != rc) {
                log_err("Failed to initialize pmem. Error: %d\n", rc);
        }

        return rc;
}

void pfm_pmem_deinit(void)
{
        int rc = EOK;

        rc = pmem_deinit();
        if (EOK != rc) {
                log_err("Failed to deinitialize pmem. Error: %d\n", rc);
        }
}

void *pfm_pmem_malloc_ext(uint32_t size, uint32_t id, uint32_t flags, uint32_t alignment)
{
        void *ptr = NULL;

        ptr = pmem_malloc_ext(size, id, flags, alignment);

        log_dbg("MEMORY PMMALLOC ptr = [0x%p], size = [%08d]\n", ptr, size);

        return ptr;
}

int pfm_pmem_free(void *vaddr)
{
        log_dbg("MEMORY PMFREE   ptr = [0x%p]  \n", vaddr);

        return pmem_free(vaddr);
}

