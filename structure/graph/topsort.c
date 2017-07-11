#include <string.h>
#include <malloc.h>

#include <saprint.h>
#include <graph.h>

int *seq_temp;//[0][1][2][3][4][5][6]
int *seq_sort;//[3][2][5][1][4][6]
int *zero_temp;
static uint32_t seq_pos = 0;

static void indegreeZeroInit(struct graph *gra)
{
    struct graphList *glp, *glr, *gls = gra->lnode;
    struct list_head *pos;
    uint32_t i, num = gra->num;

    for (i = 0; i < num; i++) {
        glr = gls + i;
        graph_list_for_each(pos, &(glr->list)) {
            glp = toGraphList(pos);
            (*(seq_temp + glp->gnode->iden))++;
        }
    }
    seq_temp[0] = -1;
    zero_temp[0] = 0;
    seq_pos = 0;

#if 0
    for (i = 1; i < num+1; i++)
        printf("%d ", *(seq_temp + i));
    printf("\n");
#endif

    return;
}

static void calcIndegree(struct graph *gra)
{
    struct graphList *glp, *glr, *gls = gra->lnode;
    struct list_head *pos;
    uint32_t i = 0;
    int32_t val, id;
    while (*(zero_temp + i) != 0) {
        val = *(zero_temp + i);
        *(seq_temp + val) = -1;
        *(zero_temp + i) = 0;

        glr = gls + val - 1;
        graph_list_for_each(pos, &(glr->list)) {
            glp = toGraphList(pos);
            id = glp->gnode->iden;
            (*(seq_temp + id))--;
        }

        i++;
    }
}

static int32_t findIndegreeZero(struct graph *gra)
{
    uint32_t i, j, num = gra->num;
    for (i = 0, j = 0; i < num + 1; i++) {
        if (*(seq_temp + i) == 0) {
            *(seq_sort + seq_pos++) = i;
            *(zero_temp + j++) = i;
        }
    }
    *(zero_temp + j) = 0;
}

void topSortGraph(struct graph *gra)
{
    uint32_t i, j = 0, num = gra->num;
    seq_temp = (int *)malloc((num+1) * sizeof(int));
    seq_sort = (int *)malloc(num * sizeof(int));
    zero_temp = (int *)malloc(num * sizeof(int));
    if (seq_sort == NULL || seq_temp == NULL || zero_temp == NULL) {
        ERROR("topSortGraph malloc fail \n");
        goto err_malloc;
    }
    //1.init all vertex indegree
    indegreeZeroInit(gra);

    while (seq_pos < num && j++ < num) {
        //2.find vertex of indegree zero
        //3.join sort queue
        findIndegreeZero(gra);
        //4.calculate indegree zero
        calcIndegree(gra);
    }

    for (i = 0; i < num; i++) {
        printf("%d ", *(seq_sort + i));
    }
    printf("\n");

    return;
err_malloc:
    free(seq_sort);
    free(seq_temp);
    free(zero_temp);
    return;
}
