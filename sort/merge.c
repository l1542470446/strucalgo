#include <malloc.h>
#include <string.h>

#include <saprint.h>
#include <sort.h>


void merge(struct dataArray *dA, int *tmp, unsigned int lpos, unsigned int rpos, unsigned int rend)
{
    unsigned int lend,sum,tpos,i;
    int *data = dA->data;
    lend = rpos - 1;
    tpos = lpos;
    sum = rend - lpos + 1;

    while ((lpos <= lend) && (rpos <= rend)) {
        if (data[lpos] > data[rpos])
            tmp[tpos++] = data[rpos++];
        else
            tmp[tpos++] = data[lpos++];
    }
    while (lpos <= lend)
        tmp[tpos++] = data[lpos++];
    while (rpos <= rend)
        tmp[tpos++] = data[rpos++];

    for (i = 0; i < sum; i++, rend--)
        data[rend] = tmp[rend];
    saprint(dA);
}

void mSort(struct dataArray *dA, int *tmp, unsigned int lpos, unsigned int rpos)
{
    unsigned int center;
    if (lpos < rpos) {
        center = (rpos + lpos) / 2;
        mSort(dA,tmp,lpos,center);
        mSort(dA,tmp,center+1,rpos);
        merge(dA,tmp,lpos,center+1,rpos);
    }
}

void mergeSort(struct dataArray *data)
{
    int *tmp = NULL;
    tmp = malloc(data->nr * sizeof(int));
    memset(tmp,0,sizeof(*tmp));
    if (tmp != NULL) {
        mSort(data,tmp,0,data->nr-1);
        free(tmp);
    }
}
