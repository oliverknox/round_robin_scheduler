#include <stdio.h>
#include <stdlib.h>

#include "task.h"

int main() {
    circular_queue *queue = circular_queue_create(sizeof(task));

    task *tasks[] = { 
        task_create(0, rand() % 100),
        task_create(1, rand() % 100),
        // task_create(2, rand() % 100) 
    };
    size_t tasks_len = sizeof(tasks) / sizeof(task);

    for (size_t i = 0; i <= tasks_len; i++) {
        circular_queue_enqueue(queue, tasks[i]);
    }

    task_state_machine *tsm = task_state_machine_create(queue);

    while (tsm->queue->length > 0) {
        task_state_machine_process(tsm);
    }

    return 0;
}