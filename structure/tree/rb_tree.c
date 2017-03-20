#include <string.h>
#include <malloc.h>

#include <saprint.h>
#include <types.h>
#include <tree.h>
#include <search_tree.h>
#include <rb_tree.h>

static struct treeNode *X, *P, *GP, *GGP;

struct rbTree *allocRbTreeNode(int element)
{
        struct rbTree *rb = NULL;
        rb = malloc(sizeof(struct rbTree));
        if (rb == NULL) {
            ERROR("read-black-tree alloc memory fail \n");
            return NULL;
        }
        rb->tn.element = element;
        rb->tn.left = rb->tn.right = NULL;
        rb->colour = RB_BLACK;
        return rb;
}

void freeRbTreeNode(struct rbTree *rb)
{
    free(rb);
    rb = NULL;
}

struct rbTree *buildRbTree(int *elements, uint num)
{
    struct rbTree *root;
    root = allocRbTreeNode(elements[0]);
    if (root == NULL)
        return NULL;
    uint32_t i;
    for (i = 1;i < num; i++) {
        root = insertRbTree(elements[i], root);
    }
    return root;
}

void freeRbTree(struct rbTree *rb)
{
    if (rb != NULL) {
        struct treeNodeList *headCur, *headNext, *head0, *head1, *pos;
        struct treeNode *tn;
        struct rbTree *rbCur;
        head0 = allocTnl();
        head1 = allocTnl();
        if ((head0 == NULL)||(head1 == NULL)) {
            goto out;
        }

        listAddTnl(&(rb->tn), head0);
        headCur = head0;
        char flag = 0;
        while (headCur->next != headCur) {
            if (flag == 0) {
                headNext = head1;
                flag = 1;
            } else {
                headNext = head0;
                flag = 0;
            }

            freeTnlList(headNext);
            list_for_each_tree(pos, headCur) {
                tn = pos->tn;
                if (tn->left != NULL) {
                    listAddTnl(tn->left, headNext);
                }
                if (tn->right != NULL) {
                    listAddTnl(tn->right, headNext);
                }
                rbCur = toRbTree(tn);
                freeRbTreeNode(rbCur);
            }
            headCur = headNext;
        }

out:
        freeTnl(head0);
        freeTnl(head1);
    }
    return;
}

static struct treeNode *rotate(int element, struct treeNode *parent)
{
    if (element < parent->element) {
        if (element < parent->left->element) {
            /*        GP               P
             *       /  \             /  \
             *     (P)   A  ---->    X   (GP)
             *     / \                   /  \
             *   (X)  B                 B    A
             */
            parent->left = singleRotateWithLeft(parent->left);
        } else {
            /*        P              X
             *       / \            /  \
             *      A   X   ---->  P    C
             *         / \        / \
             *        B   C      A   B
             */
            parent->left = singleRotateWithRight(parent->left);
        }
        return parent->left;
    } else {
        if (element < parent->right->element) {
            parent->right = singleRotateWithLeft(parent->right);
        } else {
            parent->right = singleRotateWithRight(parent->right);
        }
        return parent->right;
    }
}

static struct treeNode *handleReorient(int element, struct treeNode *root)
{
    struct rbTree *rbX, *rbP, *rbGP, *rbRoot;
    rbX = toRbTree(X);
    rbP = toRbTree(P);
    rbGP = toRbTree(GP);
    rbRoot = toRbTree(root);
    if (X != P) //consider root node (X = P)
        rbX->colour = RB_RED;
    //child colour already set done without this function
    if (rbP->colour == RB_RED) {
        rbGP->colour = RB_RED;
        if (GGP != GP) {
            if ((element < GP->element) != (element < P->element)) {
                P = rotate(element, GP);
            }
            X = rotate(element, GGP);
        } else {
            if ((element < GP->element) && (element < P->element)) {
                X = singleRotateWithLeft(GP);
            } else if ((element > GP->element) && (element > P->element)) {
                X = singleRotateWithRight(GP);
            } else if ((element < GP->element) && (element > P->element)) {
                X = doubleRotateWithLeft(GP);
            } else {
                X = doubleRotateWithRight(GP);
            }
            root = X;
            rbRoot = toRbTree(root);
        }
        rbX = toRbTree(X);
        rbX->colour = RB_BLACK;
    }

    rbRoot->colour = RB_BLACK;
    return root;
}

struct rbTree *insertRbTree(int element, struct rbTree *root)
{
    struct rbTree *left, *right, *new;

    new = allocRbTreeNode(element);
    if (new == NULL)
        return NULL;

