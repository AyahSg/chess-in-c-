/*
 * minimax.h
 *
 *  Created on: Aug 13, 2017
 *      Author: tala
 */

#ifndef MINIMAX_H_
#define MINIMAX_H_

#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* minimax:
 * implements minimax algorithm. Recursively calculates the score of each game state
 * @param
 * currentGame-curent game
 * maxDepth - difficulty level chosen by user and equals maximal recursion depth ,
 * isMaximizing - if true the function calculates score for currentGame being a max node,
 * 				if false currentGame is conisdered min node
 * alpha- used in alpha-beta pruning
 * beta- used in alpha-beta pruning
 * @return
 * The score of current game board for current player
 */
int minimaxInt(ChessGame* currentGame, int maxDepth, bool isMaximizing, int alpha, int beta);

/*
 * Goes over all current possible moves in currentGame that current player can make.
 * tells which move of all possible moves is the best and most convenient for the AI player
 * @param
 * currentGame- current game state, maxDepth - difficulty level chosen by user
 * @return
 * 4-cells-array containing {fromX,fromY,toI,toJ} according to best x,y coordinate to move from
 * and i,j coordinate to move to, respectively
 */
int* mybestmoveInt(ChessGame * currentGame,int maxDepth);

/*
 * implements scoring function for minimax algorithm.
 * The naïve scoring function goes over the board and outputs a score according to the pieces on the board.
 * The scores for each piece are given below:
 *  pawn = 1 , knight = 3 , bishop = 3 , rook = 5, queen = 9, king=100
 * if the piece belongs to current player then it's considered as a positive number as listed above
 *  else if the piece belongs to opponent player, it's considered the negative of what's listed above.
 * @param
 * currentGame-curent game
 * @return
 * score
 */
int naive_scoring(ChessGame* currentGame,bool isMaximizing);


/*
 * given game board as input checks if there are any possible moves left for the current player or if the game is tied.
 * @param
 * currentGame- current hypthetical game , used in minimax algorithm
 * @return
 * true- if game is tied or if there are no possible valid moves for current player
 * false- otherwise
 */
bool isTerminal(ChessGame* currentGame);

#endif /* MINIMAX_H_ */
