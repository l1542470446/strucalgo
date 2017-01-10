#include <malloc.h>

#include <types.h>
#include <queue.h>
#include <saprint.h>
#include <tree.h>

/********************************************************
* empty : true
* not empty : false
*********************************************************/
bool emptyBinHeap(struct binHeap *pq)
{
    if (pq->size == 0)
        return true;
    else
        return false;
}

/********************************************************
* full : true
* not full : false
*********************************************************/
bool fullBinHeap(struct binHeap *pq)
{
    if (pq->size == pq->capacity)
        return true;
    else
        return false;
}

void freeBinHeap(struct binHeap *pq)
{
    if (pq->elements != NULL)
        free(pq->elements);
    if (pq != NULL)
        free(pq);
}

void zeroBinHeap(struct binHeap *pq)
{
    uint n = pq->size;
    int *data = pq->elements;
    uint i;
    for (i = 0; i < n; i++)
        data[i] = 0;
}

struct binHeap *allocBinHeap(uint num, uint type)
{
    struct binHeap *pq = NULL;
    pq = malloc(sizeof(struct binHeap));
    if (pq == NULL) {
        ERROR("priority queue malloc failure!\n");
        return NULL;
    }
    int *data = NULL;
    data = malloc((num+1) * sizeof(int));
    if (data == NULL) {
        ERROR("elements malloc failure!\n");
        free(pq);
        return NULL;
    }
    if (type == PQUEUE_MIN) {
        data[0] = INT32_MIN;
    } else if (type == PQUEUE_MAX) {
        data[0] = INT32_MAX;
    } else {
        ERROR("priority queue type arg is wrong!\n");
        free(data);
        free(pq);
        return NULL;
    }
    pq->type = type;
    pq->elements = data;
    pq->capacity = num;
    pq->size = 0;
    return pq;
}

int inserBinHeap(struct binHeap *pq, int element)
{
    if (fullBinHeap(pq)) {
        WARN("priority queue full !\n");
        return 1;
    }

    int i;
    if (pq->type == PQUEUE_MIN) {
        for (i = ++pq->size; pq->elements[i / 2] > element; i /= 2)
            pq->elements[i] = pq->elements[i / 2];
    } else if (pq->type == PQUEUE_MAX) {
        for (i = ++pq->size; pq->elements[i / 2] < element; i /= 2)
            pq->elements[i] = pq->elements[i / 2];
    } else {
        ERROR("priority queue type unknown!\n");
        return 1;
    }
    pq->elements[i] = element;
}

/********************************************************
* data array -> a[0] a[1] ...
*                 |    |
*          index :1    2  ...
*********************************************************/
int percolateDown(struct binHeap *pq, uint index)
{
    uint child, i, n;
    int tmp;
    int *data = NULL;
    data = pq->elements;
    n = pq->size;

    if ((index > n) || (index == 0)) {
        WARN("data index overflow\n");
        return 1;
    }

    if (pq->type == PQUEUE_MIN) {
        for (tmp = data[index], i = index; LCHILD(i) < n; i = child) {
            child = LCHILD(i);
            if ((child < n) && (data[child+1] < data[child]))
                child++;
            if (data[child] < tmp)
                data[i] = data[child];
            else
                break;
        }
        data[i] = tmp;
    } else if (pq->type == PQUEUE_MAX) {
        for (tmp = data[index], i = index; LCHILD(i) < n; i = child) {
            child = LCHILD(i);
            if ((child < n) && (data[child+1] > data[child]))
                child++;
            if (data[child] > tmp)
                data[i] = data[child];
            else
                break;
        }
        data[i] = tmp;
    }
    return 0;
}

int deleteBinHeap(struct binHeap *pq, uint index)
{
    int ret = 0;
    if (emptyBinHeap(pq)) {
        WARN("priority queue is empty\n");
        return 1;
    }

    int *data = NULL;
    data = pq->elements;
    data[index] = data[pq->size];
    data[pq->size] = 0;
    pq->size--;
    ret = percolateDown(pq, index);
    return ret;
}

