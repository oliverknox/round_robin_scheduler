#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

typedef struct queue_node queue_node;

typedef struct queue_node {
    void *data;
    queue_node *next;
};

typedef struct {
    queue_node *head;
    queue_node *tail;
    size_t length;
    size_t node_size;
} queue;

queue *queue_create(size_t size);
queue_node *queue_node_create(void *data, size_t size);
void enqueue(queue *q, void *data);
void dequeue(queue *q, void *data);
void queue_clear(queue *q);
void queue_destroy(queue **q);

#endif // QUEUE_H