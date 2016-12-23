#include <malloc.h>

#include <types.h>
#include <queue.h>
#include <saprint.h>

/********************************************************
* empty : true
* not empty : false
*********************************************************/
bool emptyPrioQueue(struct prioQueue *pq)
{
    if (pq->size == 0)
        return true;
    else
        return false;
}

/********************************************************
* full : true
* not full : false
*********************************************************/
bool fullPrioQueue(struct prioQueue *pq)
{
    if (pq->size == pq->capacity)
        return true;
    else
        return false;
}

void freePrioQueue(struct prioQueue *pq)
{
    if (pq->elements != NULL)
        free(pq->elements);
    if (pq != NULL)
        free(pq);
}

void zeroPrioQueue(struct prioQueue *pq)
{
    uint n = pq->size;
    int *data = pq->elements;
    uint i;
    for (i = 0; i < n; i++)
        data[i] = 0;
}

struct prioQueue *allocPrioQueue(uint num)
{
    struct prioQueue *pq = NULL;
    pq = malloc(sizeof(struct prioQueue));
    if (pq == NULL)
        ERROR("priority queue malloc failure!\n");
}
