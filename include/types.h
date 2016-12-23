#include <stdbool.h>

#ifndef __TYPES__
#define __TYPES__

#define NULL ((void *)0)

typedef unsigned char   uchar;
typedef unsigned short  ushort;
typedef unsigned int    uint;
typedef unsigned long   ulong;

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

#endif
