#include <malloc.h>
#include <string.h>

#include <saprint.h>
#include <types.h>
#include <sort.h>

void findMaxAndMin(int *data, uint n, int *max, int *min)
{
    int *a = NULL;
    a = data;
    unsigned int i;
    *min = a[0];
    for (i = 1; i < n; i++){
        if (a[i] < *min){
            *min = a[i];
        } else if (a[i] > *max) {
            *max = a[i];
        }
    }
}

void bSort(int *data, uint n)
{
    int max,min,off;
    findMaxAndMin(data, n, &max, &min);
    off = 0 - min;

    uint *udata = NULL;
    uint umax;
    umax = (uint)(max+off+1);
    udata = malloc(umax * sizeof(int));
    memset(udata, 0, sizeof(*udata));
    uint i,j;
    for (i = 0; i < n; i++) {
        udata[ data[i] + off ]++;
    }
    for (i = 0,j = 0; i < umax; i++) {
        if (udata[i] != 0) {
            data[j++] = i - off;
        }
    }
    free(udata);
}

void bucketSort(struct dataArray *data)
{
    bSort(data->data, data->nr);
    saprint(data);
}
