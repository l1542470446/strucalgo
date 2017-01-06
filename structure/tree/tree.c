#include <malloc.h>
#include <string.h>

#include <tree.h>
#include <types.h>
#include <saprint.h>

uint layerBinTree(uint num)
{
    uint n, layer = 0;
    for (n = num; n > 0; n = n / 2)
        layer++;
    return layer;
}

struct treeNode *allocTreeNode()
{
    struct treeNode *tn = NULL;
    tn = malloc(sizeof(struct treeNode));
    if (tn == NULL) {
        ERROR("tree node alloc fail!\n");
        return tn;
    }
    tn->left = tn->right = NULL;
    return tn;
}

void freeTreeNode(struct treeNode *tn)
{
    free(tn);
    tn = NULL;
}
