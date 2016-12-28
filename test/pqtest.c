#include <stdio.h>
#include <math.h>

#include <saprint.h>
#include <queue.h>

extern void printBTreeTest();
extern void binHeapTest();
extern void buildHeapTest();

/* main function */
void main()
{
    //test 1
    //printBTreeTest();
    //test 2
    //binHeapTest();
    //test 3
    buildHeapTest();
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
    struct prioQueue *pq = NULL;
    pq = allocPrioQueue(18, PQUEUE_MAX);

    uint i;
    for (i = 0; i < 20; i++) {
        printf("---------------insert %dst element : %d---------------------\n", i+1, aa[i]);
        inserPrioQueue(pq, aa[i]);
        prArrBinTree(pq->elements + 1, 18);
    }
    printf("---------------delete 1st element : %d---------------------\n", pq->elements[1]);
    deletePrioQueue(pq, 1);
    prArrBinTree(pq->elements + 1, 17);
    freePrioQueue(pq);
}

void buildHeapTest()
{
    int aa[20] = {11,-2,3,40,5,60,7,8,-90,0, \
                  23,56,2,5,-52,65,58,12,45,69 };
    //buildHeap(aa, 20, PQUEUE_MAX);
    buildHeap(aa, 20, PQUEUE_MIN);
    prArrBinTree(aa, 20);
}
