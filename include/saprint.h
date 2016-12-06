
#ifndef __SAPRINT__
#define __SAPRINT__

struct dataArray{
	unsigned int nr;
	int data[0];
};

void saprint(struct dataArray *sa);

#endif
