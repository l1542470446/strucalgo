#include <saprint.h>
#include <sort.h>
#include <function.h>

void shellSort(struct dataArray *data)
{
    unsigned int tmpNr = data->nr;
    int *tmpDa = data->data;
    int tmpEx;
    unsigned int increment,i,j;
    for (increment = tmpNr/2; increment > 0; increment /= 2) {
        for (i = increment; i < tmpNr; i++) {
            /*insertion sort*/
            for (j = i; j >= increment; j -= increment) {
                tmpEx = tmpDa[j];
                if (tmpDa[j] > tmpDa[j-increment]) {
                    continue;
                } else {
                    tmpDa[j] = tmpDa[j-increment];
                    tmpDa[j-increment] = tmpEx;
                }
            }
        }
        saprint(data);
    }
}
