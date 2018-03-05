/*
 * game.h
 *
 *  Created on: Aug 13, 2017
 *      Author: tala
 */

#ifndef GAME_H_
#define GAME_H_

#include "setting.h"
#include <stdbool.h>
#define MAX_SIZE 1024

/** a type used to represent the result of every move that was just made.
 *  this announciation is made by player x after player x made his recent move.
 *  CHECK-indicates that the player who just played has put the opponent in check.
 *  CHECKMATE-same as CHECK, only with CHECKMATE
 *  ELSE - indicates that nothing special happened after this last move, the game must go on.
 **/
typedef enum result_message_t {
	CHECK,
	CHECKMATE,
	TIE,
	ELSE,
} RESULT_MSG;

//a type used to represent the message returned after trying to invoke a desired move
typedef enum invalid_move_message_t {
	INVALID_POSITION,
	NO_PIECE_IN_SOURCE,
	ILLEGAL_MOVE,
	VALID_MOVE
} INVALID_MOVE_MSG;


/**
 * 1. checks if moving the piece at <fromX,fromY> to <toI,toJ> is valid, and if not,
 *  checks what message should be returned about this move.
 * 2. prints a message to the user according to the message described in 1.
 * 3. if the move turned out to be valid, performs the move on the board,
 *    and announces what impact could this move have on the game:
 * 		A. Check
 * 		B. Checkmate
 * 		C. Tie
 * 		D. else- no special impact, game is still on
 * 	4. if the move has no special impact, changes current player. Game is still on.
 * @param
 *	fromX -left coordinate of the source position of the move
 *	fromY -right coordinate of the source position of the move
 *	toI -left coordinate of the target position of the move
 *	toJ -right coordinate of the target position of the move
 *	currentPlayer
 *	src -current game
 */
void play(int fromX,int fromY,int toI,int toJ,ChessGame* src);

/**
 * checks if the move about to be performed is legal for a pawn in the current game board
 * @param
 * gameBoard-the game board of current game
 * fromX -left coordinate of the source position of the move
 *	fromY -right coordinate of the source position of the move
 *	toI -left coordinate of the target position of the move
 *	toJ -right coordinate of the target position of the move
 *	curr_player - current player
 */
INVALID_MOVE_MSG isValidPawn(char (*gameBoard)[8],int fromX,int fromY,int toI,int toJ,char curr_player);

/**
 * checks if the move about to be performed is legal for a bishop in the current game board
 * @param
 * gameBoard-the game board of current game
 * fromX -left coordinate of the source position of the move
 *	fromY -right coordinate of the source position of the move
 *	toI -left coordinate of the target position of the move
 *	toJ -right coordinate of the target position of the move
 *	curr_player - current player
 */
INVALID_MOVE_MSG isValidBishop(char (*gameBoard)[8],int fromX,int fromY,int toI,int toJ,char curr_player);

/**
 * checks if the move about to be performed is legal for a rook in the current game board
 * @param
 * gameBoard-the game board of current game
 * fromX -left coordinate of the source position of the move
 *	fromY -right coordinate of the source position of the move
 *	toI -left coordinate of the target position of the move
 *	toJ -right coordinate of the target position of the move
 *	curr_player - current player
 */
INVALID_MOVE_MSG isValidRook(char (*gameBoard)[8],int fromX,int fromY,int toI,int toJ,char curr_player);

/**
 * checks if the move about to be performed is knight for a pawn in the current game board
 * @param
 * gameBoard-the game board of current game
 * fromX -left coordinate of the source position of the move
 *	fromY -right coordinate of the source position of the move
 *	toI -left coordinate of the target position of the move
 *	toJ -right coordinate of the target position of the move
 *	curr_player - current player
 */
INVALID_MOVE_MSG isValidKnight(char (*gameBoard)[8],int fromX,int fromY,int toI,int toJ,char curr_player);

/**
 * checks if the move about to be performed is legal for a king in the current game board
 * @param
 * gameBoard-the game board of current game
 * fromX -left coordinate of the source position of the move
 *	fromY -right coordinate of the source position of the move
 *	toI -left coordinate of the target position of the move
 *	toJ -right coordinate of the target position of the move
 *	curr_player - current player
 */
