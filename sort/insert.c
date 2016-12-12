#include <saprint.h>
#include <sort.h>
#include <function.h>

void insertSortI(struct dataArray *data)
{
    int *temp = data->data;

    if (data->nr > 1) {
        int i,j;
        for (i = 1;i < data->nr;i++) {
            for (j = i;j > 0;j--) {
                if (temp[j] > temp[j-1]) {
                    continue;
                } else {
                    dataExchange(temp+j,temp+j-1);
                }
            }
            saprint(data);
        }
    }
}
