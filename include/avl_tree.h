
#include <types.h>
#include <tree.h>

#ifndef __AVL_TREE__
#define __AVL_TREE__

struct avlTree {
    struct treeNode tn;
    int height;
};

#define toAvlTree(node) container_of(node, struct avlTree, tn)

extern struct avlTree *allocAvlTree(int element);
extern void freeAvlTreeNode(struct avlTree *at);

extern struct avlTree *insertAvlTree(int element, struct avlTree *at);
extern struct avlTree *deleteAvlTree(int element, struct avlTree *at);

extern struct avlTree *buildAvlTree(int *elements, uint num);
extern void freeAvlTree(struct avlTree *at);

extern struct avlTree *fminAvlTree(struct avlTree *at);
extern struct avlTree *fmaxAvlTree(struct avlTree *at);

extern int vminAvlTree(struct avlTree *at);
extern int vmaxAvlTree(struct avlTree *at);

extern void prAvlTree(struct avlTree *at);

#endif
