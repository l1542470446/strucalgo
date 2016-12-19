
#ifndef __SORT__
#define __SORT__

#include <saprint.h>

void bubbleSort(struct dataArray *data);
void selectSortDC0(struct dataArray *data);
void selectSortIC0(struct dataArray *data);
void insertSortI(struct dataArray *data);
void shellSort(struct dataArray *data);
void mergeSort(struct dataArray *data);
void quickSort(struct dataArray *data);
void bucketSort(struct dataArray *data);
void heapSort(struct dataArray *data);

void iSort(int *array,unsigned int n);

#endif
