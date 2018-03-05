/*
 * MovesHistory.h
 *
 *  Created on: Aug 25, 2017
 *      Author: tala
 */

#ifndef MOVESHISTORY_H_
#define MOVESHISTORY_H_

#include <stdlib.h>
#include <stdio.h>
/**
 * A type used for messages regarding errors
 */
typedef enum chess_array_list_message_t {
	CHESS_ARRAY_LIST_SUCCESS,
	CHESS_ARRAY_LIST_INVALID_ARGUMENT,
	CHESS_ARRAY_LIST_FULL,
	CHESS_ARRAY_LIST_EMPTY
} CHESS_ARRAY_LIST_MESSAGE;

/*
 * a type representing an array list. its fields are:
 *  talaMoves- array containing last moves of the two players, while every move is represented by
 *   sequent four elements in this array.
 *   for example the last made move <x,y> to <i,j>  will be saved in talaMoves as following:
 *   talaMoves[0]=x , talaMoves[1]=1 , talaMoves[2]=i , talaMoves[3]=j
 *   the move that was made just before that would be saved in
 *    talaMoves[4],talaMoves[5],talaMoves[6],talaMoves[7] and so on.
 *  maxSize-the maximal number of possible undo move invokations per turn, doubled by two.
 *  actualSize- the actual number of undo move invokations per turn, doubled by two.
 *
 */
typedef struct sp_array_list_t {
	int* talaMoves;
	int maxSize;
	int actualSize;
} ChessArrayList;

/*
 *  The array consists of an maxSize arrays, where each one contains of a "move array" with 4 elements,
 *  and it contains data about a certain move (the original move and the new one).
 *  The first two elements are the position of the original move, fromX and fromY.
 *  The second two elements are the new position, toI and toJ.
 *  This function creates an empty chess array list with the specified maximum capacity.
 *  @param maxSize - the maximum capacity of the target array list.
 *  @return
 *  NULL, if an allocation error occurred or maxSize  <= 0.
 *
 *  An instant of an array list otherwise.
 */
ChessArrayList* ChessArrayListCreate(int maxSize);


/**
 * returns a copy of a given ChessArrayList (parameter src)
 */
ChessArrayList* ChessArrayListCopy(ChessArrayList* src);

/**
 * Frees all memory resources associated with the source chess array list.
 * If the source array is NULL, then the function does nothing.
 * @param src - the source array list
 */

void ChessArrayListDestroy(ChessArrayList* src);

/**
 * Clears all move arrays from the source chess array list. After invoking this function,
 * the size of the source list will be reduced to zero and maximum capacity is
 * not affected.
 * @param src - the source array list
 * @return
 * CHESS_ARRAY_LIST_INVALID_ARGUMENT if src == NULL
 * CHESS_ARRAY_LIST_SUCCESS otherwise
 */
CHESS_ARRAY_LIST_MESSAGE ChessArrayListClear(ChessArrayList* src);

/**
 * Inserts a move array at the beginning of the source element. The rest of the arrays
 * will be shifted to make place for the new array. If the
 * array list reached its maximum capacity an error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param move  - the new element to be inserted
 * @return
 * CHESS_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * CHESS_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * CHESS_ARRAY_LIST_SUCCESS - otherwise
 */
CHESS_ARRAY_LIST_MESSAGE ChessArrayListAddFirst(ChessArrayList* src, int move);

/**
 * Removes an array of "move" from a the end of the list.
 * The elements (rest of the arrays) will be shifted to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @return
 * CHESS_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * CHESS_ARRAY_LIST_EMPTY - if the source array list is empty
 * CHESS_ARRAY_LIST_SUCCESS - otherwise.
 */
CHESS_ARRAY_LIST_MESSAGE ChessArrayListRemoveLast(ChessArrayList* src);

/**
 * Removes an array from the beginning of the chess list.
 * The arrays will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @return
 * CHESS_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * CHESS_ARRAY_LIST_EMPTY - if the source array list is empty
 * CHESS_ARRAY_LIST_SUCCESS - otherwise
 */
CHESS_ARRAY_LIST_MESSAGE ChessArrayListRemoveFirst(ChessArrayList* src);

/**
 * Returns the number of arrays in the array list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the number of the elements (arrays) in the list is returned.
 */
int ChessArrayListSize(ChessArrayList* src);

/**
 *
 * Returns the maxSize of the arraylist.
 * The function is called with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, maxSize is returned.
 */

int ChessArrayListMaxSize(ChessArrayList* src);
/**
 * Returns the element at the beginning of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the beginning of the list is returned.
 */
int ChessArrayListGetFirst(ChessArrayList* src);

#endif /* MOVESHISTORY_H_ */
