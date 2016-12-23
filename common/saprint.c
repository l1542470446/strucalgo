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

/**************************************************************************************
*				|i++,layer=5	layerBit=	layerSpa=		layer_num=
*0123456789ABCDEF		|i < layer	2^(layer-i)	2^(layer-1-i)-1	2^i
*               1		|0		32		15			1
*       2               3	|1		16		7			2
*   4       5       6       7	|2		8		3			4
* 8   9   A   A   A   A   A   A	|3		4		1			8
*B B B B B B B B		|4		2		0			16
**************************************************************************************/
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
