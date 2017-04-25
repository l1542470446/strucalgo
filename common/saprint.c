#include <stdio.h>
#include <math.h>

#include <types.h>
#include <saprint.h>
#include <tree.h>

void saprint(struct dataArray *sa)
{
	unsigned int i=0;
	for(i=0;i<sa->nr;i++)
		printf("%d ",sa->data[i]);
	printf("\n");
}

