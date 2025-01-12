#ifndef TASK_H
#define TASK_H

#include "circular_queue.h"

typedef enum {
    READY,
    RUNNING,
    TERMINATED
} task_state;

typedef struct {
    int task_id;
    int work_remaining;
    task_state state;
    task_state next_state;
} task;

typedef struct {
    circular_queue *queue;
    task *current_task;
    void (*on_update)(circular_queue *queue);
    void (*on_complete)(task *t);

} task_state_machine;


task *task_create(int task_id, int work_remaining);
task_state_machine *task_state_machine_create(circular_queue *queue, void (*on_update)(circular_queue *queue), void (*on_complete)(task *t));
void task_state_machine_process(task_state_machine *tsm);

#endif // TASK_H