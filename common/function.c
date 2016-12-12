#include <function.h>

void dataExchange(int *a,int *b)
{
    int c;
    c=*a;
    *a=*b;
    *b=c;
}
