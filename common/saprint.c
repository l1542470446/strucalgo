#include <stdio.h>
#include <saprint.h>

void saprint(struct dataArray *sa)
{
	unsigned int i=0;
	for(i=0;i<sa->nr;i++)
		printf("%d ",sa->data[i]);
	printf("\n");
}
