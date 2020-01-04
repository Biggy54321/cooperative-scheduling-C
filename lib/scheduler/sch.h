#ifndef _SCH_H_
#define _SCH_H_

#include "../task/task.h"

/* Functions */
void run_scheduler();

void yield_to_scheduler(TaskState state);

void load_from_scheduler();

uint32_t get_scheduled_task_id();

#endif
