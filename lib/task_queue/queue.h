#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include "../task/task.h"

/* Maximum number of tasks */
#define MAX_NUMBER_OF_TASKS (32)
/* Lowest value for the priority */
#define LOWEST_PRIORITY     (128)
/* Highest value for the priority */
#define HIGHEST_PRIORITY    (0)
/* Maximum value of task id */
#define MAX_TASK_ID         (1024)
/* Minimum value of task id */
#define MIN_TASK_ID         (0)

/* Functions */
void init_task_queue();

void add_task(void (*p_task)(void), uint32_t priority);

void remove_task(uint32_t id);

bool is_task_queue_empty();

bool is_task_queue_full();

uint32_t get_task_queue_length();

uint32_t get_task_id(uint32_t position);

TaskState get_task_state(uint32_t id);

void *get_task_function(uint32_t id);

TaskContext get_task_context(uint32_t id);

void update_task_state(uint32_t id, TaskState state);

void update_task_context(uint32_t id, TaskContext context);

#endif
