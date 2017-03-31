#include <string.h>
#include <malloc.h>

#include <tree.h>
#include <types.h>
#include <saprint.h>
#include <aa_tree.h>

struct aaTree *allocAaTreeNode(int32_t element)
{
    struct aaTree *at = NULL;
    at = malloc(sizeof(struct aaTree));
    if (at == NULL) {
        ERROR("alloc memory fail for aa-tree\n");
        return NULL;
    }
    at->tn.element = element;
    at->level = 1;
    at->tn.left = at->tn.right = NULL;
    return at;
}

void freeAaTreeNode(struct aaTree *at)
{
    free(at);
}

/*        X <-- P                X --> P
 *      /  \     \    ---->     /     / \
 *     A    B     C            A     B   C
 */

static struct aaTree *skew(struct aaTree *atP)
{
    if (atP == NULL)
        return atP;
    struct aaTree *atX;
    atX = toAaTree(atP->tn.left);// X -> atX -> atLeft
    if (atX == NULL) {
        return atP;
    }
    if (atX->level == atP->level) {
        struct treeNode *tmp;
        tmp = singleRotateWithLeft(&(atP->tn));
        return toAaTree(tmp);
    } else {
        return atP;
    }
}

/*     P --> X --> T                   X
 *    /     /     / \    ---->       /  \
 *   A     C     D   E              P    T
 *                                 / \  / \
 *                                A  C D  E
 */
static struct aaTree *split(struct aaTree *atP)
{
    if (atP == NULL)
        return atP;
    struct aaTree *atX, *atT, *atR;
    struct treeNode *tmp;
    atR = atP;
    atX = toAaTree(atP->tn.right);
    if (atX != NULL) {
        atT = toAaTree(atX->tn.right);
        if (atT != NULL && atT->level == atP->level) {
            tmp = singleRotateWithRight(&(atP->tn));
            atR = toAaTree(tmp);
            atR->level++;
        }
    }
    return atR;
}

struct aaTree *insertAaTree(int32_t element, struct aaTree *at)
{
    struct aaTree *atLeft, *atRight;
    if (at == NULL) {
        struct aaTree *atNew = allocAaTreeNode(element);
        return atNew;
    } else if (element < at->tn.element) {
        atLeft = toAaTree(at->tn.left);
        atLeft = insertAaTree(element, atLeft);
        at->tn.left = &(atLeft->tn);
    } else if (element > at->tn.element) {
        atRight = toAaTree(at->tn.right);
        atRight = insertAaTree(element, atRight);
        at->tn.right = &(atRight->tn);
    }
    at = skew(at);
    at = split(at);
    return at;
}

struct aaTree *deleteAaTree(int32_t element, struct aaTree *at)
{
    static struct aaTree *deletePtr = NULL, *lastPtr = NULL;
    struct aaTree *tmp, *atLeft, *atRight;
    if (at != NULL) {
        /* step 1 : search down tree */
        lastPtr = at;
        if (element < at->tn.element) {
            tmp = toAaTree(at->tn.left);
            tmp = deleteAaTree(element, tmp);
            at->tn.left = &(tmp->tn);
        } else {
            deletePtr = at;
            tmp = toAaTree(at->tn.right);
            tmp = deleteAaTree(element, tmp);
            at->tn.right = &(tmp->tn);
        }
        /* step 2 : at the bottom , remove element */
        if (at == lastPtr) {
            if (deletePtr != NULL && element == deletePtr->tn.element) {
                deletePtr->tn.element = at->tn.element;
                deletePtr = NULL;
                at = toAaTree(at->tn.right);
                free(lastPtr);
            } else {
                WARN("can not find element %d\n", element);
            }
        } else {
        /* step 3 : reblance tree */
            atLeft = toAaTree(at->tn.left);
            atRight = toAaTree(at->tn.right);
            if (atLeft == NULL && atRight == NULL) {
                at->level = 1;
            } else if (atLeft == NULL) {
                at->level = 1;
                atRight->level = 1;
                at = split(at);
            } else if (atRight == NULL) {
                at->level = 1;
                at = skew(at);
            } else {
                if (atLeft->level < at->level - 1 || atRight->level < at->level - 1) {
                    if (atRight->level > --(at->level))
                        atRight->level = at->level;
                    at = skew(at);
                    atRight = skew(atRight);
                    at->tn.right = &(atRight->tn);
                    tmp = toAaTree(atRight->tn.right);
                    tmp = skew(tmp);
                    atRight->tn.right = &(tmp->tn);
                    at = split(at);
                    tmp = toAaTree(at->tn.right);
                    tmp = split(tmp);
                    at->tn.right = &(tmp->tn);
                }
            }
        }
    }
    return at;
}

struct aaTree *buildAaTree(int32_t *elements, uint32_t num)
{
    struct aaTree *at;
    uint32_t i;
    for (i = 0; i < num; i++) {
        at = insertAaTree(elements[i], at);
    }
    return at;
}

void freeAaTree(struct aaTree *at)
{
    struct aaTree *atLeft, *atRight;
    if (at == NULL) {
        return;
    } else {
        atLeft = toAaTree(at->tn.left);
        atRight = toAaTree(at->tn.right);
    }
    freeAaTree(atLeft);
    freeAaTree(atRight);
    free(at);
}

struct aaTree *fminAaTree(struct aaTree *at)
{
    struct treeNode *tn = fminSearchTree(&(at->tn));
    return toAaTree(tn);
}
struct aaTree *fmaxAaTree(struct aaTree *at)
{
    struct treeNode *tn = fmaxSearchTree(&(at->tn));
    return toAaTree(tn);
}

int vminAaTree(struct aaTree *at)
{
    struct aaTree *tmp = fminAaTree(at);
    return tmp->tn.element;
}

int vmaxAaTree(struct aaTree *at)
{
    struct aaTree *tmp = fmaxAaTree(at);
    return tmp->tn.element;
}

static void prAaTreeRed(struct aaTree *at)
{
    struct aaTree *atLeft, *atRight;
    if (at == NULL)
        return;
    atLeft = toAaTree(at->tn.left);
    atRight = toAaTree(at->tn.right);
    if (atLeft != NULL) {
        if (at->level == atLeft->level)
            printf("%d ", atLeft->tn.element);
        prAaTreeRed(atLeft);
    }
    if (atRight != NULL) {
        if (at->level == atRight->level)
            printf("%d ", atRight->tn.element);
        prAaTreeRed(atRight);
    }
}

void prAaTree(struct aaTree *at)
{
    //print tree
    prBinTree(&(at->tn));
    //print same level
    printf("red element : ");
    prAaTreeRed(at);
    printf("\n");
}
