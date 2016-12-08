#include <saprint.h>
#include <sort.h>

void bubbleSort(struct dataArray *data)
{
	unsigned int tempNr = data->nr;
	int *temp = data->data;
	int tempEx;
	unsigned int i,j;
	for (i = tempNr ; i > 0 ; --i) {
		for (j = 0 ; j < i ; j++) {
			if ( temp[j] > temp[j+1] ) {
				tempEx = temp[j];
				temp[j] = temp[j+1];
				temp[j+1] = tempEx;
			}
			saprint(data);
		}
	}
}
