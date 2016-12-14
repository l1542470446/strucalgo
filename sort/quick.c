#include <saprint.h>
#include <sort.h>

#define OFFSET 3

int qMedian(int *array,unsigned int lpos,unsigned int rpos)
{
    unsigned int center = (lpos+rpos) / 2;
    // lpos,center,rpos -> sort
    if (array[lpos] > array[center])
        dataExchange(array+lpos, array+center);
    if (array[center] > array[rpos])
        dataExchange(array+center, array+rpos);
    if (array[lpos] > array[rpos])
        dataExchange(array+lpos, array+rpos);
    // swap array[center] & array[rpos-1]
    dataExchange(array+center, array+rpos-1);
    return array[rpos-1];
}

void qSort(struct dataArray *data,unsigned int lpos,unsigned int rpos)
{
    int *array = data->data;
    int pivot;
    unsigned int i,j;

    if ((lpos + OFFSET) < rpos) {
        pivot = qMedian(array, lpos, rpos);
        i = lpos;
        j = rpos-1;
        for(;;) {
            while (array[++i] < pivot);
            while (array[--j] > pivot);
            if (i < j)
                dataExchange(array+i,array+j);
            else
                break;
        }
        dataExchange(array+rpos-1,array+i);
        qSort(data, lpos, i-1);
        qSort(data, i+1, rpos);
    } else {
        iSort(array+lpos, rpos - lpos + 1);
        saprint(data);
    }
}

void quickSort(struct dataArray *data)
{
    qSort(data, 0, data->nr-1);
}
