#include <types.h>

#include <tree.h>

#ifndef __SPLAY_TREE__
#define __SPLAY_TREE__

//#define RECUR_SPLAY_TREE

typedef struct treeNode splayTree;

extern splayTree *insertSplayTree(int element, splayTree *st);
extern splayTree *buildSplayTree(int *elements, uint num);

extern void freeSplayTree(splayTree *st);

extern splayTree *allocSplayTreeNode(int element);
extern void freeSplayTreeNode(splayTree *st);

extern splayTree *accessSplayTree(int element, splayTree *st);
extern splayTree *deleteSplayTree(int element, splayTree *st);

extern splayTree *fmaxSplayTree(splayTree *st);
extern splayTree *fminSplayTree(splayTree *st);

extern int vmaxSplayTree(splayTree *st);
extern int vminSplayTree(splayTree *st);

extern void prSplayTree(splayTree *st);

#endif
