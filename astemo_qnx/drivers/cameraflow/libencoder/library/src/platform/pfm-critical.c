/**
 **************************************************************************************************
 *  @file           : pfm-critical.c
 *  @brief          : Platform critical section API wrappers
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Platform critical section API wrappers
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "MMCriticalSection.h"

#include "enc-logger.h"
#include "pfm-types.h"

int pfm_lock_create(MM_HANDLE *lock)
{
        if (NULL == lock) {
                log_err("Invalid input: lock = %p\n", lock);

                return EINVAL;
        }

        return MM_CriticalSection_Create(lock);
}

void pfm_lock_release(MM_HANDLE lock)
{
        MM_CriticalSection_Release(lock);
}

void pfm_lock(MM_HANDLE lock)
{
        int rc = EOK;

        rc = MM_CriticalSection_Enter(lock);
        if (EOK != rc) {
                log_err("Failed to lock. Error: %d\n", rc);
        }
}

void pfm_unlock(MM_HANDLE lock)
{
        int rc = EOK;

        rc = MM_CriticalSection_Leave(lock);
        if (EOK != rc) {
                log_err("Failed to unlock. Error: %d\n", rc);
        }
}

