#include <string.h>
#include <malloc.h>

#include <tree.h>
#include <types.h>
#include <saprint.h>
#include <search_tree.h>
#include <avl_tree.h>

struct avlTree *allocAvlTree(int element)
{
    struct avlTree *at = NULL;
    at = malloc(sizeof(struct avlTree));
    if (at == NULL) {
        ERROR("can not alloc memory for avl tree !\n");
        return NULL;
    }
    at->tn.element = element;
    at->tn.left = at->tn.right = NULL;
    at->height = 0;
    return at;
}

void freeAvlTreeNode(struct avlTree *at)
{
    free(at);
    at = NULL;
}

static int height(struct avlTree *at)
{
    if (at == NULL) {
        return -1;
    } else {
        return at->height;
    }
}

//update father tree height base on new child tree
static int updateHeight(struct avlTree *at)
{
    if (at == NULL)
        return -1;
    struct avlTree *left , *right;
    left = toAvlTree(at->tn.left);
    right = toAvlTree(at->tn.right);
    int h1 = height(left);
    int h2 = height(right);
    int h3 = (h1 > h2) ? h1 : h2;
    at->height = h3 + 1;
    return at->height;
}

/*          k2                     k1          k2.left = C
 *         /  \                   /  \         k1.right = k2
 *        k1  A   ------->       B   K2
 *       /  \                   /   /  \
 *      B   C                  D   C   A
 *     /
 *    D
 */

static struct avlTree *_singleRotateWithLeft(struct avlTree *k2)
{
    struct avlTree *k1, *tmpC;
    k1 = toAvlTree(k2->tn.left);
    tmpC = toAvlTree(k1->tn.right);
    k2->tn.left = &(tmpC->tn);
    k1->tn.right = &(k2->tn);
    updateHeight(k2);
    updateHeight(k1);
    return k1;
}

/*        k2                      k1            k2.right = k1.left(B)
 *       /  \                    /  \           k1.left = k2
 *      A   k1    ------->      k2  C
 *         /  \                /  \  \
 *        B   C               A   B   D
 *             \
 *             D
 */

static struct avlTree *_singleRotateWithRight(struct avlTree *k2)
{
    struct avlTree *k1, *tmpB;
    k1 = toAvlTree(k2->tn.right);
    tmpB = toAvlTree(k1->tn.left);
    k2->tn.right = &(tmpB->tn);
    k1->tn.left = &(k2->tn);
    updateHeight(k2);
    updateHeight(k1);
    return k1;
}

/*             k1                 k1                    k3
 *            /  \               /  \                 /    \
 *           k2   A   ----->    k3  A     ----->     k2     k1
 *          /  \               /  \                 /  \   /  \
 *         B   k3             k2  D                B   C  D   A
 *            /  \           /  \
 *           C   D          B   C
 *    note : node C&D , only one exist
 */

static struct avlTree *_doubleRotateWithLeft(struct avlTree *k1)
{
    struct avlTree *k2,*k3;
    k2 = toAvlTree(k1->tn.left);
    k3 = _singleRotateWithRight(k2);
    k1->tn.left = &(k3->tn);
    return _singleRotateWithLeft(k1);
}

/*         k1                k1                     k3
 *        /  \              /  \                   /   \
 *       A   k2   ----->   A   k3    ----->      k1     k2
 *          /  \              /  \              /  \   /  \
 *         k3  B             C   k2            A   C  null B
 *        /  \                  /  \
 *       C   null            null  B
 */

static struct avlTree *_doubleRotateWithRight(struct avlTree *k1)
{
    struct avlTree *k2, *k3;
    k2 = toAvlTree(k1->tn.right);
    k3 = _singleRotateWithLeft(k2);
    k1->tn.right = &(k3->tn);
    return _singleRotateWithRight(k1);
}

