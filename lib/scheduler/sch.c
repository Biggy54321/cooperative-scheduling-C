#include <stdio.h>
#include <stdint.h>
#include "../task/task.h"
#include "../task_queue/queue.h"
#include "../assembly/asm.h"
#include "sch.h"

/* Pointer to the task control block for the current task */
uint32_t g_id;
/* Whether the function returned through a yield or not */
bool g_yield_return;
/* Pointer to store the stack pointer of the current stack frame */
uint8_t *g_rsp;
/* Pointer to store the base pointer of the task function when first called */
uint8_t *g_rbp;
/* Pointer to stack buffer */
uint8_t *g_stack;
/* Task context */
TaskContext g_cxt;

/**
 * @brief Runs the scheduler, which parses the queue to run the tasks in that
 *        queue
 */
void run_scheduler() {

    TaskControlBlock tcb;
    void (*p_task)(void);

    uint32_t i = 0;

    /* Run infinitely */
    while (1) {

        /* Loop on the task queue */
        while (i < get_task_queue_length()) {

            /* Get the task id at the ith position */
            g_id = get_task_id(i);

            /* Take action according to the state of the task */
            switch (get_task_state(g_id)) {

            case TASK_IS_CREATED:
                /* Initialize the base pointer for the task function */
                GET_NEXT_RBP(g_rbp);
                /* Get the task function */
                p_task = get_task_function(g_id);
                /* Call the task function */
                p_task();
                /* Check if the task returned through yield or directly */
                if (g_yield_return) {
                    /* Reset the global flag */
                    g_yield_return = false;
                }
                else {
                    /* Remove the task from the queue */
                    remove_task(g_id);
                }

                /* Reset the value of i to 0 */
                i = 0;
                break;

            case TASK_IS_READY:
                /* Load the task function again */
                load_from_scheduler();
                /* Check if the task returned through yield or directly */
                if (g_yield_return) {
                    /* Reset the global flag */
                    g_yield_return = false;
                }
                else {
                    /* Remove the task from the queue */
                    remove_task(g_id);
                }

                /* Reset the value of i to 0 */
                i = 0;
                break;

            case TASK_IS_WAITING_FOR_XX:

                /* If the task is waiting then increment to check next task */
                i++;
                break;
            }
        }

        /* Reset the index */
        i = 0;
    }
}

/**
 * @brief Saves the current task context, updates the state with #state and
 *        returns to the scheduler
 * @param[in] state Task state to be updated with
 */
__attribute__((naked)) void yield_to_scheduler(TaskState state) {

    /* Set the status flag */
    g_yield_return = true;

    /* Set the returned state */
    update_task_state(g_id, state);

    /* Get the current stack pointer */
    GET_RSP(g_rsp);

    /* Set the length of the stack from the base of the task till now */
    g_cxt.stk_len = g_rbp - g_rsp;

    /* Set the pointer to the stack buffer of the task */
    g_stack = g_cxt.stk_buff;

    /* Copy the stack from call stack to buffer */
    while (g_rsp < g_rbp) {
        *g_stack++ = *g_rsp++;
    }

    /* Update the context of the task in the actual queue */
    update_task_context(g_id, g_cxt);

    /* Set the stack pointer to the original base pointer */
    SET_RSP(g_rbp);

    /* Perform the epilogue sequence same as the task functions */
    asm ("nop");
    asm ("pop %rbp");
    asm ("retq");
}

/**
 * @brief Loads the context of the task into the call stack and jumps to the
 *        point where it had previously yielded
 */
__attribute__((naked)) void load_from_scheduler() {

    /* Perfrom the prologue sequence same as the task function */
    asm ("push %rbp");
    asm ("mov %rsp, %rbp");

    /* Get the base pointer value  */
    GET_RBP(g_rbp);

    /* Get the context of the task to be loaded */
    g_cxt = get_task_context(g_id);

    /* Update the value of global stack pointer according to the length of the
     * stack buffer */
    g_rsp = g_rbp - g_cxt.stk_len;

    /* Set the pointer to the stack buffer of the task */
    g_stack = g_cxt.stk_buff;

    /* Copy the stack */
    while (g_rsp < g_rbp) {
        *g_rsp++ = *g_stack++;
    }

    /* Get the original position of the stack pointer */
    g_rsp = g_rbp - g_cxt.stk_len;

    /* Set the stack pointer to where it was previously in the task */
    SET_RSP(g_rsp);

    /* Perform the epilogue sequence similar to that of the yield function */
    asm ("ret");
}

/**
 * @brief Returns the task if of the task which is currently running
 * @return task id
 */
uint32_t get_scheduled_task_id() {

    return g_id;
}
