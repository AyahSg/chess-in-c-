/*
 * MoveHistory.c
 *
 *  Created on: Aug 25, 2017
 *      Author: tala
 */

#include "ChessArrayList.h"
#include <string.h>


ChessArrayList* ChessArrayListCreate(int maxSize){
	maxSize=maxSize*4;//every 4 spots are 1 move
	if (maxSize<=0)
		return NULL;
	ChessArrayList *list = (ChessArrayList*) malloc(sizeof(ChessArrayList));
	if (!list) return NULL;
	int* talaMoves=(int*)malloc(sizeof(int)*maxSize);
	list->talaMoves=talaMoves;
	list->maxSize=maxSize;
	list->actualSize=0;
	return list;
}

ChessArrayList* ChessArrayListCopy(ChessArrayList* src){
	if (!src){
		printf("ERROR: null pointer in function ChessArrayListCopy in ChessArrayList.c\n");
		fflush(stdout);
		return NULL;
	}
	ChessArrayList *copy=(ChessArrayList*)malloc(sizeof(ChessArrayList));
	int *dup = (int*)malloc(sizeof(int)*src->maxSize);
	if (!copy || !dup){
		printf("ERROR: memory allocation fail in function ChessArrayListCopy in ChessArrayList.c\n");
		fflush(stdout);
		return NULL;
	}
	copy->maxSize=src->maxSize;
	copy->actualSize=src->actualSize;
	int len=src->actualSize;
	memcpy(dup,src->talaMoves,len*sizeof(int));
	copy->talaMoves=dup;
	return copy;
}

void ChessArrayListDestroy(ChessArrayList* src){
	if (!src){
		return;
	}
	if (!src->talaMoves){
		free(src);
		return;
	}
	free(src->talaMoves);
	free(src);
}

CHESS_ARRAY_LIST_MESSAGE ChessArrayListClear(ChessArrayList* src){

	CHESS_ARRAY_LIST_MESSAGE res;
	if (!src){
		printf("ERROR: null pointer in function ChessArrayListClear in ChessArrayList.c\n");
		fflush(stdout);
		res=CHESS_ARRAY_LIST_INVALID_ARGUMENT;
		return res;
	}
	src->actualSize=0;
	res=CHESS_ARRAY_LIST_SUCCESS;
	return res;
}

CHESS_ARRAY_LIST_MESSAGE ChessArrayListAddFirst(ChessArrayList* src, int move){
	CHESS_ARRAY_LIST_MESSAGE res;
	if (!src){
		printf("ERROR: null pointer in function ChessArrayListClear in ChessArrayList.c\n");
		fflush(stdout);
		res=CHESS_ARRAY_LIST_INVALID_ARGUMENT;
		return res;
	}
	if (src->actualSize==src->maxSize){
		res=CHESS_ARRAY_LIST_FULL;
		return res;
	}
	memmove(&src->talaMoves[1], &src->talaMoves[0], (src->maxSize-1)*sizeof(int));
	src->talaMoves[0]=move;
	src->actualSize++;
	res=CHESS_ARRAY_LIST_SUCCESS;
	return res;
}

CHESS_ARRAY_LIST_MESSAGE ChessArrayListRemoveLast(ChessArrayList* src){
	CHESS_ARRAY_LIST_MESSAGE res;
	if (!src) {
		printf("ERROR: null pointer in function ChessArrayListClear in ChessArrayList.c\n");
		fflush(stdout);
		res=CHESS_ARRAY_LIST_INVALID_ARGUMENT;
		return res;
	}
	if (src->actualSize==0){
		res=CHESS_ARRAY_LIST_EMPTY;
		return res;
	}
	src->actualSize--;
	res=CHESS_ARRAY_LIST_SUCCESS;
	return res;
}

int ChessArrayListSize(ChessArrayList* src){
	if (!src){
		printf("ERROR: null pointer in function ChessArrayListSize in ChessArrayList.c\n");
		fflush(stdout);
		return -1;
	}
	return src->actualSize;

}

int ChessArrayListMaxSize(ChessArrayList* src){
	if (!src){
		printf("ERROR: null pointer in function ChessArrayListSize in ChessArrayList.c\n");
		fflush(stdout);
		return -1;
	}
	return src->maxSize;
}


CHESS_ARRAY_LIST_MESSAGE ChessArrayListRemoveFirst(ChessArrayList* src){
	CHESS_ARRAY_LIST_MESSAGE res;
	if (!src) {
		printf("ERROR: null pointer in function ChessArrayListRemoveFirst in ChessArrayList.c\n");
		fflush(stdout);
		res=CHESS_ARRAY_LIST_INVALID_ARGUMENT;
		return res;
	}
	if (src->actualSize==0){
		res=CHESS_ARRAY_LIST_EMPTY;
		return res;
	}
	memmove(&src->talaMoves[0], &src->talaMoves[1], (src->maxSize-1)*sizeof(int));
	src->actualSize--;
	res=CHESS_ARRAY_LIST_SUCCESS;
	return res;
}

int ChessArrayListGetFirst(ChessArrayList* src){
	if (!src || src->actualSize==0){
		printf("ERROR: null pointer in function ChessArrayListRemoveFirst in ChessArrayList.c\n");
		fflush(stdout);
		return -1;
	}
	return src->talaMoves[0];
}
