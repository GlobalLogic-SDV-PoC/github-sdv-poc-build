/**
 **************************************************************************************************
 *  @file           : pfm-queue.h
 *  @brief          : Platform wrappers for queue header
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Platform wrappers for queue header
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#ifndef __PFM_QUEUE__H__
#define __PFM_QUEUE__H__

typedef struct queue_node_st {
        void                 *item;
        struct queue_node_st *next;
} queue_node_st_t;

typedef struct queue_st {
        struct queue_node_st *head;
        struct queue_node_st *tail;
        unsigned int         count;
} queue_st_t;

queue_st_t *pfm_allocate_queue(void);
void pfm_free_queue(queue_st_t *queue);

int pfm_queue_push(queue_st_t *queue, void *item);
void *pfm_queue_pop(queue_st_t *queue);

#endif /* __PFM_QUEUE__H__ */