INVALID_MOVE_MSG isValidKing(char (*gameBoard)[8],int fromX,int fromY,int toI,int toJ,char curr_player);

/**
 * checks if the move about to be performed is legal for a queen in the current game board
 * @param
 * gameBoard-the game board of current game
 * fromX -left coordinate of the source position of the move
 *	fromY -right coordinate of the source position of the move
 *	toI -left coordinate of the target position of the move
 *	toJ -right coordinate of the target position of the move
 *	curr_player - current player
 */
INVALID_MOVE_MSG isValidQueen(char (*gameBoard)[8],int fromX,int fromY,int toI,int toJ,char curr_player);

/**
 * given a piece and the current player, tells if this piece belongs to the opposite player or not.
 * @param
 * piece- character representing the relevant character
 * curr_player- current player
 * @return
 * true- if piece belongs to the oppositeplayer
 * false- if the piece belongs to the current player
 */
bool isOppositeColor(char piece,char curr_player);

/**
 * given a game and a move from <x,y> to <i,j> , checks if move is valid.
 * @param
 * src - source game to be checked
 * fromX - x coordinate of source position
 * fromY - y coordinate of source position
 * toI - i coordinate of target position
 * toJ - j coordinate of target position
 *
 *@return
 *INVALID_POSITION - if either one of the locations in the command is invalid
 *NO_PIECE_IN_SOURCE - if position <x,y> does not contain a piece of the user's color
 *ILLEGAL_MOVE - if the move is illegal for the piece in the position <x,y>
 *VALID_MOVE - otherwise
 *
 */
INVALID_MOVE_MSG isValidMove(ChessGame* src,int fromX, int fromY, int toI, int toJ);

/**
 * Moves the current player's piece located at <x,y> to <i,j> in a given source game.
 * Function is called only after checking that the move from <x,y> to <i,j> is valid.
 *
 * param@
 * src - given source game
 * fromX - x coordinate of source position
 * fromY - y coordinate of source position
 * toI - i coordinate of target position
 * toJ - j coordinate of target position
 *
 * The board is updated and one of the following is returned
 * @return
 * CHECK - if any of the player’s king is threatened. This should be returned if there is no Checkmate.
 * CHECKMATE - In case there is a "checkmate
 * TIE - In case there is a tie
 * ELSE - if there is no special case such as the above and the game shall continue to next turn.
 */
RESULT_MSG SetMove(ChessGame * src, int fromX, int fromY, int toI, int toJ);


/**
* same as SetMove only without testing all the possible results of current move, and without pawn promotion
* @param
* same as SetMove
* @return
* true if current move has put the other player in checkmate.
* false otherwise
**/
bool Simple_SetMove(ChessGame * src, int fromX, int fromY, int toI, int toJ);

/*
 * bonus: decided not to use it
 */
void pawn_promotion(ChessGame* src,char piece,int toI, int toJ);


/*
 * a function that checks whether ,after making a move, i put my opponent in check or not.
 * this is checked by going over all the current player's pieces and seeing if any of them
 * can capture the other's king in the next move.
 * @param
 * src-current game
 * oppkingX-opponent king's row coordinate
 * oppkingY-opponent king's column coordinate
 * ptrToDangerousX-pointer to the threatening piece row coordinate
 * ptrToDangerousY-pointer to the threatening piece column coordinate
 */
bool did_I_put_Opponent_In_Check(ChessGame * src,int oppkingX, int oppkingY, int *ptrToDangerousX, int *ptrToDangerousY);


/*
 * a function that checks whether ,after making a move, i put myself in check or not.
 * this is checked by going over all the opponent player's pieces and seeing if any of them
 * can capture my king in his next move.
 * @param
 * src-current game
 * fromX,fromY,toI,toJ - coordinates of current last move <x,y> to <i,j> made by current player
 */
bool did_I_put_myself_In_Check(ChessGame * src, int fromX, int fromY, int toI, int toJ);



