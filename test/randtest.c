#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include <rand.h>

extern void randtest(void);

int main()
{
    randtest();
}

void randtest(void)
{
    uint32_t i, j;
    uint64_t r;
    printf("\n--------------------rand test 1---------------------\n\n");
    randInit(111);
    for (i = 0; i < 10; i++) {
        r = randSa();
        printf("%lu  ", r);
    }
    printf("\n\n--------------------rand test 2---------------------\n\n");
    randInit(777);
    for (i = 0; i < 10; i++) {
        r = randSa();
        printf("%lu  ", r);
    }
    printf("\n\n--------------------rand region[0-51] test---------------------\n\n");
    for (j = 0; j < 5; j++) {
        for (i = 0; i < 10; i++) {
            r = randRegion(51);
            printf("%lu  ", r);
        }
        printf("\n");
    }
    printf("\n");
}
