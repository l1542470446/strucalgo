#include <malloc.h>
#include <string.h>

#include <splay_tree.h>
#include <search_tree.h>

splayTree *insertSplayTree(int element, splayTree *st)
{
    splayTree *tmp;
    tmp = insertSearchTree(element, st);
    return tmp;
}

splayTree *buildSplayTree(int *elements, uint num)
{
    splayTree *tmp;
    tmp = buildSearchTree(elements, num);
    return tmp;
}

void freeSplayTree(splayTree *st)
{
    freeSearchTree(st);
}

void freeSplayTreeNode(splayTree *st)
{
    freeSearchTreeNode(st);
}

/*            k3                k1
 *           /  \              /  \
 *          k2   A  ---->     C   k2
 *         /  \                  /  \
 *        k1  B                 D   k3
 *       /  \                      /  \
 *      C   D                     B    A
 */

static splayTree *leftRotateWithLeft(splayTree *k3)
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

static splayTree *rightRotateWithRight(splayTree *k3)
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

static splayTree *leftRotateWithRight(splayTree *k3)
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

static splayTree *rightRotateWithLeft(splayTree *k3)
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
                    st = leftRotateWithLeft(st);
                }
            }
        } else if (element > child->element) {
            right = child->right;
            if (right == NULL) {
                child->right = accessSplayTree(element, right);
            } else {
                child->right = accessSplayTree(element, right);
                if (element == child->right->element) {
                    st = leftRotateWithRight(st);
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
                    st = rightRotateWithLeft(st);
                }
            }
        } else if (element > child->element) {
            right = child->right;
            if (right == NULL) {
                child->right = accessSplayTree(element, right);
            } else {
                child->right = accessSplayTree(element, right);
                if (element == child->right->element) {
                    st = rightRotateWithRight(st);
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