    if (root == NULL) {
        X = P = GP = GGP = NULL;
        return new;
    } else {
        X = P = GP = GGP = &(root->tn);
    }

    while (X != NULL) {
        left = toRbTree(X->left);
        right = toRbTree(X->right);
        if ((left != NULL && left->colour == RB_RED) && (right != NULL && right->colour == RB_RED)) {
            left->colour = RB_BLACK;
            right->colour = RB_BLACK;
            root = handleReorient(element, root);
        }

        GGP = GP; GP = P; P = X;
        if (element < X->element) {
            X = X->left;
        } else {
            X = X->right;
        }
    }

    new->colour = RB_RED;
    if (element < P->element) {
        P->left = &(new->tn);
        X = P->left;
    } else {
        P->right = &(new->tn);
        X = P->right;
    }
    root = handleReorient(element, root);

    return root;
}

static bool childAllRed(struct rbTree *rb)
{
    struct rbTree *left, *right;
    if (rb != NULL) {
        left = toRbTree(rb->tn.left);
        right = toRbTree(rb->tn.right);
        if ((left != NULL && left->colour == RB_RED) && (right != NULL && right->colour == RB_RED)) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

static bool childAllBlack(struct rbTree *rb)
{
    struct rbTree *left, *right;
    if (rb != NULL) {
        left = toRbTree(rb->tn.left);
        right = toRbTree(rb->tn.right);
        if ((left == NULL || left->colour == RB_BLACK) && (right == NULL || right->colour == RB_BLACK)) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

static bool childHaveRed(struct rbTree *rb)
{
    struct rbTree *left, *right;
    if (rb != NULL) {
        left = toRbTree(rb->tn.left);
        right = toRbTree(rb->tn.right);
        if ((left != NULL && left->colour == RB_RED) || (right != NULL && right->colour == RB_RED)) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

static bool leftChildIsRed(struct rbTree *rb)
{
    if (rb == NULL)
        return false;
    struct rbTree *rbL;
    rbL = toRbTree(rb->tn.left);
    if (rbL == NULL) {
        return false;
    } else if (rbL->colour == RB_RED) {
        return true;
    } else {
        return false;
    }
}

static bool rightChildIsRed(struct rbTree *rb)
{
    if (rb == NULL)
        return false;
    struct rbTree *rbR;
    rbR = toRbTree(rb->tn.right);
    if (rbR == NULL) {
        return false;
    } else if (rbR->colour == RB_RED) {
        return true;
    } else {
        return false;
    }
}

static bool nodeIsRed(struct rbTree *rb)
{
    if (rb != NULL) {
        if (rb->colour == RB_RED) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

/* return next red node */
static struct treeNode *handleRotate(int *element, struct treeNode **vcur, struct treeNode *parent)
{
    struct treeNode *next, *rnext, *sibling, *cur, *ncur;
    struct rbTree *rbC, *rbN, *rbS, *rbNC, *rbT;
    cur = *vcur;
    rbC = toRbTree(cur);
    if (*element < cur->element) {
        /*       (cur)
         *       /   \
         *    next   sibling
         */
        next = cur->left;
        rnext = next;
        sibling = cur->right;
        rbN = toRbTree(next);
        rbS = toRbTree(sibling);
        if (next == NULL) {
            next == NULL;
        } else if (childHaveRed(rbN)) {
            //1.next have red child node
            if (*element < next->element) {
                ncur = next->left;
                rbNC = toRbTree(ncur);
                if (rbNC == NULL || rbNC->colour == RB_BLACK) {
                    /*        next                   r
                     *       /    \                /   \
                     *    ncur    (r)  ---->   (next)  b2
                     *           /   \         /   \
                     *          b1   b2      ncur  b1
                     */
                    cur->left = singleRotateWithRight(next);
                    rbN->colour = RB_RED;
                    rbT = toRbTree(cur->left);
                    rbT->colour = RB_BLACK;
                    *vcur = cur->left;
                } else {
                    /*        next
                     *       /    \
                     *   (ncur)   'x'  ---->   next -> ncur
                     *   /   \
                     *  b1   b2
                     */
                     *vcur = next;
                     rnext = ncur;
                }
            } else {
                ncur = next->right;
                rbNC = toRbTree(ncur);
                if (rbNC == NULL || rbNC->colour == RB_BLACK) {
                    /*        next                   r
                     *       /    \                /   \
                     *      (r)   ncur  ---->     b1  (next)
                     *     /   \                      /   \
                     *    b1   b2                    b2   ncur
                     */
                    cur->left = singleRotateWithLeft(next);
                    rbN->colour = RB_RED;
                    rbT = toRbTree(cur->left);
                    rbT->colour = RB_BLACK;
                    *vcur = cur->left;
                } else {
                    /*        next     element ? next->element
                     *       /    \         |--==-->  change element
                     *      'x'  (ncur)  ---|
                     *           /   \      |--!=-->  next-->ncur
                     *          b1   b2
                     */
                     if (*element == next->element) {
                         *element = vminSearchTree(ncur);
                         next->element = *element;
                     }
                     *vcur = next;
                     rnext = ncur;
                }
            }
        } else {
            //2.next node do not have red child node
            if (childHaveRed(rbS)) {
                if (rightChildIsRed(rbS)) {
                    /*         (cur)                    (sibling)
                     *        /    \                     /     \
                     *     next   sibling   ---->      cur     r
                     *    /   \    /    \             /   \     \
                     *   b     b  X     (r)       (next)   X     b
                     *                    \       /   \
                     *                    b      b     b
                     */
                     rbT = toRbTree(sibling->right);
                     if (*element < parent->element) {
                         parent->left = singleRotateWithRight(cur);
                     } else {
                         parent->right = singleRotateWithRight(cur);
                     }
                     rbC->colour = RB_BLACK;
                     rbS->colour = RB_RED;
                     rbN->colour = RB_RED;
                     rbT->colour = RB_BLACK;
                } else {
                    /*         (cur)                       (l)
                     *        /    \                      /   \
                     *     next   sibling   ---->      cur    sibling
                     *    /   \    /    \             /   \     /   \
                     *   b    b  (l)     X       (next)   b1   b2   X
                     *           / \              /   \
                     *          b1 b2            b     b
                     */
                     if (*element < parent->element) {
                         parent->left = doubleRotateWithRight(cur);
                     } else {
                         parent->right = doubleRotateWithRight(cur);
                     }
                     rbC->colour = RB_BLACK;
                     rbN->colour = RB_RED;
                }
            } else {
                /*        (cur)                        cur
                 *       /    \                      /    \
                 *     next  'sibling'  ---->   (next)   ('sibling')
                 *    /    \                    /    \
                 *   b      b                  b      b
                 */
                 if (rbS != NULL)
                    rbS->colour = RB_RED;
                 rbC->colour = RB_BLACK;
                 rbN->colour = RB_RED;
            }
        }
    } else {
        /*       (cur)
         *       /   \
         *  sibling  next
         */
        next = cur->right;
        rnext = next;
        sibling = cur->left;
        rbN = toRbTree(next);
        rbS = toRbTree(sibling);

        if (next != NULL) {
            if (*element == cur->element) {
                *element = vminSearchTree(next);
                cur->element = *element;
            }
            if (childHaveRed(rbN)) {
                //1.next have red child node
                if (*element < next->element) {
                    ncur = next->left;
                    rbNC = toRbTree(ncur);
                    if (rbNC == NULL || rbNC->colour == RB_BLACK) {
                        /*        next                   r
                         *       /    \                /   \
                         *    ncur    (r)  ---->   (next)  b2
                         *           /   \         /   \
                         *          b1   b2      ncur  b1
                         */
                        cur->right = singleRotateWithRight(next);
                        rbN->colour = RB_RED;
                        rbT = toRbTree(cur->right);
                        rbT->colour = RB_BLACK;
                        *vcur = cur->right;
                    } else {
                        /*        next
                         *       /    \
                         *   (ncur)   'x'  ---->   next -> ncur
                         *   /   \
                         *  b1   b2
                         */
                         *vcur = next;
                         rnext = ncur;
                    }
                } else {
                    ncur = next->right;
                    rbNC = toRbTree(ncur);
                    if (rbNC == NULL || rbNC->colour == RB_BLACK) {
                        /*        next                   r
                         *       /    \                /   \
                         *      (r)   ncur  ---->     b1  (next)
                         *     /   \                      /   \
                         *    b1   b2                    b2   ncur
                         */
                        cur->right = singleRotateWithLeft(next);
                        rbN->colour = RB_RED;
                        rbT = toRbTree(cur->right);
                        rbT->colour = RB_BLACK;
                        *vcur = cur->right;
                    } else {
                        /*        next     element ? next->element
                         *       /    \         |--==-->  change element
                         *      'x'  (ncur)  ---|
                         *           /   \      |--!=-->  next-->ncur
                         *          b1   b2
                         */
                         if (*element == next->element) {
                             *element = vminSearchTree(ncur);
                             next->element = *element;
                         }
                         *vcur = next;
                         rnext = ncur;
                    }
                }
            } else {
                //2.next node do not have red child node
                if (childHaveRed(rbS)) {
                    if (leftChildIsRed(rbS)) {
                        /*          (cur)                  (sibling)
                         *         /     \                 /     \
                         *    sibling    next    ---->    l      cur
                         *    /    \    /   \            /      /  \
                         *  (l)    x   b     b          b      x  (next)
                         *  /                                     /   \
                         * b                                     b     b
                         */
                         rbT = toRbTree(sibling->left);
                         if (*element < parent->element) {
                             parent->left = singleRotateWithLeft(cur);
                         } else {
                             parent->right = singleRotateWithLeft(cur);
                         }
                         rbC->colour = RB_BLACK;
                         rbS->colour = RB_RED;
                         rbN->colour = RB_RED;
                         rbT->colour = RB_BLACK;
                    } else {
                        /*         (cur)                        (l)
                         *        /     \                      /   \
                         *   sibling    next   ---->    sibling    cur
                         *   /    \    /   \            /   \     /   \
                         *  x     (l) b    b           x    b1   b2   (next)
                         *        / \                                 /   \
                         *       b1 b2                               b     b
                         */
                         if (*element < parent->element) {
                             parent->left = doubleRotateWithLeft(cur);
                         } else {
                             parent->right = doubleRotateWithLeft(cur);
                         }
                         rbC->colour = RB_BLACK;
                         rbN->colour = RB_RED;
                    }
                } else {
                    /*         (cur)                         cur
                     *         /    \                      /    \
                     * 'sibling'   next   ---->   ('sibling')  (next)
                     *            /    \                      /    \
                     *           b      b                    b      b
                     */
                     if (rbS != NULL)
                        rbS->colour = RB_RED;
                     rbC->colour = RB_BLACK;
                     rbN->colour = RB_RED;
                }
            }
        } else {
            //only sibling node maybe exist
            if (*element == cur->element) {
                if (*element < parent->element) {
                    parent->left = sibling;
                } else {
                    parent->right = sibling;
                }
            }
            rnext = NULL;
        }
    }
    return rnext;
}

struct rbTree *deleteRbTree(int element, struct rbTree *rbroot)
{
    struct treeNode *parent, *cur, *next;

    if (rbroot == NULL)
        return NULL;
    struct treeNode *rroot = allocTreeNode();
    struct rbTree *root = allocRbTreeNode(INT32_MIN);
    if (root == NULL) {
        ERROR("fail delete rb-tree node \n");
        return rbroot;
    } else {
        /*         rroot
         *        /
         *    (root)
         *    /   \
         * null   rbroot
         */
        rroot->element = INT32_MAX;
        rroot->left = &(root->tn);
        root->colour = RB_RED;
        root->tn.right = &(rbroot->tn);
        parent = rroot;
        cur = &(root->tn);
    }

    while (true) {
        next = handleRotate(&element, &cur, parent);
        if (next == NULL) {
            break;
        } else {
            parent = cur;
            cur = next;
        }
    }
    if (element == cur->element) {
        free(cur);
    } else {
        ERROR("can not find element [%d] in rb-tree\n", element);
    }

    root = toRbTree(rroot->left);
    rbroot = toRbTree(root->tn.right);
    if (rbroot != NULL)
        rbroot->colour = RB_BLACK;
    free(root);
    free(rroot);
    return rbroot;
}

struct rbTree *fmaxRbTree(struct rbTree *rb)
{
    struct treeNode *tn;
    tn = fmaxSearchTree(&(rb->tn));
    return toRbTree(tn);
}

struct rbTree *fminRbTree(struct rbTree *rb)
{
    struct treeNode *tn;
    tn = fminSearchTree(&(rb->tn));
    return toRbTree(tn);
}

int vminRbTree(struct rbTree *rb)
{
    return vminSearchTree(&(rb->tn));
}

int vmaxRbTree(struct rbTree *rb)
{
    return vmaxSearchTree(&(rb->tn));
}


static void redNode(struct rbTree *rb)
{
    if (rb != NULL) {
        if (rb->colour == RB_RED)
            printf("%d ", rb->tn.element);
        struct rbTree *left, *right;
        if (rb->tn.left != NULL) {
            left = toRbTree(rb->tn.left);
            redNode(left);
        }
        if (rb->tn.right != NULL) {
            right = toRbTree(rb->tn.right);
            redNode(right);
        }
    }
    return;
}

void prRbTree(struct rbTree *rb)
{
    if (rb != NULL) {
        prBinTree(&(rb->tn));
        printf("red element : \n");
        redNode(rb);
        printf("\n");
    }
}
