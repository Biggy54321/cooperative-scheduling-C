#ifndef _TASK_H_
#define _TASK_H_

#include <stdint.h>

/**
 * @brief Flags to denote the state of the task
 */
typedef enum _TaskState {
    TASK_IS_CREATED,                /* For tasks which have just entered */
    TASK_IS_READY,                  /* For tasks waiting for CPU time */
    TASK_IS_RUNNING,                /* For tasks which are executing */
    TASK_IS_WAITING_FOR_XX,         /* For tasks waiting for certain subtask */
    TASK_IS_TERMINTATED             /* For tasks which have finished */
} TaskState;

/* Stack size for the internal contexts */
#define STACK_BUFFER_SIZE (256)

/**
 * @brief Structure to represent a task context
 */
typedef struct _TaskContext {
    uint8_t stk_buff[STACK_BUFFER_SIZE]; /* Stack buffer */
    uint32_t stk_len;                    /* Stack length in bytes */
} TaskContext;

/**
 * @brief Structure to represent a task
 */
typedef struct _TaskControlBlock {
    uint32_t id;                /* Task id */
    TaskState state;            /* Task state */
    void (*p_task)(void);       /* Task function */
    uint32_t priority;          /* Task priority */
    TaskContext context;        /* Task context */
} TaskControlBlock;

#endif
