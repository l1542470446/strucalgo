#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include <saprint.h>
#include <sort.h>

void dataMalloc(struct dataArray *sa)
{
	int n=10;
	int a[10]={5,50,14,36,9,7,17,68,95,57};
	//sa=malloc(sizeof(struct dataArray)+3*sizeof(int));
	sa->data=malloc(n*sizeof(int));
	memset(sa->data,0,sizeof(*(sa->data)));
	sa->nr=n;
	char i;
	for(i=0;i<n;i++)
		sa->data[i]=a[i];
}



int main()
{
	struct dataArray sa;
	dataMalloc(&sa);
	//bubbleSort(&sa);
	//selectSortIC0(&sa);
	insertSortI(&sa);
//	int i=1;
//	for (i=2;i>0;i--)
//		saprint(&sa);
}
