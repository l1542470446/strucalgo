#include <malloc.h>
#include <math.h>

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
        return lh;
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

static uint abMaxTreeHeap(struct treeNode *tr)
{
    int max, min;
    uint abso = 0;
    max = maxBinTree(tr);
    min = tr->element;
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

uint findAbLeftHeap(struct leftHeap *lh)
{
    struct treeNode *tr = NULL;
    tr = &lh->tn;
    return abMaxTreeHeap(tr);
}

void freeLeftHeap(struct leftHeap *lh)
{
    free(lh);
    lh = NULL;
}

void freeLeftHeaps(struct leftHeap *lh)
{
    struct leftHeap *leftLh, *righLh;
    if (lh->tn.left != NULL) {
        leftLh = toLeftHeap(lh->tn.left);
        freeLeftHeaps(leftLh);
    }
    if (lh->tn.right != NULL) {
        righLh = toLeftHeap(lh->tn.right);
        freeLeftHeaps(righLh);
    }
    freeLeftHeap(lh);
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

/********************************************/
/*                  skew-heap               */
/********************************************/

struct skewHeap *allocSkewHeap()
{
    struct skewHeap *sh = NULL;
    sh = malloc(sizeof(struct skewHeap));
    if (sh == NULL) {
        ERROR("skew heap alloc fail!\n");
        return sh;
    }
    sh->tn.left = sh->tn.right = NULL;
    return sh;
}

void freeSkewHeap(struct skewHeap *sh)
{
    free(sh);
    sh = NULL;
}

static void swapChileSkew(struct skewHeap *sh)
{
    struct treeNode *tmp = NULL;
    tmp = sh->tn.right;
    sh->tn.right = sh->tn.left;
    sh->tn.left = tmp;
}

static struct skewHeap *__mergeSkewHeap(struct skewHeap *sh1, struct skewHeap *sh2)
{
    if (sh1->tn.left == NULL) {
        sh1->tn.left = &(sh2->tn);
    } else {
        struct skewHeap *tmp, *right;
        tmp = toSkewHeap(sh1->tn.right);
        right = mergeSkewHeap(tmp, sh2);
        sh1->tn.right = &(right->tn);
        swapChileSkew(sh1);
    }
    return sh1;
}

struct skewHeap *mergeSkewHeap(struct skewHeap *sh1, struct skewHeap *sh2)
{
    if (sh1 == NULL)
        return sh2;
    if (sh2 == NULL)
        return sh1;
    if (sh1->tn.element < sh2->tn.element)
        return __mergeSkewHeap(sh1, sh2);
    else
        return __mergeSkewHeap(sh2, sh1);
}

struct skewHeap *insertSkewHeap(int data, struct skewHeap *sh)
{
    struct skewHeap *new = NULL;
    new = allocSkewHeap();
    if (new == NULL)
        return sh;
    new->tn.element = data;
    return mergeSkewHeap(new, sh);
}

void prSkewHeap(struct skewHeap *sh)
{
    struct treeNode *tr = NULL;
    tr = &(sh->tn);
    //calculate max layer num
	uint layermax = layerBinTree(tr);
	//calculate max value and max bit
	uint absoMax = abMaxTreeHeap(tr);
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

struct skewHeap *delMinSkewHeap(struct skewHeap *sh)
{
    if (sh == NULL)
        return NULL;
    struct skewHeap *leftSh, *righSh, *merSh;
    leftSh = toSkewHeap(sh->tn.left);
    righSh = toSkewHeap(sh->tn.right);
    merSh = mergeSkewHeap(leftSh, righSh);
    freeSkewHeap(sh);
    return merSh;
}

void freeSkewHeaps(struct skewHeap *sh)
{
    struct skewHeap *leftSh, *righSh;
    if (sh->tn.left != NULL) {
        leftSh = toSkewHeap(sh->tn.left);
        freeSkewHeaps(leftSh);
    }
    if (sh->tn.right != NULL) {
        righSh = toSkewHeap(sh->tn.right);
        freeSkewHeaps(righSh);
    }
    freeSkewHeap(sh);
}

/********************************************/
/*            binomial queue                */
/********************************************/

struct binoQueue *allocBinoQueue()
{
    struct binoQueue *bq = NULL;
    bq = malloc(sizeof(struct binoQueue));
    if (bq == NULL) {
        ERROR("binomial queue alloc fail !\n");
        return bq;
    }
    bq->child = bq->sibling = NULL;
    return bq;
}

static struct binoTree *allocBinoTree()
{
    struct binoTree *bt = NULL;
    bt = malloc(sizeof(struct binoTree));
    if (bt == NULL) {
        //ERROR("");
        return NULL;
    }
    bt->next = NULL;
    bt->bq = NULL;
    return bt;
}

static void freeBinoTrees(struct binoTree *bt)
{
    struct binoTree *cur, *tmp, *next;
    for (cur = bt; cur != NULL; cur = next) {
        next = cur->next;
        tmp = cur;
        free(tmp);
        tmp = NULL;
    }
}

static struct binoTree *allocBinoTrees(uint n)
{
    struct binoTree *bt_root, *ptmp, *ntmp;
    bt_root = ptmp = ntmp = NULL;
    //1. alloc bt_root
    bt_root = allocBinoTree();
    if (bt_root == NULL) {
        goto fail;
    }
    //2. alloc trees
    uint i;
    ptmp = bt_root;
    for (i = 1; i < n; i++) {
        ntmp = allocBinoTree();
        if (ntmp == NULL) {
            freeBinoTrees(bt_root);
            goto fail;
        }
        ptmp->next = ntmp;
        ptmp = ntmp;
        ntmp = NULL;
    }
    return bt_root;
fail:
    ERROR("binomial forest alloc tree fail !\n");
    return NULL;
}

struct binoForest *allocBinoForest(uint cap)
{
    uint i, tmp_n = 0;
    struct binoForest *bf = NULL;
    struct binoTree *bt_root;
    bf = malloc(sizeof(struct binoForest));
    tmp_n = log2(cap)+1;
    bt_root = allocBinoTrees(tmp_n);
    if ((bf == NULL) || (bt_root == NULL)) {
        ERROR("binomial queue forest alloc fail !\n");
        free(bf);
        free(bt_root);
        return NULL;
    }

    bf->cap = cap;
    bf->size = 0;
    bf->bt = bt_root;
    return bf;
}

void freeBinoForest(struct binoForest *bf)
{
    freeBinoTrees(bf->bt);
    free(bf);
    bf = NULL;
}

struct binoQueue *merBinoQueue(struct binoQueue *bq1, struct binoQueue *bq2)
{
    if (bq1->element > bq2->element) {
        return merBinoQueue(bq2, bq1);
    }
    bq2->sibling = bq1->child;
    bq1->child = bq2;
    return bq1;
}

struct binoForest *merBinoForest(struct binoForest *bf1, struct binoForest *bf2)
{
    if (bf1->cap > bf2->cap) {
        return merBinoForest(bf2, bf1);
    }

    uint j, capacity;
    struct binoQueue *carry, *tmp;
    struct binoTree *bt1, *bt2;

    capacity = bf1->size + bf2->size;
    if (capacity > bf2->cap) {
        //TODO:expand forest
        ERROR("binomial forest overflow !\n");
        return NULL;
    }

    carry = NULL;
    bt1 = bf1->bt;
    bt2 = bf2->bt;
    for (j = 1; j <= bf2->cap; j *= 2) {
        if ((j > bf1->size) && (carry == NULL)) {
            break;
        }
        // 1 + 2 + 4
        switch (1*(!!(bt1 ? bt1->bq : 0)) + 2*(!!(bt2->bq)) + 4*(!!carry)) {
            case 0:
            case 2:
                break;
            case 1:
                bt2->bq = bt1->bq;
                bt1->bq = NULL;
                break;
            case 3:
                carry = merBinoQueue(bt1->bq, bt2->bq);
                bt1->bq = bt2->bq = NULL;
                break;
            case 4:
                bt2->bq = carry;
                carry = NULL;
                break;
            case 5:
                tmp = carry;
                carry = merBinoQueue(bt1->bq, tmp);
                bt1->bq = NULL;
                break;
            case 6:
                tmp = carry;
                carry = merBinoQueue(bt2->bq, tmp);
                bt2->bq = NULL;
                break;
            case 7:
                tmp = bt2->bq;
                bt2->bq = carry;
                carry = merBinoQueue(bt1->bq, tmp);
                bt1->bq = NULL;
                break;
        }
        bt2 = bt2->next;
        if (bt1 != NULL)
            bt1 = bt1->next;
    }
    freeBinoForest(bf1);
    bf2->size = capacity;
    return bf2;
}

struct binoForest *addBinoForest(struct binoQueue *bq, struct binoForest *bf)
{
    struct binoForest *tbf = NULL;
    tbf = allocBinoForest(1);
    if (tbf == NULL) {
        return NULL;
    }
    tbf->bt->bq = bq;
    tbf->size = 1;
    return merBinoForest(tbf, bf);
}

static void __prBinoQueue(struct binoQueue *bq, uint space, const uint bit)
{
    if (bq == NULL) {
        printf("NULL\n");
        return;
    }
    if (bq->child == NULL) {
        printf("%-*s", space, "");
        printf("%-*d\n", bit, bq->element);
        return;
    }
    struct binoQueue *sib;
    uint ns = space + bit + SPACE_BQ;
    for (sib = bq->child; sib->sibling != NULL; sib = sib->sibling) {
        __prBinoQueue(sib, ns, bit);
    }
    printf("%-*s", space, "");
    printf("%-*d", bit, bq->element);
    printf("%-*s", SPACE_BQ, "");
    printf("%-*d\n", bit, sib->element);
}

void prBinoQueue(struct binoQueue *bq)
{
    //TODO:calculate max value bit +1(for -negetive value)
    uint bit = 3; // data bit
    //start align to 0
    __prBinoQueue(bq, 0, bit);
}

void prBinoForest(struct binoForest *bf)
{
    struct binoTree *root, *tmp;
    root = bf->bt;
    for (tmp = root; tmp != NULL; tmp = tmp->next) {
        prBinoQueue(tmp->bq);
        printf("----------------------------\n");
    }
}
