/**
 **************************************************************************************************
 *  @file           : pfm-critical.h
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

#ifndef __PFM_CRITICAL__H__
#define __PFM_CRITICAL__H__

#include "MMThread.h"

int pfm_lock_create(MM_HANDLE *lock);
void pfm_lock_release(MM_HANDLE lock);

void pfm_lock(MM_HANDLE lock);
void pfm_unlock(MM_HANDLE lock);

#endif /* __PFM_CRITICAL__H__ */

