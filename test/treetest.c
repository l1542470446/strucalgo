#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <saprint.h>
#include <tree.h>
#include "data.h"

extern void simpleTreeTest();
extern void searchTreeTest();

void main()
{
    //simpleTreeTest();
    searchTreeTest();
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
