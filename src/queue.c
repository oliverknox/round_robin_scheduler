#include "queue.h"
#include <stdlib.h>
#include <string.h>

queue *queue_create(size_t size) {
    queue *q = (queue *)malloc(sizeof(queue));

    q->head = q->tail = NULL;
    q->length = 0;
    q->node_size = size;

    return q;
}

queue_node *queue_node_create(void *data, size_t size) {
    queue_node *node = (queue_node *)malloc(sizeof(queue_node));

    node->data = malloc(size);
    memcpy(node->data, data, size);

    node->next = NULL;

    return node;
}

void enqueue(queue *q, void *data) {
    if (q == NULL) {
        return;
    }

    queue_node *node = queue_node_create(data, q->node_size);

    if (q->length == 0) {
        q->head = q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }

    q->length++;
}

void dequeue(queue *q, void *data) {
    if (q == NULL || q->length == 0) {
        return;
    }

    if (q->length == 1) {
        if (data != NULL) {
            memcpy(data, q->head->data, q->node_size);
        }

        free(q->head->data);
        free(q->head);
        
        q->head = q->tail = NULL;
        q->length = 0;
        
        return;
    }

    if (data != NULL) {
        memcpy(data, q->head->data, q->node_size);
    }
    
    free(q->head->data);
    free(q->head);

    q->head = q->head->next;
    q->length--;
}

void queue_clear(queue *q) {
    if (q == NULL) {
        return;
    }

    while (q->length > 0) {
        queue_node *temp = q->head;
        q->head = q->head->next;

        free(temp->data);
        free(temp);

        q->length--;
    }

    q->head = q->tail = NULL;
}

void queue_destroy(queue **q) {
    if (q == NULL) {
        return;
    }

    queue_clear(*q);
    free(*q);

    *q = NULL;
}