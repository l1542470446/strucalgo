#include <function.h>
#include <types.h>

/* find max and min value in a array */
void findMaxAndMin(int *data, uint n, int *max, int *min)
{
    if (n < 2)
        return;
    int *a = NULL;
    a = data;
    unsigned int i;

    if (a[0] > a[1]) {
        *min = a[1];
        *max = a[0];
    } else {
        *max = a[1];
        *min = a[0];
    }

    for (i = 2; i < n; i++){
        if (a[i] < *min){
            *min = a[i];
        } else if (a[i] > *max) {
            *max = a[i];
        }
    }
}

/* calculate maximum absolute value in a array */
uint findMaxAbsoVal(int *data, uint n)
{
    int max,min;
    uint abso = 0;
    findMaxAndMin(data, n, &max, &min);
    if (max <= 0) {
        abso = (uint)(0 - min);
    } else if (min >= 0){
        abso = max;
    } else {
        abso = 0 - min;
        if (abso < max)
            abso = max;
    }
    return abso;
}

/* swap two data*/
void dataExchange(int *a,int *b)
{
    int c;
    c=*a;
    *a=*b;
    *b=c;
}

/* calculate data bit */
uchar uDataBit(uint data)
{
    uchar bit = 0;
    for (; data > 0; data /= 10, bit++);
    return bit;
}
