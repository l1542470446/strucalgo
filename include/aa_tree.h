#include <tree.h>
#include <types.h>

#ifndef __AA_TREE__
#define __AA_TREE__

struct aaTree {
    struct treeNode tn;
    int32_t level;
};

#define toAaTree(node) container_of(node, struct aaTree, tn)

extern struct aaTree *allocAaTreeNode(int32_t element);
extern void freeAaTreeNode(struct aaTree *at);

extern struct aaTree *insertAaTree(int32_t element, struct aaTree *at);
extern struct aaTree *deleteAaTree(int32_t element, struct aaTree *at);

extern struct aaTree *buildAaTree(int32_t *elements, uint32_t num);
extern void freeAaTree(struct aaTree *at);

extern struct aaTree *fminAaTree(struct aaTree *at);
extern struct aaTree *fmaxAaTree(struct aaTree *at);

extern int vminAaTree(struct aaTree *at);
extern int vmaxAaTree(struct aaTree *at);

extern void prAaTree(struct aaTree *at);

#endif
