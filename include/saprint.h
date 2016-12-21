#include <types.h>

#ifndef __SAPRINT__
#define __SAPRINT__

/*
struct dataArray{
	unsigned int nr;
	int data[0];
};
*/

struct dataArray{
	unsigned int nr;
	int *data;
};

extern void saprint(struct dataArray *sa);

extern void prArrBinTree(int *array,uint num);

#endif
