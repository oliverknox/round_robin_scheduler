#include <stdlib.h>
#include <string.h>

#include "circular_queue.h"

circular_queue *circular_queue_create(size_t size) {
    circular_queue *queue = (circular_queue *)malloc(sizeof(circular_queue));

    queue->head = queue->tail = NULL;
    queue->length = 0;
    queue->node_size = size;

    return queue;
}

circular_queue_node *circular_queue_node_create(void *data, size_t size) {
    circular_queue_node *node = (circular_queue_node *)malloc(sizeof(circular_queue_node));

    node->data = malloc(size);
    memcpy(node->data, data, size);

    node->next = NULL;

    return node;
}

void circular_queue_enqueue(circular_queue *queue, void *data) {
    if (queue == NULL) {
        return;
    }

    circular_queue_node *node = circular_queue_node_create(data, queue->node_size);

    if (queue->length == 0) {
        queue->head = queue->tail = node;
        queue->tail->next = queue->head;
    } else {
        node->next = queue->head;
        queue->tail->next = node;
        queue->tail = node;
    }

    queue->length++;
}

void circular_queue_dequeue(circular_queue *queue, void *data) {
    if (queue == NULL || queue->length == 0) {
        return;
    }

    if (queue->length == 1) {
        if (data != NULL) {
            memcpy(data, queue->head->data, queue->node_size);
        }

        free(queue->head->data);
        free(queue->head);
        
        queue->head = queue->tail = NULL;
        queue->length = 0;
        
        return;
    }

    if (data != NULL) {
        memcpy(data, queue->head->data, queue->node_size);
    }

    free(queue->head->data);
    free(queue->head);

    queue->head = queue->head->next;
    queue->tail->next = queue->head;
    queue->length--;
}

void circular_queue_clear(circular_queue *queue) {
    if (queue == NULL) {
        return;
    }

    while (queue->length > 0) {
        circular_queue_node *temp = queue->head;
        queue->head = queue->head->next;

        free(temp->data);
        free(temp);

        queue->length--;
    }

    queue->head = queue->tail = NULL;
}

void circular_queue_destroy(circular_queue **queue) {
    if (queue == NULL) {
        return;
    }

    circular_queue_clear(*queue);
    free(*queue);

    *queue = NULL;
}