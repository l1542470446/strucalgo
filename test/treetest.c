#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <saprint.h>
#include <tree.h>
#include "data.h"

extern void simpleTreeTest();
extern void searchTreeTest();
extern void avlTreeTest();
extern void splayTreeTest();
extern void rbTreeTest();

void main()
{
    //simpleTreeTest();
    //searchTreeTest();
    //avlTreeTest();
    //splayTreeTest();
    rbTreeTest();
}

#include <rb_tree.h>
void rbTreeTest()
{
    int data[10] = {1,2,3,4,5,6,7,8,9,10};
    struct rbTree *root;
    printf("---------------build a read-black-tree----------------\n");
    root = buildRbTree(data, 10);
    prRbTree(root);
    printf("--------------- insert element 20 --------------------\n");
    root = insertRbTree(20, root);
    prRbTree(root);
    printf("--------------- insert element 30 --------------------\n");
    root = insertRbTree(30, root);
    prRbTree(root);
    printf("--------------- insert element 25 --------------------\n");
    root = insertRbTree(25, root);
    prRbTree(root);
    printf("----------------delete element 10----------------------\n");
    root = deleteRbTree(10, root);
    prRbTree(root);
    printf("----------------delete element 40----------------------\n");
    root = deleteRbTree(40, root);
    prRbTree(root);
    freeRbTree(root);
    root = NULL;
}

#include <splay_tree.h>
void splayTreeTest()
{
    int data[10] = {11,15,8,1,6,5,4,3,2,7};
    splayTree *st;
    printf("----------build splay tree-----------\n");
    st = buildSplayTree(data, 10);
    prSplayTree(st);
    printf("----------access element 6-----------\n");
    st = accessSplayTree(6, st);
    prSplayTree(st);
    printf("----------access element 4-----------\n");
    st = accessSplayTree(4, st);
    prSplayTree(st);
    printf("----------access element 9-----------\n");
    st = accessSplayTree(9, st);
    prSplayTree(st);
    printf("----------delete element 2-----------\n");
    st = deleteSplayTree(2, st);
    prSplayTree(st);
    printf("----------insert element 20-----------\n");
    st = insertSplayTree(20, st);
    prSplayTree(st);

    freeSplayTree(st);
}

#include <avl_tree.h>
void avlTreeTest()
{
    int i;
    printf("elements : ");
    for (i = 0;i < 10; i++) {
        printf("%d ", arData10[i]);
    }
    printf("\n---------------------------\n");
    int max, min;
    struct avlTree *at = NULL;
    at = buildAvlTree(arData10, 10);
    prAvlTree(at);
    printf("---------------------------\n");
    max = vmaxAvlTree(at);
    min = vminAvlTree(at);
    printf("max = %d \n", max);
    printf("min = %d \n", min);
    printf("---------------------------\n");
    printf("delete %d\n", arData10[0]);
    at = deleteAvlTree(arData10[0], at);
    prAvlTree(at);
    printf("---------------------------\n");
    printf("delete %d\n", arData10[3]);
    at = deleteAvlTree(arData10[3], at);
    prAvlTree(at);
    printf("---------------------------\n");
    printf("delete %d %d %d %d \n", arData10[9], arData10[8], arData10[7], arData10[6]);
    at = deleteAvlTree(arData10[9], at);
    at = deleteAvlTree(arData10[8], at);
    at = deleteAvlTree(arData10[7], at);
    at = deleteAvlTree(arData10[6], at);
    prAvlTree(at);

    freeAvlTree(at);
}

#include <search_tree.h>
void searchTreeTest()
{
    int data;
    searchTree *st = NULL;
    st = buildSearchTree(arData10, 10);
    printf("----------search tree----------\n");
    prSearchTree(st);
    printf("-------------------------------\n");
    data = vmaxSearchTree(st);
    printf("max vlaue = %d\n", data);
    data = vminSearchTree(st);
    printf("min vlaue = %d\n", data);
    printf("-------------------------------\n");
    searchTree *snode = NULL;
    snode = findSearchTree(10, st);
    if (snode == NULL) {
        printf("cloud not find element %d\n", 10);
    } else {
        printf("already find element %d\n", snode->element);
    }

    snode = findSearchTree(20, st);
    if (snode == NULL) {
        printf("could not find element %d\n", 20);
    } else {
        printf("already find element %d\n", snode->element);
    }
    printf("------ delete element 10 ------\n");
    delSearchTree(10, st);
    prSearchTree(st);
    printf("------ delete element 85 ------\n");
    delSearchTree(85, st);
    prSearchTree(st);
    freeSearchTree(st);
}

void simpleTreeTest()
{
    struct treeNode *head , *left, *right, *cleft;
    head = left = right = cleft = NULL;
    head = allocTreeNode();
    left = allocTreeNode();
    cleft = allocTreeNode();
    right = allocTreeNode();
    if (head == NULL || left == NULL || right == NULL || cleft == NULL) {
        ERROR("simple tree test : alloc fail \n");
        goto free;
    }
    head->element = 10;
    left->element = 5;
    cleft->element = 3;
    right->element = 4;
    head->left = left;
    head->right = right;
    right->left = cleft;
    prSimpBinTree(head);
free:
    free(head);
    free(left);
    free(cleft);
    free(right);
}
