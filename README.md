# NON-PREEMPTIVE PRIORITY BASED SCHEDULER

## Features

* Provides a library of functions required to implement a non-preemptive/cooperative scheduler in C.

* The tasks to be scheduled must have specific priorities.

* The tasks should be added to the queue in order to schedule them.

* The tasks will start execution if it is the only highest priority ready task in the queue.

* Once the task is scheduled it runs till completion or till it yields the control to the scheduler. A task may yield if it wants to wait for some event.

* Once the control is in the scheduler, it finds the highest priority task in the queue. Depending on the state of the task it takes respective actions.

* The context switches in this case are implemented using swapping of stacks. This means that the task which yields will store its current stack and the task to be loaded will have its stack loaded by the scheduler.

## Limitations

* The size of the stack buffer that each task maintains is required to be more. But the current implementation uses only 256 bytes of stack buffer

* The first function belonging to every task must have a common signature (i.e. void function(void)) for ease in getting the value of call stack pointers and context switching.