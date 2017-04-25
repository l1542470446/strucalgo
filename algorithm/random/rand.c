#include <stdio.h>

#include <types.h>
#include <rand.h>

static uint64_t randSeed = 1;
#define A 48271
#define M 21474836471
#define Q (M / A)
#define R (M % A)

uint64_t randRegion(uint64_t reg)
{
    uint64_t r = randSa();
    return (uint64_t)(r % reg);
}

uint64_t randSa(void)
{
    int64_t tmpSeed;
    tmpSeed = A * (randSeed % Q) - R * (randSeed / Q);
    if (tmpSeed >= 0) {
        randSeed = (uint64_t)tmpSeed;
    } else {
        randSeed = (uint64_t)(M + tmpSeed);
    }
    return randSeed;
}

void randInit(uint64_t val)
{
    randSeed = val;
}
