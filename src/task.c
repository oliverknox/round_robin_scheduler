#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "circular_queue.h"
#include "task.h"

task *task_create(int task_id, int total_work) {
    task *t = (task *)malloc(sizeof(task));

    t->task_id = task_id;
    t->total_work = t->work_remaining = total_work;
    t->state = READY;
    t->next_state = READY;
    
    return t;
}

void task_process(task *t, int quantum) {
    if (t == NULL) {
        return;
    }

    t->work_remaining -= quantum;
}

// TODO: task_state_machine should be moved into scheduler.c 

task_state_machine *task_state_machine_create(circular_queue *queue, void (*on_update)(circular_queue *queue), void (*on_complete)(task *t)) {
    task_state_machine *tsm = (task_state_machine *)malloc(sizeof(task_state_machine));

    tsm->queue = queue;
    tsm->current_task = (task *)malloc(sizeof(task));
    tsm->current_task->next_state = READY;
    tsm->on_update = on_update;
    tsm->on_complete = on_complete;

    return tsm;
}

void task_state_machine_process_ready(task_state_machine *tsm) {
    circular_queue_dequeue(tsm->queue, tsm->current_task);
    tsm->current_task->next_state = RUNNING;
    tsm->current_task->state = READY;
}

void task_state_machine_process_running(task_state_machine *tsm) {
    task_process(tsm->current_task, 1);

    if (tsm->current_task->work_remaining <= 0) {
        tsm->current_task->next_state = TERMINATED;
        tsm->current_task->state = RUNNING;
    } else {
        circular_queue_enqueue(tsm->queue, tsm->current_task);
        tsm->current_task->next_state = READY;
        tsm->current_task->state = RUNNING;
    }
}

void task_state_machine_process_terminated(task_state_machine *tsm) {
    tsm->current_task->next_state = READY;
    tsm->current_task->state = TERMINATED;
    tsm->on_complete(tsm->current_task);
}

void task_state_machine_tick(task_state_machine *tsm) {
    switch (tsm->current_task->next_state) {
        case READY:
            task_state_machine_process_ready(tsm);
            break;
        case RUNNING:
            task_state_machine_process_running(tsm);
            break;
        case TERMINATED:
            task_state_machine_process_terminated(tsm);
            break;
    }
}

void task_state_machine_process(task_state_machine *tsm) {
    bool has_terminated = false;
    bool has_requeued = false;

    while (!has_terminated && !has_requeued) {
        task_state_machine_tick(tsm);

        has_terminated = tsm->current_task->state == TERMINATED;
        has_requeued = tsm->current_task->state == RUNNING && tsm->current_task->next_state == READY;
    }

    if (tsm->on_update) {
        tsm->on_update(tsm->queue);
    }
}