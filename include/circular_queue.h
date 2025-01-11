#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stddef.h>

typedef struct circular_queue_node circular_queue_node;

struct circular_queue_node {
    void *data;
    circular_queue_node *next;
};

typedef struct {
    circular_queue_node *head;
    circular_queue_node *tail;
    size_t length;
    size_t node_size;
} circular_queue;

circular_queue *circular_queue_create(size_t size);
circular_queue_node *circular_queue_node_create(void *data, size_t size);
void circular_queue_enqueue(circular_queue *queue, void *data);
void circular_queue_dequeue(circular_queue *queue, void *data);
void circular_queue_clear(circular_queue *queue);
void circular_queue_destroy(circular_queue **queue);

#endif // CIRCULAR_QUEUE_H