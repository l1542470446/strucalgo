#include <types.h>

#ifndef __QUEUE__
#define __QUEUE__

#define INT32_MIN (-2147483648)
#define INT32_MAX  (2147483647)
#define UINT32_MIN (0)

/*******************************************
*           1
*       2       3
*     4   5   6   7
*   8   9   .......
* result: P->i ; Pleft->2*i ; Pright->2*i+1
********************************************/
#define LCHILD(i) (2*(i))

struct prioQueue {
#define PQUEUE_MIN 0
#define PQUEUE_MAX 1
    uint type;
    uint capacity;
    uint size;
    int *elements;
};

extern struct prioQueue *allocPrioQueue(uint num, uint type);
extern void freePrioQueue(struct prioQueue *pq);
extern void zeroPrioQueue(struct prioQueue *pq);
extern int inserPrioQueue(struct prioQueue *pq, int element);
extern bool emptyPrioQueue(struct prioQueue *pq);
extern bool fullPrioQueue(struct prioQueue *pq);
extern int deletePrioQueue(struct prioQueue *pq, uint index);
extern int percolateDown(struct prioQueue *pq, uint index);

extern void buildHeap(int *data, uint n, uint type);

#endif
