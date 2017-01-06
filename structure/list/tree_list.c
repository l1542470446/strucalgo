#include <malloc.h>
#include <string.h>

#include <types.h>
#include <tree.h>
#include <saprint.h>

struct treeNodeList *allocTnl()
{
    struct treeNodeList *tnl = NULL;
    tnl = malloc(sizeof(struct treeNodeList));
    if (tnl == NULL) {
        ERROR("tree node list alloc fail!\n");
        return tnl;
    }
    tnl->next = tnl->prev = tnl;
    return tnl;
}

void freeTnl(struct treeNodeList *tnl)
{
    free(tnl);
    tnl = NULL;
}

void listDelTnl(struct treeNodeList *tnl)
{
    struct treeNodeList *prev, *next;
    prev = tnl->prev;
    next = tnl->next;
    prev->next = next;
    next->prev = prev;
    freeTnl(tnl);
}

void freeTnlList(struct treeNodeList *tnl)
{
    struct treeNodeList *tmp;
    for (tmp = tnl->next; tmp != tnl; tmp = tnl->next) {
        listDelTnl(tmp);
    }
    //freeTnl(tnl);
}

void checkTnlList(struct treeNodeList *tnl)
{
    struct treeNodeList *tmp;
    for (tmp = tnl->prev; (tmp->type == TN_NULL) && (tmp != tnl); tmp = tnl->prev) {
        freeTreeNode(tmp->tn);
        listDelTnl(tmp);
    }
}

bool listAddTnlTail(struct treeNode *tn, struct treeNodeList *list)
{
    //init tnl
    struct treeNodeList *tnl = NULL;
    struct treeNodeList *prev;
    tnl = allocTnl();
    if (tnl == NULL) {
        return false;
    }
    //init tnl with tn
    if (tn == NULL) {
        tn = allocTreeNode();
        if (tn == NULL)
            return false;
        tnl->type = TN_NULL;
    } else {
        tnl->type = TN_FULL;
    }
    tnl->tn = tn;
    //tnl add to list
    prev = list->prev;
    prev->next = tnl;
    tnl->prev = prev;
    tnl->next = list;
    list->prev = tnl;
    return true;
}

bool listAddTnl(struct treeNode *tn, struct treeNodeList *list)
{
    //init tnl
    struct treeNodeList *tnl = NULL;
    struct treeNodeList *next;
    tnl = allocTnl();
    if (tnl == NULL) {
        return false;
    }
    //init tnl with tn
    if (tn == NULL) {
        tn = allocTreeNode();
        if (tn == NULL)
            return false;
        tnl->type = TN_NULL;
    } else {
        tnl->type = TN_FULL;
    }
    tnl->tn = tn;
    //tnl add to list
    next = list->next;
    next->prev = tnl;
    tnl->next = next;
    tnl->prev = list;
    list->next = tnl;
    return true;
}
