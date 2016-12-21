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

void prArrBinTree(int *array,uint num)
{
	//calculate bin-tree layer
	uint layer = layerBinTree(num);
	//printf("layer = %d\n", layer);
	//calculate max value bit
	uint absoMax = findMaxAbsoVal(array, num);
	uchar bit = uDataBit(absoMax);
	//printf("absoMax = %d,bit = %d\n", absoMax, bit);
	//show tree
	uint i, j, aryn = 0;
	uint layerNum, layerSpa, layerBit;
	for (i = 0; i < layer; i++) {
		layerNum = pow(2,i);
		layerSpa = pow(2, layer - 1 - i) - 1;
		layerSpa = layerSpa * bit;
		layerBit = pow(2, layer - i);
		layerBit = layerBit * bit;
		printf("%-*s", layerSpa, "");
		for (j = 0; j < layerNum; j++) {
			printf("%-*d", layerBit, array[aryn++]);
			if (aryn >= num)
				break;
		}
		printf("\n");
	}
}
