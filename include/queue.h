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

struct binHeap {
#define PQUEUE_MIN 0
#define PQUEUE_MAX 1
    uint type;
    uint capacity;
    uint size;
    int *elements;
};

extern struct binHeap *allocBinHeap(uint num, uint type);
extern void freeBinHeap(struct binHeap *pq);
extern void zeroBinHeap(struct binHeap *pq);
extern int inserBinHeap(struct binHeap *pq, int element);
extern bool emptyBinHeap(struct binHeap *pq);
extern bool fullBinHeap(struct binHeap *pq);
extern int deleteBinHeap(struct binHeap *pq, uint index);
extern int percolateDown(struct binHeap *pq, uint index);

extern void buildHeap(int *data, uint n, uint type);

#endif
