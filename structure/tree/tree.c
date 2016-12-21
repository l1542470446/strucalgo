#include <tree.h>
#include <types.h>

uint layerBinTree(uint num)
{
    uint n, layer = 0;
    for (n = num; n > 0; n = n / 2)
        layer++;
    return layer;
}
