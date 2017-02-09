#include <types.h>

#include <tree.h>

#ifndef __SEARCH_TREE__
#define __SEARCH_TREE__

typedef struct treeNode searchTree;

extern searchTree *allocSearchTree(int element);
extern void freeSearchTreeNode(searchTree *st);
extern void freeSearchTree(searchTree *st);

extern searchTree *buildSearchTree(int *elements, uint num);
extern searchTree *insertSearchTree(int element, searchTree *st);

extern searchTree *findSearchTree(int element, searchTree *st);
extern searchTree *delSearchTree(int element, searchTree *st);

extern searchTree *fminSearchTree(searchTree *st);
extern searchTree *fmaxSearchTree(searchTree *st);

extern int vminSearchTree(searchTree *st);
extern int vmaxSearchTree(searchTree *st);

extern void prSearchTree(searchTree *st);

#endif
