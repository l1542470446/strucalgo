
#include <types.h>
#include <tree.h>

#ifndef __RB_TREE__
#define __RB_TREE__

typedef enum colourType {
    RB_RED,
    RB_BLACK
} colourType;

struct rbTree {
    struct treeNode tn;
    colourType colour;
};

#define toRbTree(node) container_of(node, struct rbTree, tn)

extern struct rbTree *buildRbTree(int *elements, uint num);
extern void freeRbTree(struct rbTree *rb);

extern struct rbTree *allocRbTreeNode(int element);
extern void freeRbTreeNode(struct rbTree *rb);

extern struct rbTree *insertRbTree(int element, struct rbTree *rb);
extern struct rbTree *deleteRbTree(int element, struct rbTree *rb);

extern struct rbTree *fmaxRbTree(struct rbTree *rb);
extern struct rbTree *fminRbTree(struct rbTree *rb);

extern int vminRbTree(struct rbTree *rb);
extern int vmaxRbTree(struct rbTree *rb);

extern void prRbTree(struct rbTree *rb);

#endif
