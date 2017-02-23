#include <types.h>

#ifndef __TREE__
#define __TREE__

/***********************
* num : element number in a tree
* return : layers
***********************/
extern uint layerBinHeap(uint num);

/* tree node */
struct treeNode {
    int element;
    struct treeNode *left;
    struct treeNode *right;
};

extern uint layerBinTree(struct treeNode *tn);
extern int maxBinTree(struct treeNode *tn);
extern int minBinTree(struct treeNode *tn);
extern uint findAbMaxBTree(struct treeNode *tn);

/* tree node list */
struct treeNodeList {
#define TN_NULL 0
#define TN_FULL 1
//#define TN_ROOT 4
    uint type;
    struct treeNode *tn;
    struct treeNodeList *prev;
    struct treeNodeList *next;
};
/* tree node functions */
extern struct treeNode *allocTreeNode();
extern void freeTreeNode(struct treeNode *tn);

/* tree node list functions */
extern struct treeNodeList *allocTnl();
extern void freeTnl(struct treeNodeList *tnl);
extern void freeTnlList(struct treeNodeList *tnl);
extern void checkTnlList(struct treeNodeList *tnl);
extern bool listAddTnl(struct treeNode *tn, struct treeNodeList *list);
extern bool listAddTnlTail(struct treeNode *tn, struct treeNodeList *list);
extern void listDelTnl(struct treeNodeList *tnl);

#endif
