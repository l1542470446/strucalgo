#include <stdio.h>

#include <types.h>
#include <tree.h>

#ifndef __SAPRINT__
#define __SAPRINT__
/*
#define ERROR(fmt, ...) \
	printf(">>>ERROR:"); \
	printf(fmt, ##__VA_ARGS__)
*/
#define PRINT(a, fmt, ...) \
	printf(">>>%s:", a); \
	printf(fmt, ##__VA_ARGS__)

#define ERROR(fmt, ...) PRINT("ERROR", fmt, ##__VA_ARGS__)
#define WARN(fmt, ...)  PRINT(">WARN", fmt, ##__VA_ARGS__)

extern void saprint(struct dataArray *sa);
extern void prArrBinTree(int *array,uint num);

extern struct treeNodeList *__prBinTree(struct treeNodeList *head, uint layer, uint layerMax, uchar bit);
extern void prSimpBinTree(struct treeNode *head);

#endif
