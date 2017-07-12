#include <string.h>
#include <malloc.h>

#include <saprint.h>
#include <stack.h>

static int isEmpty(struct stack *sta)
{
    if (sta->next == NULL)
        return 1;
    else
        return 0;
}

struct stack *createStack()
{
    struct stack *stackTemp = NULL;
    stackTemp = malloc(sizeof(struct stack));
    if (stackTemp == NULL) {
        ERROR("stack structure malloc fail\n");
        return NULL;
    }
    stackTemp->element = NULL;
    stackTemp->next = NULL;
    return stackTemp;
}

int pushStack(struct stack *sta, void *element)
{
    int ret = 0;
    struct stack *topStack = NULL;
    topStack = malloc(sizeof(struct stack));
    if (topStack == NULL) {
        ERROR("stack structure top element malloc fail\n");
        ret = -1;
    } else {
        topStack->element = element;
        topStack->next = sta->next;
        sta->next = topStack;
    }
    return ret;
}

/**
 * pop element exist in memory
 */
struct stack *popStack(struct stack *sta)
{
    struct stack *popStack;
    if (isEmpty(sta)) {
        popStack = NULL;
    } else {
        popStack = sta->next;
        sta->next = sta->next->next;
    }
    return popStack;
}
