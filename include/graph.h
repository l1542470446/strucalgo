#include <types.h>
#include <list.h>

#ifndef __GRAPH_H__
#define __GRAPH_H__

struct graphNode {
	int32_t iden;
};

struct graphList {
    struct list_head list;
    struct graphNode *gnode;
    int32_t weight;
};

struct graph {
	uint32_t num;
	struct graphList *lnode;
    struct graphNode *gnodes;
	void *hash;
};

#define toGraphList(gl) container_of(gl, struct graphList, list)

/**
 * graph_list_for_each	-	iterate over a graph list
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
#define graph_list_for_each(pos, head) \
	for (pos = (head)->next; pos != NULL; pos = pos->next)

extern struct graph *createGraph(uint32_t num, int32_t *ids);
extern int addNodeToGraph(int32_t id, struct graph *gra);
extern int nodeLinkVertex(struct graph *gra, struct graphNode *vs, struct graphNode *ve);
extern int idenLinkVertex(struct graph *gra, int32_t ids, int32_t ide);

extern void prGraph(struct graph *gra);

#endif