struct avlTree *insertAvlTree(int element, struct avlTree *at)
{
    struct avlTree *left, *right;
    if (at == NULL) {
        at = allocAvlTree(element);
    } else if (element < at->tn.element) {
        left = toAvlTree(at->tn.left);
        right = toAvlTree(at->tn.right);
        left = insertAvlTree(element, left);
        at->tn.left = &(left->tn);
        if (height(left) - height(right) == 2) {
            if (element < left->tn.element) {
                at = _singleRotateWithLeft(at);
            } else {
                at = _doubleRotateWithLeft(at);
            }
        }
    } else if (element >= at->tn.element) {
        left = toAvlTree(at->tn.left);
        right = toAvlTree(at->tn.right);
        right = insertAvlTree(element, right);
        at->tn.right = &(right->tn);
        if (height(right) - height(left) == 2) {
            if (element >= right->tn.element) {
                at = _singleRotateWithRight(at);
            } else {
                at = _doubleRotateWithRight(at);
            }
        }
    }
    updateHeight(at);
    return at;
}

struct avlTree *deleteAvlTree(int element, struct avlTree *at)
{
    struct avlTree *left, *right, *tmp;
    if (at == NULL)
        return NULL;

    left = toAvlTree(at->tn.left);
    right = toAvlTree(at->tn.right);
    if (element < at->tn.element) {
        left = deleteAvlTree(element, left);
        if (left == NULL) {
            at->tn.left = NULL;
        } else {
            at->tn.left = &(left->tn);
        }
        updateHeight(at);
        if (height(right) - height(left) == 2) {
            if (right->tn.right != NULL) {
                at = _singleRotateWithRight(at);
            } else {
                at = _doubleRotateWithRight(at);
            }
        }
    } else if (element > at->tn.element) {
        right = deleteAvlTree(element, right);
        if (right == NULL) {
            at->tn.right = NULL;
        } else {
            at->tn.right = &(right->tn);
        }
        updateHeight(at);
        if (height(left) - height(right) == 2) {
            if (left->tn.left != NULL) {
                at = _singleRotateWithLeft(at);
            } else {
                at = _doubleRotateWithLeft(at);
            }
        }
    } else if (at->tn.left && at->tn.right) {
        //printf("ssssssssssssssssssss\n");
        tmp = fminAvlTree(right);
        at->tn.element = tmp->tn.element;
        right = deleteAvlTree(tmp->tn.element, right);
        if (right == NULL) {
            //printf("dddd\n");
            at->tn.right = NULL;
        } else {
            //printf("fffffff\n");
            at->tn.right = &(right->tn);
        }
        updateHeight(at);
    } else {
        //printf("aaaaaaaaaaaaaaaaaaaaaaaaa\n");
        tmp = at;
        if (right == NULL) {
            //printf("bbbb\n");
            at = left;
        } else {
            //printf("cccc\n");
            at = right;
        }
        freeAvlTreeNode(tmp);
        //printf("eeeee\n");
        updateHeight(at);
    }
    return at;
}

struct avlTree *buildAvlTree(int *elements, uint num)
{
    struct avlTree *at = NULL;
    uint i;
    for (i = 0; i < num; i++) {
        at = insertAvlTree(elements[i], at);
    }
    return at;
}

void freeAvlTree(struct avlTree *at)
{
    struct avlTree *left, *right;
    if (at == NULL)
        return;
    left = toAvlTree(at->tn.left);
    right = toAvlTree(at->tn.right);
    freeAvlTree(left);
    freeAvlTree(right);
    freeAvlTreeNode(at);
}

struct avlTree *fminAvlTree(struct avlTree *at)
{
    struct avl_tree *minTree;
    struct treeNode *tn;
    struct searchTree *tmp;
    tn = &(at->tn);
    tmp = fminSearchTree((struct searchTree *)tn);
    minTree = toAvlTree((struct treeNode *)tmp);
    return minTree;
}

struct avlTree *fmaxAvlTree(struct avlTree *at)
{
    struct avl_tree *maxTree;
    struct treeNode *tn;
    struct searchTree *tmp;
    tn = &(at->tn);
    tmp = fmaxSearchTree((struct searchTree *)tn);
    maxTree = toAvlTree((struct treeNode *)tmp);
    return maxTree;

}

int vminAvlTree(struct avlTree *at)
{
    struct avlTree *tmp;
    tmp = fminAvlTree(at);
    return tmp->tn.element;
}

int vmaxAvlTree(struct avlTree *at)
{
    struct avlTree *tmp;
    tmp = fmaxAvlTree(at);
    return tmp->tn.element;
}

void prAvlTree(struct avlTree *at)
{
    struct treeNode *tn;
    tn = &(at->tn);
    prSimpBinTree(tn);
}
