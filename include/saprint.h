
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

void saprint(struct dataArray *sa);

#endif
