#include <stdbool.h>

#ifndef __TYPES__
#define __TYPES__

#define NULL ((void *)0)

#define INT32_MIN (-2147483648)
#define INT32_MAX  (2147483647)
#define UINT32_MIN (0)

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

#define sa_offsetof(TYPE, MEMBER)	((uint)&((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - sa_offsetof(type,member) );})

#endif
