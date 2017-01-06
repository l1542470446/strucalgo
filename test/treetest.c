#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <saprint.h>
#include <tree.h>

extern void simpleTreeTest();

void main()
{
    simpleTreeTest();
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
