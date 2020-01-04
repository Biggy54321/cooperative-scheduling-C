#ifndef _ASM_H_
#define _ASM_H_

/* Get the value of the stack pointer into the variable */
#define GET_RSP(var) {asm ("mov %%rsp, %0": "=r" (var));}
/* Set the value of the stack pointer with that of the variable */
#define SET_RSP(var) {asm ("mov %0, %%rsp":: "r" (var));}
/* Get the value of the base pointer into the variable */
#define GET_RBP(var) {asm ("mov %%rbp, %0": "=r" (var));}
/* Get the value of the base pointer for the next function
 * The signature of the next function must be "void function(void)"
 * Hence from the current stack we subtract two address elements to get the
 * value of base pointer that the next called function of the above signature
 * will have
 */
#define GET_NEXT_RBP(var)                               \
    {                                                   \
        GET_RSP(var);                                   \
        var = (uint8_t *)var - sizeof(uint8_t *) * 2;   \
    }

#endif
