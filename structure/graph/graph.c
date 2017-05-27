#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <saprint.h>
#include <graph.h>
#include <list.h>

static struct graphList *findGraList(struct graph *gra, struct graphNode *gnode)
{
    struct graphList *rlist = gra->lnode;
    uint32_t i;
    for (i = 0; i < gra->num; i++) {
        if (gnode == (rlist + i)->gnode) {
            return rlist + i;
        }
    }
    return NULL;
}

struct graph *createGraph(uint32_t num, int32_t *ids)
{
    struct graph *gra = NULL;
    struct graphNode *gnods = NULL;
    struct graphList *glist = NULL;

    gra = malloc(sizeof(struct graph));
    if (gra == NULL) {
        ERROR("malloc graph fail \n");
        goto err0;
    }

    gnods = (struct graphNode *)malloc(num * sizeof(struct graphNode));
    if (gnods == NULL) {
        ERROR("malloc %d graph node fail \n", num);
        goto err1;
    }

    glist = (struct graphList *)malloc(num * sizeof(struct graphList));
    if (glist == NULL) {
        ERROR("malloc %d graph list fail \n", num);
        goto err2;
    }

    uint32_t i;
    if (ids != NULL) {
        for (i = 0; i < num; i++) {
            gnods[i].iden = ids[i];
        }
    }
    for (i = 0; i < num; i++) {
        glist[i].gnode = gnods + i;
        glist[i].list.next = NULL;
    }

    gra->num = num;
    gra->lnode = glist;
    gra->gnodes = gnods;
    gra->hash = NULL;
    return gra;

err2:
    free(glist);
err1:
    free(gnods);
err0:
    free(gra);
    return NULL;
}

/**
 * @vs : vertex start
 * @ve : vertex end
 */
int nodeLinkVertex(struct graph *gra, struct graphNode *vs, struct graphNode *ve)
{
    struct graphList *glp, *gle = NULL, *gls = NULL;
    struct list_head *prev, *next;

    gle = malloc(sizeof(struct graphList));
    if (gle == NULL) {
        ERROR("alloc graph list fail !\n");
        goto err0;
    }
    gle->gnode = ve;
    gle->list.next = NULL;

    gls = findGraList(gra, vs);
    if (gls == NULL) {
        ERROR("can not find graph list [%d]!\n", vs->iden);
        goto err0;
    }
    prev = &(gls->list);
    next = prev->next;
    while (next != NULL) {
        prev = next;
        next = prev->next;
    }
    glp = toGraphList(prev);
    glp->list.next = &(gle->list);
    return 0;

err0:
    free(gle);
    return -1;
}

static struct graphNode *findGraNode(struct graph *gra, int32_t iden)
{
    uint32_t i, num = gra->num;
    struct graphNode *gnodes = gra->gnodes;
    for (i = 0; i < num; i++) {
        if (iden == (gnodes + i)->iden)
            return gnodes + i;
    }
    return NULL;
}

/**
 * @ids : iden of vertex that start
 * @ide : iden of vertex that end
 */
int idenLinkVertex(struct graph *gra, int32_t ids, int32_t ide)
{
    struct graphNode *vs = NULL, *ve = NULL;
    vs = findGraNode(gra, ids);
    ve = findGraNode(gra, ide);
    if (vs == NULL || ve == NULL) {
        return -1;
    }
    return nodeLinkVertex(gra, vs, ve);
}

void prGraph(struct graph *gra)
{
    struct graphList *glp, *glr, *gls = gra->lnode;
    struct list_head *pos;
    uint32_t i, num = gra->num;

    for (i = 0; i < num; i++) {
        glr = gls + i;
        printf("%d", glr->gnode->iden);
        graph_list_for_each(pos, &(glr->list)) {
            glp = toGraphList(pos);
            printf(" -> %d", glp->gnode->iden);
        }
        printf("\n");
    }
}
