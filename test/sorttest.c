#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include <saprint.h>
#include <sort.h>
#include "data.h"

void dataMalloc(struct dataArray *sa)
{
	int n=10;
	//int a[10] ={5,50,14,5,9,7,17,68,95,57};
	//sa=malloc(sizeof(struct dataArray)+3*sizeof(int));
	sa->data=malloc(n*sizeof(int));
	memset(sa->data,0,sizeof(*(sa->data)));
	sa->nr=n;
	char i;
	for(i=0;i<n;i++)
		sa->data[i]=arData10[i];
}

int main()
{
	struct dataArray sa;
	dataMalloc(&sa);
	//bubbleSort(&sa);
	//selectSortIC0(&sa);
	//insertSortI(&sa);
	//shellSort(&sa);
	saprint(&sa);
	//mergeSort(&sa);
	//quickSort(&sa);
	//bucketSort(&sa);
	heapSort(&sa);
	//saprint(&sa);
}
