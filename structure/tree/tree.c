#include <malloc.h>
#include <string.h>

#include <tree.h>
#include <types.h>
#include <saprint.h>

uint layerBinHeap(uint num)
{
    uint n, layer = 0;
    for (n = num; n > 0; n = n / 2)
        layer++;
    return layer;
}

uint layerBinTree(struct treeNode *tn)
{
    if (tn == NULL)
        return 0;
    uint laLeft, laRigh, layer;
    laLeft = layerBinTree(tn->left);
    laRigh = layerBinTree(tn->right);
    layer = (laLeft > laRigh ? laLeft : laRigh);
    return (layer + 1);
}

int maxBinTree(struct treeNode *tn)
{
    if (tn == NULL)
        return 0;
    int mxLeft, mxRigh, maxchild, max;
    mxLeft = maxBinTree(tn->left);
    mxRigh = maxBinTree(tn->right);
    maxchild = (mxLeft > mxRigh ? mxLeft : mxRigh);
    max = (tn->element > maxchild ? tn->element : maxchild);
    return max;
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
