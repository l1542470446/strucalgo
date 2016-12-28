#include <stdio.h>

#include <saprint.h>
#include <sort.h>
#include <function.h>
#include <types.h>
#include <queue.h>

/*******************************************
*           0
*       1       2
*     3   4   5   6
*   7   8   .......
* result: P->i ; Pleft->2*i+1 ; Pright->2*(i+1)
********************************************/

#define leftChild(i) (2*(i) + 1)

void percDown(int *data, int i, uint n, uint type)
{
    uint child;
    int temp;
    if (type == PQUEUE_MAX) {
        for (temp = data[i]; leftChild(i) < n; i = child) {
            child = leftChild(i);
            if (child != n-1 && data[child] < data[child + 1])
                child++;
            if (data[child] > temp)
                data[i] = data[child];
            else
                break;
        }
        data[i] = temp;
    } else if (type == PQUEUE_MIN) {
        for (temp = data[i]; leftChild(i) < n; i = child) {
            child = leftChild(i);
            if (child != n-1 && data[child] > data[child + 1])
                child++;
            if (data[child] < temp)
                data[i] = data[child];
            else
                break;
        }
        data[i] = temp;
    }
}

void buildHeap(int *data, uint n, uint type)
{
    int i;
    for (i = (n-1) / 2; i >= 0; i--) {
        percDown(data, i, n, type);
    }
}

void heapSort(struct dataArray *data)
{
    uint n = data->nr;
    int i;
    //buile heap
    printf(" build heap \n");
    for (i = (n-1) / 2; i >= 0; i--) {
        percDown(data->data, i, n, PQUEUE_MAX);
        saprint(data);
    }
    //delete max value
    printf(" delete max value ,and start sort \n");
    uint j;
    for (j = n-1; j > 0; j--) {
        dataExchange(data->data , data->data + j);
        percDown(data->data, 0, j, PQUEUE_MAX);
        saprint(data);
    }
}