/*@param
 * src-current game
 * kingX-opponent king's row coordinate
 * kingY-opponent king's column coordinate
 * ptrToDangerousX-pointer to the threatening piece row coordinate
 * ptrToDangerousY-pointer to the threatening piece column coordinate
 */
bool isInCheckMate(ChessGame * src, int dangerousPieceX, int dangerousPieceY, int kingX, int kingY);

/* the function is called when some player is in check.
 * It tells whether the player in check can escape from it by moving the king.
 * @param
 * src-current game
 * kingX-opponent king's row coordinate
 * kingY-opponent king's column coordinate
 * @return
 * true-if checked king can move and escape from threat.
 * false-otherwise.
 */
bool kingCanEscape(ChessGame * src, int kingX, int kingY);


/* the function is called when some player is in check.
 * It tells whether the player in check can escape from it by moving the king.
 * @param
 * src-current game
 * dangerousPieceX- x coordinate of the piece that has just put the king in check.
 * dangerousPieceY- y coordinate of the piece that has just put the king in check.
 * @return
 * true-if the player under check can get out of check by capturing the dangerous piece.
 * false-otherwise.
 */
bool canCaptureCheckingPiece(ChessGame * src, int dangerousPieceX, int dangerousPieceY);

/* the function is called when some player is in check.
 * It tells whether the player in check can escape from it by moving the king.
 * if th threatetnig piece is a knight then false is returned because there is no way to
 *  block a knight,it jumps over all pieces!
 * Also no way to block a threatening pawn because he must be adjacent to the king in danger if he is threatening
 * Also no way to block a threatening king because he must be adjacent to the king in danger
 * @param
 * src-current game
 * dangerousPieceX- x coordinate of the piece that has just put the king in check.
 * dangerousPieceY- y coordinate of the piece that has just put the king in check.
 * kingX-opponent king's row coordinate
 * kingY-opponent king's column coordinate
 * @return
 * true-if the player under check can get out of check by blocking the dangerous piece from reaching the threatened king.
 * false-otherwise.
 */
bool canBlockCheck(ChessGame * src, int dangerousPieceX, int dangerousPieceY, int kingX, int kingY);

/*
 * helper function for function canBlockCheck:
 *  tells if there is any piece (belonging to the player who is
 *   in danger) that can be moved to certain square (minX,minY) in order to block the threat.
 * @param
 * src- game
 * minX- x coordinate of the square being tested currently
 * minY- y coordinate of the square being tested currently
 */
bool can_victim_block_threat(ChessGame * src, int minX, int minY);

/**
 * the function is called if there is no check meantime! because if there is a check then it's cerainly not a tie
 * if the opponent's king is checked (by current player) then it's not a tie
 * because i might win after having warned my opponent.
 * otherwise the game is not checked, that's why, after having made a move,
 * current player will check if opponent doesn't have any legal move,
 * 			and if so then it's a tie.
 * 			otherwise, he has a possible legal move and it's not a tie.
 * @param
 * kingX- x position of opponent king
 * kingY- y position of opponent king
 */
bool isItATie(ChessGame *src,int kingX,int kingY);

/**
 * takes a pointer to x and y coordinate, and updates the content of these two pointers to hold
 * the position of the opponent's king
 */
void find_opponent_king(ChessGame * src, int* kingX, int* kingY);

/**
 * takes a pointer to x and y coordinate, and updates the content of these two pointers to hold
 * the position of one's own king
 */
void find_my_king(ChessGame * src, int* kingX, int* kingY);

/**
 * Given a game, a piece and the new position to of that piece on board,
 * this function calculates the consequences of this piece being in this position.
 * The consequences may be one of the following:
 * 		1.There's a CHECK
 * 		2.There's a CHECKMATE
 * 		3.There's a TIE
 * 		4.There's nothing special, no warning, game is still on as it was,
 * 		  opposite player should play next.
 *
 *
 *each player is not allowed to make a move that threatens his king,
 *so we'll be in check or checkmate or tie according to this function only when the threatining player has just played!

 * @param
 * src- source game
 * @return
 * CHECK - if any of the player’s king is threatened. This should be returned if there is no Checkmate.
 * CHECKMATE - In case there is a "Checkmate"
 * TIE - In case there is a tie
 * ELSE - if there is no special case such as the above and the game shall continue to next turn.
 */
