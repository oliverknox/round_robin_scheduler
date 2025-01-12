#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fort.h>

#include "task.h"

// TODO: Tidy up into progress_reporter
const char* sprintf_progress(int percentage, int block_size) {
    int total_blocks = 100 / block_size;

    // string format: "[total_blocks] 100 units left" = total_blocks + 17 chars + 1 null terminator
    char *progress_str = (char*)malloc(total_blocks + 18);

    progress_str[0] = '[';

    for (int i = 0; i < total_blocks; i++) {
        if (i * block_size < percentage) {
            progress_str[i + 1] = '#';
        } else {
            progress_str[i + 1] = '-';
        }
    }

    progress_str[total_blocks + 1] = ']';
    progress_str[total_blocks + 2] = ' ';
    snprintf(progress_str + total_blocks + 3, 15, "%3d units left", percentage);

    return progress_str;
}   

int task_by_task_id_predicate(const void *a, const void *b) {
    task* at = (task*)a;
    task* bt = (task*)b;

    return at->task_id - bt->task_id;
}

void on_state_machine_update(circular_queue *queue) {
    if (queue == NULL || queue->length == 0) {
        return;
    }     

    printf("\033[H");

    ft_table_t *table = ft_create_table();

    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_MAGENTA);
    ft_set_cell_prop(table, 1, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_BLUE);
    ft_set_cell_prop(table, 2, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_CYAN);
    ft_set_cell_prop(table, 3, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_BLUE);

    ft_write_ln(table, "Task ID", "Work Remaining");

    task *tasks = (task *)malloc(queue->length * sizeof(task));

    circular_queue_node *current = queue->head;
    int i = 0;
    do {
        task *t = (task *)current->data;
        tasks[i] = *t;

        i++;

        current = current->next;
    } while (current != queue->head);

    qsort(tasks, queue->length, sizeof(task), task_by_task_id_predicate);

    for (i = 0; i < queue->length; i++) {
        task t = tasks[i];

        char task_id_str[12];

        sprintf(task_id_str, "%d", t.task_id);
        const char *progress_str = sprintf_progress(t.work_remaining, 5);

        ft_write_ln(table, task_id_str, progress_str);

        free((char *)progress_str);
    }

    printf("%s\n", ft_to_string(table));

    free(tasks);
    ft_destroy_table(table);
}

// TODO: Implement task_history, to improve reporting of completed tasks.
void on_state_machine_complete(task *t) {
    printf("\033[2J");
}

int main() {
    printf("\033[2J");

    circular_queue *queue = circular_queue_create(sizeof(task));

    task *tasks[] = { 
        task_create(0, rand() % 100),
        task_create(1, rand() % 100),
        task_create(2, rand() % 100) 
    };
    size_t tasks_len = sizeof(tasks) / sizeof(tasks[0]);

    for (size_t i = 0; i < tasks_len; i++) {
        circular_queue_enqueue(queue, tasks[i]);
    }

    task_state_machine *tsm = task_state_machine_create(queue, on_state_machine_update, on_state_machine_complete);

    while (tsm->queue->length > 0) {
        task_state_machine_process(tsm);
        usleep(300000);
    }

    return 0;
}