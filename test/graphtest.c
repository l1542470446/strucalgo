#include <string.h>
#include <malloc.h>

#include <types.h>
#include <graph.h>

extern void graphPrintTest(void);

int main(void)
{
    //graphPrintTest();
    topSortTest();
}

static struct graph *createGraphTest()
{
/** graph adjacency list
 * 1 -> 2 -> 4 -> 3
 * 2 -> 4 -> 5
 * 3 -> 6
 * 4 -> 6 -> 7 -> 3
 * 5 -> 4 -> 7
 * 6
 * 7 -> 6
 */
    int32_t ids[7] = {1, 2, 3, 4, 5, 6, 7};
    struct graph *gra = NULL;
    gra = createGraph(7, ids);
    idenLinkVertex(gra, 1, 2);
    idenLinkVertex(gra, 1, 4);
    idenLinkVertex(gra, 1, 3);
    idenLinkVertex(gra, 2, 4);
    idenLinkVertex(gra, 2, 5);
    idenLinkVertex(gra, 3, 6);
    idenLinkVertex(gra, 4, 6);
    idenLinkVertex(gra, 4, 7);
    idenLinkVertex(gra, 4, 3);
    idenLinkVertex(gra, 5, 4);
    idenLinkVertex(gra, 5, 7);
    idenLinkVertex(gra, 7, 6);
    return gra;
}

void graphPrintTest()
{
    struct graph *gra = NULL;
    gra = createGraphTest();
    prGraph(gra);
}

void topSortTest()
{
    struct graph *gra = NULL;
    gra = createGraphTest();
    topSortGraph(gra);
}