RESULT_MSG result_of_current_move(ChessGame * src);

/*
 * updates the history array which contains the last moves made by the user and computer
 */
void MovesHistoryUpdate(ChessGame* src, int fromX, int fromY, int toI, int toJ);

/*
 * Updates the destinations array which includes the pieces of the player's latest destinations as follows:
 * for each player, adds the last position that the player went to, to the player's private array of last destinations
 * piece- a char, may be an empty entry or a representation of a captured piece that belonged to the opponent
 */
void PlayerDestinataionUpdate(ChessGame* src, char piece);

/**
 * Function available only in 1-player mode
 *
 * puts back to previous position the last piece that was moved and updates the position that was occupied recently by this last piece.
 * If the user invoked this command more than historySize times in a row then an error is announced.
 * If there is no moves in history then the command is not executed and the user is told so.
 *
 * @return
 * NO_HISTORY - If the user is trying to invoke the undo command and the history is empty.
 * GAME_SUCCESS - otherwise
 */
GAME_MESSAGE undo_move(ChessGame * src);


/**
 * Switches the program state to the setting state.
 * Clears all current setting
 * The following message is printed after the execution of this command "Restarting...\n"
 */
void reset(ChessGame * src);

/*
 * Terminates the game.
 * frees all resources.
 * before terminating prints the message "Exiting..."
 * @param
 */
void quitGame(ChessGame* game);

/*
 * Bonus: This feature is only supported in 1 player mode and difficulties 1 and 2 (noob and easy),
 * and it presents to the user all possible moves that can be performed
 * by a specified piece(at position <x,y> on board)
 */
void get_moves(ChessGame * src, int x, int y);

/*
 * boolean function that tells if there is any piece belonging to opponent player that can capture
 * the current player's piece located at position1,position2
 */
bool opponent_can_reach_position(ChessGame * game,int position1,int position2);

/*
 * Prints the msg: "Exiting..." when quit command is executed
 */
void printExiting();

/*
 *  The game asks the relevant user to enter her move by printing a specified message
 *
 *  @param-
 *  curr_player - current player in order to print the msg accordingly
 */
void printEnterYourMove(int curr_player);

/*
 * After user enters desired move, if either one of the locations in the command is invalid,
 * the program prints a specified message
 */
void printInvalidPosition();
/*
 * If the user enters desired position on the board and it does not contain a piece of the user's color,
 * the function prints specified msg
 */
void printNoPieceContained();

void printNoPieceContainedGetMoves(int curr_player);

/*
 * If the entered move by the user is illegal for the piece in the position, the function prints specified msg
 */
void printIllegalMove();
/*
 * If the AI's king is threatened and there's a check, prints a spcefied msg
 * @param
 * threatened - color of threatened king, in order to print the msg accordingly
 */
void printCheckByPlayer(int threatened);

/*
 * If the user's king is threatened and there's a check, prints a spcefied msg
 */
void printCheckByComputer();


/*
 * In case there is a "checkmate" - a specified message is printed
 * @param
 * winner - the winner's color, in order to print the msg accordingly
 */
void printCheckmate(int winner);

/*
 * Prints a specified msg in case of a tie in the game that was caused by last move of the user
 */
void printTieByPlayer();


/*
 * Prints a specified msg in case of a tie in the game that was caused by last move of the AI
 */
void printTieByComputer();


/*
 * prints "Restarting..." when reset command is invoked
 */
void printRestarting();

/*
 * currently unused function: prints the message
 *  "Pawn promotion- please replace the pawn by queen, rook, knight, bishop or pawn:\n"
 */
void printPawnPromotion_player();

/*
 * currently unused function: prints the message "Invalid Type" if the user enters a wrong option of promotion
 * the right options are "queen,bishop,rook,pawn"
 */
void printInvalidTypePawnPromotion();


#endif /* GAME_H_ */
