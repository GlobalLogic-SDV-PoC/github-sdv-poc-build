/**
 **************************************************************************************************
 *  @file           : pfm-queue.c
 *  @brief          : Platform wrappers for queue
 **************************************************************************************************
 *  @author     Vasyl Khursa
 *
 *  @description:
 *      Platform wrappers for queue
 *
 *  @section  HISTORY
 *  v1.0  - First version
 *
 *  @copyright  (c) 2023 Hitachi Astemo Ltd
 *
 **************************************************************************************************
 **/

#include "enc-logger.h"
#include "pfm-queue.h"
#include "pfm-stdlib.h"
#include "pfm-types.h"

queue_st_t *pfm_allocate_queue(void)
{
        return (queue_st_t *)pfm_calloc(1, sizeof(queue_st_t));
}

void pfm_free_queue(queue_st_t *queue)
{
        if (NULL == queue) {
                log_err("Invalid input: queue = %p\n", queue);

                return;
        }

        while (queue->count > 0) {
                pfm_queue_pop(queue);
        }

        pfm_free(queue);
}

int pfm_queue_push(queue_st_t *queue, void *item)
{
        queue_node_st_t *node = NULL;

        if (NULL == queue || NULL == item) {
                log_err("Invalid input: queue = %p, item = %p\n", queue, item);

                return EINVAL;
        }

        node = (queue_node_st_t *)pfm_calloc(1, sizeof(queue_node_st_t));
        if (NULL == node) {
                log_err("Failed to allocate queue node\n");

                return ENOMEM;
        }

        node->item = item;
        node->next = NULL;

        if (0 == queue->count) {
                queue->head = node;
        } else {
                queue->tail->next = node;
        }

        queue->tail = node;
        queue->count++;

        return EOK;
}

void *pfm_queue_pop(queue_st_t *queue)
{
        queue_node_st_t *next_node = NULL;
        void *next_item = NULL;

        if (NULL == queue) {
                log_err("Invalid input: queue = %p\n", queue);

                return NULL;
        }

        if (0 == queue->count) {
                log_dbg("Queue is empty\n");

                return NULL;
        }

        next_node = queue->head;
        next_item = next_node->item;

        if (1 == queue->count) {
                queue->head = queue->tail = NULL;
        } else {
                queue->head = queue->head->next;
        }

        pfm_free(next_node);

        queue->count--;

        return next_item;
}