/********************************************/
/*                  left-heap               */
/********************************************/

struct leftHeap *allocLeftHeap()
{
    struct leftHeap *lh = NULL;
    lh = malloc(sizeof(struct leftHeap));
    if (lh == NULL) {
        ERROR("left heap alloc fail!\n");
        return lh;
    }
    lh->tn.left = lh->tn.right = NULL;
    lh->npl = 0;
    return lh;
}

static void swapChildLeft(struct leftHeap *lh)
{
    struct treeNode *tmp = NULL;
    tmp = lh->tn.right;
    lh->tn.right = lh->tn.left;
    lh->tn.left = tmp;
}

static struct leftHeap *__mergeLeftHeap(struct leftHeap *lh1, struct leftHeap *lh2)
{
    struct leftHeap *right = NULL, *left = NULL;
    struct leftHeap *tmp = NULL;
    if (lh1->tn.left == NULL) {
        lh1->tn.left = &(lh2->tn);
    } else {
        right = toLeftHeap(lh1->tn.right);
        tmp = mergeLeftHeap(right, lh2);
        lh1->tn.right = &(tmp->tn);
        right = tmp;
        left = toLeftHeap(lh1->tn.left);
        if (left->npl < right->npl)
            swapChildLeft(lh1);//swap
        right = toLeftHeap(lh1->tn.right);
        lh1->npl = right->npl + 1;
    }
    return lh1;
}

struct leftHeap *mergeLeftHeap(struct leftHeap *lh1, struct leftHeap *lh2)
{
    if (lh1 == NULL)
        return lh2;
    if (lh2 == NULL)
        return lh1;
    if (lh1->tn.element < lh2->tn.element)
        return __mergeLeftHeap(lh1, lh2);
    else
        return __mergeLeftHeap(lh2, lh1);
}

struct leftHeap *inserLeftHeap(int data, struct leftHeap *lh)
{
    struct leftHeap *new = NULL;
    new = allocLeftHeap();
    if (new == NULL)
        return new;
    new->tn.element = data;
    return mergeLeftHeap(new, lh);
}

void prLeftHeap(struct leftHeap *lh)
{
    struct treeNode *tr = NULL;
    tr = &lh->tn;
    //calculate max layer num
	uint layermax = layerBinTree(tr);
	//calculate max value and max bit
	uint absoMax = findAbLeftHeap(lh);
	uchar bit = uDataBit(absoMax);
	uint i, j;
	struct treeNodeList *curnlist = NULL;
	struct treeNodeList *nextlist = NULL;
	curnlist = allocTnl();
	listAddTnlTail(tr, curnlist);
	for (i = 0; i < layermax; i++) {
		nextlist = __prBinTree(curnlist, i, layermax, bit);
		curnlist = nextlist;
	}
	freeTnlList(curnlist);
}

uint findAbLeftHeap(struct leftHeap *lh)
{
    int max, min;
    uint abso = 0;
    struct treeNode *tr = NULL;
    tr = &lh->tn;
    max = maxBinTree(tr);
    min = lh->tn.element;
    if (max <= 0) {
        abso = (uint)(0 - min);
    } else if (min >= 0){
        abso = max;
    } else {
        abso = 0 - min;
        if (abso < max)
            abso = max;
    }
    return abso;
}

void freeLeftHeap(struct leftHeap *lh)
{
    free(lh);
    lh = NULL;
}

struct leftHeap *delMinLeftHeap(struct leftHeap *lh)
{
    if (lh == NULL)
        return NULL;
    struct leftHeap *leftLh, *righLh, *merLh;
    leftLh = toLeftHeap(lh->tn.left);
    righLh = toLeftHeap(lh->tn.right);
    merLh = mergeLeftHeap(leftLh, righLh);
    freeLeftHeap(lh);
    return merLh;
}
