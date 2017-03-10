#include <malloc.h>
#include <string.h>

#include <saprint.h>
#include <splay_tree.h>
#include <search_tree.h>

splayTree *allocSplayTreeNode(int element)
{
    return allocSearchTree(element);
}

splayTree *buildSplayTree(int *elements, uint num)
{
    splayTree *tmp;
    tmp = buildSearchTree(elements, num);
    return tmp;
}

/*            k3                k1
 *           /  \              /  \
 *          k2   A  ---->     C   k2
 *         /  \                  /  \
 *        k1  B                 D   k3
 *       /  \                      /  \
 *      C   D                     B    A
 */

static splayTree *_leftRotateWithLeft(splayTree *k3)
{
    splayTree *k2, *k1;
    k2 = k3->left;
    k1 = k2->left;
    k2->left = k1->right;
    k3->left = k2->right;
    k1->right = k2;
    k2->right = k3;
    return k1;
}

/*        k3                     k1
 *       /  \                   /  \
 *      A   k2    ---->        k2   D
 *         /  \               /  \
 *        B   k1             k3  C
 *           /  \           /  \
 *          C    D         A   B
 */

static splayTree *_rightRotateWithRight(splayTree *k3)
{
    splayTree *k2, *k1;
    k2 = k3->right;
    k1 = k2->right;
    k3->right = k2->left;
    k2->right = k1->left;
    k1->left = k2;
    k2->left = k3;
    return k1;
}

/*           k3                   k1
 *          /  \                /    \
 *         k2   A   ---->      k2    k3
 *        /  \                /  \  /  \
 *       B   k1              B   C D   A
 *          /  \
 *         C    D
 */

static splayTree *_leftRotateWithRight(splayTree *k3)
{
    splayTree *k2, *k1;
    k2 = k3->left;
    k1 = k2->right;
    k2->right = k1->left;
    k3->left = k1->right;
    k1->left = k2;
    k1->right = k3;
    return k1;
}

/*          k3                  k1
 *         /  \               /    \
 *        A   k2   ---->     k3    k2
 *           /  \           /  \  /  \
 *          k1   B         A   C D   B
 *         /  \
 *        C    D
 */

static splayTree *_rightRotateWithLeft(splayTree *k3)
{
    splayTree *k2, *k1;
    k2 = k3->right;
    k1 = k2->left;
    k3->right = k1->left;
    k2->left = k1->right;
    k1->left = k3;
    k1->right = k2;
    return k1;
}

/*          k2                   k1
 *         /  \                 /  \
 *        A   k1   ---->       k2   C
 *           /  \             /  \
 *          B    C           A    B
 */

static splayTree *rightRotate(splayTree *k2)
{
    splayTree *k1;
    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    return k1;
}

/*          k2                k1
 *         /  \              /  \
 *        k1   A   ---->    B   k2
 *       /  \                  /  \
 *      B    C                C    A
 */

static splayTree *leftRotate(splayTree *k2)
{
    splayTree *k1;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    return k1;
}

/* splay tree recurisive achieve */
#ifdef RECUR_SPLAY_TREE

splayTree *insertSplayTree(int element, splayTree *st)
{
    splayTree *tmp;
    tmp = insertSearchTree(element, st);
    return tmp;
}

splayTree *accessSplayTree(int element, splayTree *st)
{
    splayTree *child, *left, *right;
    if (st == NULL) {
        printf("can not find element %d in splay tree\n", element);
        //return NULL;
    } else if (element < st->element) {
        child = st->left;
        if (child == NULL) {
            st->left = accessSplayTree(element, child);
        } else if (element < child->element){
            left = child->left;
            if (left == NULL) {
                child->left = accessSplayTree(element, left);
            } else {
                child->left = accessSplayTree(element, left);
                if (element == child->left->element) {
                    st = __leftRotateWithLeft(st);
                }
            }
        } else if (element > child->element) {
            right = child->right;
            if (right == NULL) {
                child->right = accessSplayTree(element, right);
            } else {
                child->right = accessSplayTree(element, right);
                if (element == child->right->element) {
                    st = _leftRotateWithRight(st);
                }
            }
        } else {
            st = leftRotate(st);
        }
    } else if (element > st->element) {
        child = st->right;
        if (child == NULL) {
            st->left = accessSplayTree(element, child);
        } else if (element < child->element){
            left = child->left;
            if (left == NULL) {
                child->left = accessSplayTree(element, left);
            } else {
                child->left = accessSplayTree(element, left);
                if (element == child->left->element) {
                    st = _rightRotateWithLeft(st);
                }
            }
        } else if (element > child->element) {
            right = child->right;
            if (right == NULL) {
                child->right = accessSplayTree(element, right);
            } else {
                child->right = accessSplayTree(element, right);
                if (element == child->right->element) {
                    st = _rightRotateWithRight(st);
                }
            }
        } else {
            st = rightRotate(st);
        }
    } else {
        //return st;
    }
    return st;
}

