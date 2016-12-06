#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include <saprint.h>


void dataMalloc(struct dataArray *sa)
{
	int n=3;
	sa=malloc(sizeof(struct dataArray)+3*sizeof(int));
	memset(sa,0,sizeof(*sa));
	sa->nr=3;
	sa->data[0]=1;
	sa->data[2]=2;
	sa->data[3]=3;
}



main()
{
	struct dataArray sa;
	dataMalloc(&sa);	
	/*
	sa.nr=10;	
	int data[10]={4,5,3,9,44,51,35,99,37,16};
	char si=0;
	for(si=0;si<sa.nr;si++)
		sa.data[si]=data[si];
	
	sa.data[0]=4;
	sa.data[1]=5;
	sa.data[2]=3;
	sa.data[3]=9;
	sa.data[4]=4;
	sa.data[5]=4;
	sa.data[6]=4;
	sa.data[7]=4;
	sa.data[8]=4;
	sa.data[9]=4;
*/
	saprint(&sa);
//	saprint(&sa);
//	free(&sa);
}
