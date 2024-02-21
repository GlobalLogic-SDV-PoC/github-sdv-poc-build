/**
 **************************************************************************************************
 *  @file           : pfm-pmem.h
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

#ifndef __PFM_PMEM__H__
#define __PFM_PMEM__H__

#include <stdint.h>

int pfm_pmem_init(void);
void pfm_pmem_deinit(void);

void *pfm_pmem_malloc_ext(uint32_t size, uint32_t id, uint32_t flags, uint32_t alignment);
int pfm_pmem_free(void *vaddr);

#endif /* __PFM_PMEM__H__ */

