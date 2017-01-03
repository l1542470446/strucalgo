#include <malloc.h>

#include <types.h>
#include <queue.h>
#include <saprint.h>

/********************************************************
* empty : true
* not empty : false
*********************************************************/
bool emptyBinHeap(struct binHeap *pq)
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
bool fullBinHeap(struct binHeap *pq)
{
    if (pq->size == pq->capacity)
        return true;
    else
        return false;
}

void freeBinHeap(struct binHeap *pq)
{
    if (pq->elements != NULL)
        free(pq->elements);
    if (pq != NULL)
        free(pq);
}

void zeroBinHeap(struct binHeap *pq)
{
    uint n = pq->size;
    int *data = pq->elements;
    uint i;
    for (i = 0; i < n; i++)
        data[i] = 0;
}

struct binHeap *allocBinHeap(uint num, uint type)
{
    struct binHeap *pq = NULL;
    pq = malloc(sizeof(struct binHeap));
    if (pq == NULL) {
        ERROR("priority queue malloc failure!\n");
        return NULL;
    }
    int *data = NULL;
    data = malloc((num+1) * sizeof(int));
    if (data == NULL) {
        ERROR("elements malloc failure!\n");
        free(pq);
        return NULL;
    }
    if (type == PQUEUE_MIN) {
        data[0] = INT32_MIN;
    } else if (type == PQUEUE_MAX) {
        data[0] = INT32_MAX;
    } else {
        ERROR("priority queue type arg is wrong!\n");
        free(data);
        free(pq);
        return NULL;
    }
    pq->type = type;
    pq->elements = data;
    pq->capacity = num;
    pq->size = 0;
    return pq;
}

int inserBinHeap(struct binHeap *pq, int element)
{
    if (fullBinHeap(pq)) {
        WARN("priority queue full !\n");
        return 1;
    }

    int i;
    if (pq->type == PQUEUE_MIN) {
        for (i = ++pq->size; pq->elements[i / 2] > element; i /= 2)
            pq->elements[i] = pq->elements[i / 2];
    } else if (pq->type == PQUEUE_MAX) {
        for (i = ++pq->size; pq->elements[i / 2] < element; i /= 2)
            pq->elements[i] = pq->elements[i / 2];
    } else {
        ERROR("priority queue type unknown!\n");
        return 1;
    }
    pq->elements[i] = element;
}

/********************************************************
* data array -> a[0] a[1] ...
*                 |    |
*          index :1    2  ...
*********************************************************/
int percolateDown(struct binHeap *pq, uint index)
{
    uint child, i, n;
    int tmp;
    int *data = NULL;
    data = pq->elements;
    n = pq->size;

    if ((index > n) || (index == 0)) {
        WARN("data index overflow\n");
        return 1;
    }

    if (pq->type == PQUEUE_MIN) {
        for (tmp = data[index], i = index; LCHILD(i) < n; i = child) {
            child = LCHILD(i);
            if ((child < n) && (data[child+1] < data[child]))
                child++;
            if (data[child] < tmp)
                data[i] = data[child];
            else
                break;
        }
        data[i] = tmp;
    } else if (pq->type == PQUEUE_MAX) {
        for (tmp = data[index], i = index; LCHILD(i) < n; i = child) {
            child = LCHILD(i);
            if ((child < n) && (data[child+1] > data[child]))
                child++;
            if (data[child] > tmp)
                data[i] = data[child];
            else
                break;
        }
        data[i] = tmp;
    }
    return 0;
}

int deleteBinHeap(struct binHeap *pq, uint index)
{
    int ret = 0;
    if (emptyBinHeap(pq)) {
        WARN("priority queue is empty\n");
        return 1;
    }

    int *data = NULL;
    data = pq->elements;
    data[index] = data[pq->size];
    data[pq->size] = 0;
    pq->size--;
    ret = percolateDown(pq, index);
    return ret;
}
