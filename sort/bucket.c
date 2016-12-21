#include <malloc.h>
#include <string.h>

#include <saprint.h>
#include <types.h>
#include <sort.h>
#include <function.h>

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
        while (udata[i]--) {
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
