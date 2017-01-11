#include <types.h>
#include <tree.h>

#ifndef __QUEUE__
#define __QUEUE__
/********************************************/
/*                  bin-heap                */
/********************************************/
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

/********************************************/
/*                  left-heap               */
/********************************************/

struct leftHeap {
    struct treeNode tn;
    int npl;
};

#define toLeftHeap(tree) container_of(tree, struct leftHeap, tn)

extern struct leftHeap *allocLeftHeap();
extern void freeLeftHeap(struct leftHeap *lh);
extern void freeLeftHeaps(struct leftHeap *lh);
extern struct leftHeap *delMinLeftHeap(struct leftHeap *lh);
extern struct leftHeap *mergeLeftHeap(struct leftHeap *lh1, struct leftHeap *lh2);
extern struct leftHeap *inserLeftHeap(int data, struct leftHeap *lh);
extern void prLeftHeap(struct leftHeap *lh);
extern uint findAbLeftHeap(struct leftHeap *lh);

/********************************************/
/*                  skew-heap               */
/********************************************/

struct skewHeap {
    struct treeNode tn;
};

#define toSkewHeap(tree) container_of(tree, struct skewHeap, tn)

extern struct skewHeap *allocSkewHeap();
extern void freeSkewHeap(struct skewHeap *sh);
extern void freeSkewHeaps(struct skewHeap *sh);
extern struct skewHeap *mergeSkewHeap(struct skewHeap *sh1, struct skewHeap *sh2);
extern struct skewHeap *insertSkewHeap(int data, struct skewHeap *sh);
extern void prSkewHeap(struct skewHeap *sh);
extern struct skewHeap *delMinSkewHeap(struct skewHeap *sh);

#endif
