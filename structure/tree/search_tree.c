#include <malloc.h>
#include <string.h>

#include <tree.h>
#include <types.h>
#include <saprint.h>
#include <search_tree.h>

searchTree *allocSearchTree(int element)
{
    searchTree *st = NULL;
    st = malloc(sizeof(searchTree));
    if (st == NULL) {
        ERROR("alloc search tree fail !\n");
        return st;
    }

    st->element = element;
    st->left = st->right = NULL;
    return st;
}

void freeSearchTreeNode(searchTree *st)
{
    free(st);
    st = NULL;
}

void freeSearchTree(searchTree *st)
{
    if (st == NULL)
        return;
    freeSearchTree(st->left);
    freeSearchTree(st->right);
    freeSearchTreeNode(st);
}

static searchTree *__insertSearchTree(searchTree *node, searchTree *st)
{
    if (st == NULL)
        return node;
    if (node->element < st->element) {
        st->left = __insertSearchTree(node, st->left);
    } else {
        st->right = __insertSearchTree(node, st->right);
    }
    return st;
}

searchTree *insertSearchTree(int element, searchTree *st)
{
    searchTree *newNode = NULL;
    searchTree *newTree = NULL;

    newNode = allocSearchTree(element);
    if (newNode == NULL) {
        return NULL;
    }

    return __insertSearchTree(newNode, st);
}

searchTree *buildSearchTree(int *elements, uint num)
{
    uint i;
    if (num == 0)
        return NULL;
    searchTree *st = NULL;
    st = allocSearchTree(elements[0]);
    if (st == NULL) {
        return NULL;
    }
    for (i = 1; i < num; i++) {
        insertSearchTree(elements[i], st);
    }
    return st;
}

#if 1 //recursive function

searchTree *fminSearchTree(searchTree *st)
{
    if (st->left == NULL) {
        return st;
    }
    return fminSearchTree(st->left);
}

searchTree *fmaxSearchTree(searchTree *st)
{
    if (st->right == NULL) {
        return st;
    }
    return fmaxSearchTree(st->right);
}

#else

searchTree *fminSearchTree(searchTree *st)
{
    searchTree *stmin;
    stmin = st;

    while (stmin->left != NULL) {
        stmin = stmin->left;
    }
    return stmin;
}

searchTree *fmaxSearchTree(searchTree *st)
{
    searchTree *stmax;
    stmax = st;

    while (stmax->right != NULL) {
        stmax = stmax->right;
    }
    return stmax;

}

#endif

int vminSearchTree(searchTree *st)
{
    searchTree *node;
    node = fminSearchTree(st);
    return node->element;
}

int vmaxSearchTree(searchTree *st)
{
    searchTree *node;
    node = fmaxSearchTree(st);
    return node->element;
}

searchTree *findSearchTree(int element, searchTree *st)
{
    if (st == NULL)
        return NULL;
    if (element < st->element) {
        return findSearchTree(element, st->left);
    } else if (element > st->element) {
        return findSearchTree(element, st->right);
    } else {
        return st;
    }
}

searchTree *delSearchTree(int element, searchTree *st)
{
    searchTree *tmp;
    if (st == NULL) {
        //WARN("could not find element\n");
    //1. find element
    } else if (element < st->element) {
        st->left = delSearchTree(element, st->left);
    } else if (element > st->element) {
        st->right = delSearchTree(element, st->right);
    //2. child node have two
    } else if (st->left && st->right) {
        tmp = fminSearchTree(st->right);
        st->element = tmp->element;
        st->right = delSearchTree(tmp->element, st->right);
    //3. child node have one or zero
    } else {
        tmp = st;
        if (st->right == NULL) {
            st = st->left;
        } else if (st->left == NULL) {
            st = st->right;
        }
        freeSearchTreeNode(tmp);
    }
    return st;
}

void prSearchTree(searchTree *st)
{
    prSimpBinTree(st);
}
