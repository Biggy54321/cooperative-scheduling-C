#include <stdio.h>
#include "../lib/task/task.h"
#include "../lib/task_queue/queue.h"
#include "../lib/scheduler/sch.h"

/* Ids for the three tasks */
uint32_t task1_id;
uint32_t task2_id;
uint32_t task3_id;

/**
 * @brief Sub task 1
 */
void subfunc1() {

    printf("Subtask 1 (before yield)\n");

    /* Yield as the subtask wants to wait for resource XX */
    yield_to_scheduler(TASK_IS_WAITING_FOR_XX);

    /* Unlock the third task */
    update_task_state(task3_id, TASK_IS_READY);

    printf("Subtask 1 (after yield)\n");
}

/**
 * @brief Task 1
 */
void func1() {
    printf("Task 1 (before subtask1)\n");

    /* Get the task id */
    task1_id = get_scheduled_task_id();

    /* Call the subtask */
    subfunc1();

    printf("Task 1 (after subtask1 before yield)\n");

    /* Yield as the task wants to wait for resource XX */
    yield_to_scheduler(TASK_IS_WAITING_FOR_XX);

    printf("Task 1 (after subtask1 after yield)\n");
}

/**
 * @brief Task 2
 */
void func2() {
    printf("Task 2 (before yield)\n");

    /* Get the task id */
    task2_id = get_scheduled_task_id();

    /* Yield as the task wants to wait for resource XX */
    yield_to_scheduler(TASK_IS_WAITING_FOR_XX);

    /* Unlock the first sub task */
    update_task_state(task1_id, TASK_IS_READY);

    printf("Task 2 (after yield)\n");
}

/**
 * @brief Task 3
 */
void func3() {
    printf("Task 3 (before yield)\n");

    /* Get the task id */
    task3_id = get_scheduled_task_id();

    /* Unlock the second task */
    update_task_state(task2_id, TASK_IS_READY);

    /* Yield as the task wants to wait for resource XX */
    yield_to_scheduler(TASK_IS_WAITING_FOR_XX);

    /* Unlock the first task */
    update_task_state(task1_id, TASK_IS_READY);

    printf("Task 3 (after yield)\n");
}

/**
 * @brief Initialize the task queue with some dummy tasks and run the scheduler
 */
void main() {

    /* Initialize the task queue */
    init_task_queue();

    /* Add the tasks with their priorities */
    add_task(func1, 1);
    add_task(func2, 2);
    add_task(func3, 3);

    /* Schedule the tasks accordingly */
    run_scheduler();
}
