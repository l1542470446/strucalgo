#include <types.h>

#ifndef __STACK_H__
#define __STACK_H__

/**     |       |-------|       top
 *      |       |       |
 *      |   .   |      next
 *      |   .   |<------|
 *      |   .   |
 *      ---------           bottom
 */

struct stack {
    void *element;
    struct stack *next;
};

extern struct stack *createStack();
extern int pushStack(struct stack *sta, void *element);
extern struct stack *popStack(struct stack *sta);

#endif
