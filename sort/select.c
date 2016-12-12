#include <saprint.h>
#include <sort.h>
#include <function.h>


void selectSortDC0(struct dataArray *data)
{
    unsigned int tempNr = data->nr;
	int *temp = data->data;
	int max;
	int i,j,imax;
    for (i = 0;i < tempNr-1;i++) {
        imax = i;
        max = temp[i];
        for (j = i+1;j < tempNr;j++) {
            if (temp[j] > max){
                max = temp[j];
                imax = j;
            }
        }
        dataExchange(temp+i,temp+imax);
        saprint(data);
    }
}


void selectSortIC0(struct dataArray *data)
{
    unsigned int tempNr = data->nr;
	int *temp = data->data;
	int min;
	int i,j,imin;
    for (i = 0;i < tempNr-1;i++) {
        imin = i;
        min = temp[i];
        for (j = i+1;j < tempNr;j++) {
            if (temp[j] < min){
                min = temp[j];
                imin = j;
            }
        }
        dataExchange(temp+i,temp+imin);
        saprint(data);
    }
}
