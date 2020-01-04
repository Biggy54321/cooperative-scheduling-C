#include <stdio.h>
#include "queue.h"

/* Task Queue (Priority queue, add task and sort, remove no need to sort) */
static TaskControlBlock gs_task_queue[MAX_NUMBER_OF_TASKS];
/* Task queue length */
static uint32_t gs_task_queue_len;
/* Id for the task (must be unique for all the active tasks) */
static uint32_t gs_next_task_id;

/**
 * @brief Initializes the task queue
 */
void init_task_queue() {

    /* Reset the queue index */
    gs_task_queue_len = 0;

    /* Reset the task id */
    gs_next_task_id = 0;
}

/**
 * @brief Adds the specified task to the queue with a specific id
 * @param[in] p_task Pointer to the function for that task
 * @param[in] priority Priority for the task
 */
void add_task(void (*p_task)(void), uint32_t priority) {

    uint32_t i;
    uint32_t j;

    /* Find the first task having priority greater than the current task */
    for (i = 0; i < gs_task_queue_len; i++) {
        if (priority < gs_task_queue[i].priority) {
            break;
        }
    }

    /* Rearrange the queue */
    for (j = gs_task_queue_len; j > i; j--) {

        /* Shift the elements to the right */
        gs_task_queue[j] = gs_task_queue[j - 1];
    }

    /* Insert the current task */
    gs_task_queue[i] = (TaskControlBlock){.id = gs_next_task_id,
                                          .state = TASK_IS_CREATED,
                                          .p_task = p_task,
                                          .priority = priority};

    /* Update the length of the queue */
    gs_task_queue_len++;

    /* Update the id given */
    gs_next_task_id = (gs_next_task_id + 1) % MAX_TASK_ID;
}

/**
 * @brief Removes the task from the queue with the given id (index)
 * @param[in] id ID of the task to be removed
 */
void remove_task(uint32_t id) {

    uint32_t i;

    /* Search for the element */
    for (i = 0; i < gs_task_queue_len; i++) {
        if (id == gs_task_queue[i].id) {
            break;
        }
    }

    /* For all the elements after the given id */
    for (; i < gs_task_queue_len - 1; i++) {

        /* Shift the tasks one block behind */
        gs_task_queue[i] = gs_task_queue[i + 1];
    }

    /* Update the length of the queue */
    gs_task_queue_len--;
}

/**
 * @brief Checks is task queue is empty
 * @return true if empty
 * @return false if not empty
 */
bool is_task_queue_empty() {

    /* Return true if the length of the queue is equal to zero */
    return gs_task_queue_len == 0;
}

/**
 * @brief Checks is task queue is full
 * @return true if full
 * @return false if not full
 */
bool is_task_queue_full() {

    /* Return true if length of queue is equal to the max value */
    return gs_task_queue_len == MAX_NUMBER_OF_TASKS;
}

/**
 * @brief Returns the number of tasks currently in the task queue
 * @return Length of the queue
 */
uint32_t get_task_queue_length() {

    return gs_task_queue_len;
}

/**
 * @brief Returns the task id at the specified position in the queue
 * @param[in] position Index of the task in the queue
 * @return Task id having position #position
 */
uint32_t get_task_id(uint32_t position) {

    return gs_task_queue[position].id;
}

/**
 * @brief Returns the state of the task
 * @param[in] id ID of the task to be updated
 * @return Task state having given id
 */
TaskState get_task_state(uint32_t id) {

    uint32_t i;

    for (i = 0; i < gs_task_queue_len; i++) {
        if (gs_task_queue[i].id == id) {
            return gs_task_queue[i].state;
        }
    }
}

/**
 * @brief Returns the pointer to the function of the task
 * @param[in] id ID of the task to be updated
 * @return Pointer to the function for the given task id
 */
void *get_task_function(uint32_t id) {

    uint32_t i;

    for (i = 0; i < gs_task_queue_len; i++) {
        if (gs_task_queue[i].id == id) {
            return gs_task_queue[i].p_task;
        }
    }
}

/**
 * @brief Returns the context of the task
 * @param[in] id ID of the task to be updated
 * @return Context of the task with given id
 */
TaskContext get_task_context(uint32_t id) {

    uint32_t i;

    for (i = 0; i < gs_task_queue_len; i++) {
        if (gs_task_queue[i].id == id) {
            return gs_task_queue[i].context;
        }
    }
}

/**
 * @brief Updates the state of the task
 * @param[in] id ID of the task to be updated
 * @param[in] state State to be set
 */
void update_task_state(uint32_t id, TaskState state) {

    uint32_t i;

    for (i = 0; i < gs_task_queue_len; i++) {
        if (gs_task_queue[i].id == id) {
            gs_task_queue[i].state = state;
        }
    }
}

/**
 * @brief Updates the context of the task
 * @param[in] id ID of the task to be updated
 * @param[in] context Context to be set
 */
void update_task_context(uint32_t id, TaskContext context) {

    uint32_t i;

    for (i = 0; i < gs_task_queue_len; i++) {
        if (gs_task_queue[i].id == id) {
            gs_task_queue[i].context = context;
        }
    }
}
