#include <types.h>

#ifndef __QUEUE__
#define __QUEUE__

struct prioQueue {
    uint capacity;
    uint size;
    int *elements;
};

extern struct prioQueue *allocPrioQueue(uint num);
extern void freePrioQueue(struct prioQueue *pq);
extern void zeroPrioQueue(struct prioQueue *pq);
extern int inserPrioQueue(struct prioQueue *pq, int element);
extern bool emptyPrioQueue(struct prioQueue *pq);
extern bool fullPrioQueue(struct prioQueue *pq);

#endif