/*         k1                   M
 *        /  \     del k1      / \
 *       L    R    ---->      L   R
 *      / \                  / \
 *     .....                .....
 *     D   M                D
 */

splayTree *deleteSplayTree(int element, splayTree *st)
{
    splayTree *k1, *left, *right, *max, *parent, *next;
    k1 = accessSplayTree(element, st);
    if (k1 == NULL)
        return NULL;
    left = k1->left;//L
    right = k1->right;//R
    freeSplayTreeNode(k1);
    if (left == NULL) {
        return right;
    } else if (left->right == NULL) {
        left->right = right;
        return left;
    } else {
        for (next = left->right; next->right != NULL; next = parent->right) {
            parent = next;
            max = parent->right;//M
        }
        max->left = left;
        max->right = right;
        parent->right = NULL;
        return max;
    }
}

#else /* splay tree non-recurisive achieve */

/*     L      k2      R          L     k1        R
 *           /  \                     /  \      /
 *          k1   A     ----->        B    C    k2
 *         /  \                                  \
 *        B    C                                  A
 */

/*     L      k3      R          L     k1         R
 *           /  \                     /  \       /
 *          k2   A     ----->        C    D     k2
 *         /  \                                   \
 *        k1   B                                  k3
 *       /  \                                    /  \
 *      C    D                                  B    A
 */

splayTree *accessSplayTree(int element, splayTree *st)
{
    if (st == NULL)
        return NULL;
    splayTree header;
    splayTree *treeMax, *treeMin;
    header.left = header.right = NULL;
    treeMax = treeMin = &header;

    while (element != st->element) {
        if (element < st->element) {
            if (st->left != NULL) {
                if ((element < st->left->element) && (st->left->left != NULL)) {
                    st = leftRotate(st);
                    treeMax->left = st;
                    st = st->left;
                } else {
                    treeMax->left = st;
                    st = st->left;
                }
                treeMax = treeMax->left;
                treeMax->left = NULL;

            } else {
                break;
            }
        } else {
            if (st->right != NULL) {
                if ((element > st->right->element) && (st->right->right != NULL)) {
                    st = rightRotate(st);
                    treeMin->right = st;
                    st = st->right;
                } else {
                    treeMin->right = st;
                    st = st->right;
                }
                treeMin = treeMin->right;
                treeMin->right = NULL;
            } else {
                break;
            }
        }
    }
    if (header.right != NULL) {
        treeMin->right = st->left;
        st->left = header.right;
    }
    if (header.left != NULL) {
        treeMax->left = st->right;
        st->right = header.left;
    }
    return st;
}

splayTree *deleteSplayTree(int element, splayTree *st)
{
    splayTree *newTree, *delTree;
    if (st != NULL) {
        newTree = accessSplayTree(element, st);
        if (element == newTree->element) {
            delTree = newTree;
            if (newTree->left == NULL) {
                newTree = newTree->right;
            } else {
                newTree = accessSplayTree(element, newTree->left);
                newTree->right = delTree->right;
            }
        }
    } else {
        newTree = st;
    }
    freeSplayTreeNode(delTree);
    return newTree;
}

splayTree *insertSplayTree(int element, splayTree *st)
{
    splayTree *newNode = NULL;
    newNode = allocSplayTreeNode(element);
    if (newNode == NULL) {
        ERROR("alloc memory fail for splay tree node\n");
        return NULL;
    }
    if (st == NULL) {
        st = newNode;
    } else {
        st = accessSplayTree(element, st);
        if (element < st->element) {
            newNode->left = st->left;
            newNode->right = st;
            st->left = NULL;
            st = newNode;
        } else if (element > st->element) {
            newNode->right = st->right;
            newNode->left = st;
            st->right = NULL;
            st = newNode;
        } else {
            freeSplayTreeNode(newNode);
        }
    }
    return st;
}

#endif /* splay tree non-recurisive achieve */

splayTree *fmaxSplayTree(splayTree *st)
{
    return fmaxSearchTree(st);
}

splayTree *fminSplayTree(splayTree *st)
{
    return fminSearchTree(st);
}

int vmaxSplayTree(splayTree *st)
{
    return vmaxSearchTree(st);
}

int vminSplayTree(splayTree *st)
{
    return vminSearchTree(st);
}

void prSplayTree(splayTree *st)
{
    prSearchTree(st);
}

void freeSplayTree(splayTree *st)
{
    freeSearchTree(st);
}

void freeSplayTreeNode(splayTree *st)
{
    freeSearchTreeNode(st);
}
