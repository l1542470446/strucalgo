#include <stdio.h>

struct dataArray{
	unsigned int nr;
	int data[];
}

main()
{
	struct dataArray sa;
	sa.nr=2;
	sa.data[0]=1;
	sa.data[1]=2;
	printf("ssss %d,%d\n",sa.data[0],sa.data[1]);
}
