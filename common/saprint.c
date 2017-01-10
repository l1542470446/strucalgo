#include <stdio.h>
#include <math.h>

#include <types.h>
#include <saprint.h>
#include <tree.h>

void saprint(struct dataArray *sa)
{
	unsigned int i=0;
	for(i=0;i<sa->nr;i++)
		printf("%d ",sa->data[i]);
	printf("\n");
}

/**************************************************************************************
*				|i++,layer=5	layerBit=	layerSpa=		layer_num=
*0123456789ABCDEF		|i < layer	2^(layer-i)	2^(layer-1-i)-1	2^i
*               1		|0		32		15			1
*       2               3	|1		16		7			2
*   4       5       6       7	|2		8		3			4
* 8   9   A   A   A   A   A   A	|3		4		1			8
*B B B B B B B B		|4		2		0			16
**************************************************************************************/
void prArrBinTree(int *array,uint num)
{
	//calculate bin-tree layer
	uint layer = layerBinHeap(num);
	//printf("layer = %d\n", layer);
	//calculate max value bit
	uint absoMax = findMaxAbsoVal(array, num);
	uchar bit = uDataBit(absoMax);
	//printf("absoMax = %d,bit = %d\n", absoMax, bit);
	//show tree
	uint i, j, aryn = 0;
	uint layerNum, layerSpa, layerBit;
	for (i = 0; i < layer; i++) {
		layerNum = pow(2,i);
		layerSpa = pow(2, layer - 1 - i) - 1;
		layerSpa = layerSpa * bit;
		layerBit = pow(2, layer - i);
		layerBit = layerBit * bit;
		printf("%-*s", layerSpa, "");
		for (j = 0; j < layerNum; j++) {
			printf("%-*d", layerBit, array[aryn++]);
			if (aryn >= num)
				break;
		}
		printf("\n");
	}
}

struct treeNodeList *__prBinTree(struct treeNodeList *head, uint layer, uint layerMax, uchar bit)
{
	if (head->next == head)
		return;
	uint layerNum, layerSpa, layerBit;
	layerNum = pow(2,layer);
	layerSpa = pow(2, layerMax - 1 - layer) - 1;
	layerSpa = layerSpa * bit;
	layerBit = pow(2, layerMax - layer);
	layerBit = layerBit * bit;
	printf("%-*s", layerSpa, "");

	struct treeNodeList *tmp;
	struct treeNodeList *next;
	struct treeNode *tntmp;

	next = allocTnl();

	for (tmp = head->next; tmp != head; tmp = tmp->next) {
		tntmp = tmp->tn;
		if (tmp->type == TN_FULL) {
			printf("%-*d", layerBit, tntmp->element);
		} else if (tmp->type == TN_NULL) {
			printf("%-*s", layerBit, " ");
		}
		listAddTnlTail(tntmp->left, next);
		listAddTnlTail(tntmp->right, next);
	}
	printf("\n");
	freeTnlList(head);
	checkTnlList(next);
	return next;
}

void prSimpBinTree(struct treeNode *head)
{
	//TODO:layerBinTree()
	uint layermax = 5;
	//calculate max value bit,TODO:findAbMaxBTree
	uint absoMax = 99;
	uchar bit = uDataBit(absoMax);
	uint i, j;
	struct treeNodeList *curnlist = NULL;
	struct treeNodeList *nextlist = NULL;
	curnlist = allocTnl();
	listAddTnlTail(head, curnlist);
	for (i = 0; i < layermax; i++) {
		nextlist = __prBinTree(curnlist, i, layermax, bit);
		curnlist = nextlist;
	}
	freeTnlList(curnlist);
}
