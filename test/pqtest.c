#include <stdio.h>
#include <math.h>

#include <saprint.h>
#include <queue.h>
#include "data.h"

extern void printBTreeTest();
extern void binHeapTest();
extern void buildHeapTest();
extern void leftHeapTest();

/* main function */
void main()
{
    //test 1
    //printBTreeTest();
    //test 2
    //binHeapTest();
    //test 3
    //buildHeapTest();
    //test 4
    leftHeapTest();
}

/*------------------------------------------------------------------------*/
void printBTreeTest()
{
    int aa[20] = {11,-2,3,40,5,60,7,8,-90,0, \
                  23,56,2,5,-52,65,58,12,45,69 };
    prArrBinTree(aa,20);
}

void binHeapTest()
{
    int aa[20] = {11,-2,3,40,5,60,7,8,-90,0, \
                  23,56,2,5,-52,65,58,12,45,69 };
    struct binHeap *pq = NULL;
    pq = allocBinHeap(18, PQUEUE_MAX);

    uint i;
    for (i = 0; i < 20; i++) {
        printf("---------------insert %dst element : %d---------------------\n", i+1, aa[i]);
        inserBinHeap(pq, aa[i]);
        prArrBinTree(pq->elements + 1, 18);
    }
    printf("---------------delete 1st element : %d---------------------\n", pq->elements[1]);
    deleteBinHeap(pq, 1);
    prArrBinTree(pq->elements + 1, 17);
    freeBinHeap(pq);
}

void buildHeapTest()
{
    int aa[20] = {11,-2,3,40,5,60,7,8,-90,0, \
                  23,56,2,5,-52,65,58,12,45,69 };
    //buildHeap(aa, 20, PQUEUE_MAX);
    buildHeap(aa, 20, PQUEUE_MIN);
    prArrBinTree(aa, 20);
}

void leftHeapTest()
{
    printf("---------------build left heap test---------------------\n");
    int i;
    struct leftHeap *cur = NULL, *next = NULL;
    for (i = 0; i < 10; i++) {
        next = inserLeftHeap(arData10[i], cur);
        cur = next;
    }
    prLeftHeap(cur);
    printf("---------------delete min heap test---------------------\n");
    next = delMinLeftHeap(cur);
    prLeftHeap(next);
}
