/*
 * setting.h
 *
 *  Created on: Aug 13, 2017
 *      Author: tala
 */

#ifndef SETTING_H_
#define SETTING_H_
#include <stdbool.h>
#include "ChessArrayList.h"

//Definitions
#define ROWS 8
#define COLUMNS 8
#define BLACK_PLAYER_SYMBOL 0
#define WHITE_PLAYER_SYMBOL 1
#define EMPTY_ENTRY '_'
#define WHITE_PAWN 'm'
#define BLACK_PAWN 'M'
#define WHITE_BISHOP 'b'
#define BLACK_BISHOP 'B'
#define WHITE_ROOK 'r'
#define BLACK_ROOK 'R'
#define WHITE_KNIGHT 'n'
#define BLACK_KNIGHT 'N'
#define WHITE_QUEEN 'q'
#define BLACK_QUEEN 'Q'
#define WHITE_KING 'k'
#define BLACK_KING 'K'
#define GAME_MODE_1 1
#define GAME_MODE_2 2
#define MAX_DIFFICULTY 5
#define MIN_DIFFICULTY 1
#define DASH '-'



/*
 * a new type that represents a game and relevant settings.
 * fields:
 * 	gameMode- 1 for 1-player mode, 2 for 2-player mode
	isInSetting- true if in setting state, false if in game state
	gameDifficulty-range 1 to 4
	playerColor- represents user color : 1 for white, 0 for black, relevant if in 1-mode state
	currentPlayer- 1 for white, 0 for black
	gameBoard-  gameboard representation (double array)
	historySize- the maximal number of undo move command possible per each turn
	movesHistory- a pointer to ChessArrayList array that saves the last moves
	Player1LastDestinations- a pointer to ChessArrayList array representing white player array
	 that saves the pieces that were originally in the latest destinations, can be empty entry or captured pieces
	Player2LastDestinations- a pointer to ChessArrayList array representing black player array
	 that saves the pieces that were originally in the latest destinations, can be empty entry or captured pieces
	supported- boolean: true if expert level supported,false otherwise
	shouldGoToNextTurn- boolean: set to true if a move was set by current player and
	 the game must go on to next turn
	undoCountPerTurn- counter for number of invocations of "undo" command per turn
 */
typedef struct chess_game_t {
	int gameMode;
	bool isInSetting;
	int gameDifficulty;
	int playerColor;
	int currentPlayer;
	char gameBoard[ROWS][COLUMNS];
	int historySize;
	ChessArrayList* movesHistory;
	ChessArrayList* Player1LastDestinations;
	ChessArrayList* Player2LastDestinations;
	bool supported;
	bool shouldGoToNextTurn;
	int undoCountPerTurn;
} ChessGame;

/**
 * Type used for returning error codes from game functions
 */
typedef enum game_message_t {
	INVALID_MOVE,
	INVALID_ARGUMENT,
	NO_HISTORY,
	GAME_SUCCESS,
} GAME_MESSAGE;

/**
 * Creates a new chess game with a specified history size and with the default settings.
 * The default settings are:
 * 		game mode : 1 (1-player mode)
 * 		difficulty level : 2 (easy)
 * 		user color : 1 (white)
 *
 * The history size is a parameter which specifies the number of previous moves to store.
 * If the number of moves played so far exceeds this parameter, then first moves stored will
 * be discarded in order for new moves to be stored.
 *
 * Undo command is available only in 1-player mode.
 * @historySize - The total number of moves to undo,
 *                a player can undo at most historySizeMoves turns.
 * @return
 * NULL if either a memory allocation failure occurs or historySize <= 0.
 * Otherwise, a new game instant is returned.
 */
ChessGame* GameCreate(int historySize);

/**
 *  Creates a copy of a given game.
 *	The new copy has the same status and settings as the src game.
 *
 *	@param src - the source game which will be copied
 *	@return
 *	NULL if either src is NULL or a memory allocation failure occurred.
 *	Otherwise, an new copy of the source game is returned.
 *
 */
ChessGame* GameCopy(ChessGame* src);

/*
 * Clears the current game by clearing the movesHistory array and the game board
 * also resets the settings to the default settings
 **/
void ClearGame(ChessGame* src);

/*
 * Clears the current game by clearing the movesHistory array and the game board
 * without changing current settings
 */
void ClearGameWithoutChangingSetting(ChessGame* src);

/**
 * Frees all memory allocation associated with a given game. If src==NULL
 * the function does nothing.
 *
 * @param src - the source game
 */
void GameDestory(ChessGame* src);

/**
 * Given a source game and a desired mode, sets the game mode to that mode.
 *
 * @param
 * src - the source game for which the mode will be set
 * mode - 1 or 2 for 1-player, or 2-player mode, respectively
 * @return
 * INVALID_ARGUMENT - if src is NULL or mode is out-of-range
 * GAME_SUCCESS - otherwise
 *
 */
GAME_MESSAGE SetMode(ChessGame* src, int mode);

/**
 * Returns the game mode of a given game.
 * The function is called with the assertion that all arguments are valid.
 * If any of the arguments is invalid then an undefined value is returned.
 *
 * @param src - the source game for which the mode will be returned
 *
 * @return
 * Undefined value if either src == NULL
 * Otherwise, 1 or 2 is returned for 1-player, or 2-player mode, respectively.
 */
int GetMode(ChessGame* src);

/*
 * Available only in 1-player mode
 * Given a source game and a desired difficulty, sets the game difficulty level to that difficulty
 *
 * @param
 * src - the source game for which the mode will be set
 * diff - the number which represents the difficulty of the game, should be between 1-5
 * @return
 * INVALID_ARGUMENT - if src is NULL or diff is out-of-range
 * GAME_SUCCESS - otherwise
 */
GAME_MESSAGE SetDifficulty(ChessGame* src, int diff);

/**
 * Returns the difficulty level of a given game.
 * The function is called with the assertion that all arguments are valid.
 * If any of the arguments is invalid then an undefined value is returned.
 *
 * @param src - the source game for which the difficulty will be returned
 *
 * @return
 * Undefined value if src == NULL
 * Otherwise, the number which represents the difficulty of the game will be returned
 */
int GetDifficulty(ChessGame* src);

/**
 * Available only in 1-player mode.
 * Given a source game and a chosen color, sets player's color.
 *
 * @param
 * src - the source game for which the mode will be set
 * color - 0 or 1, for black or white respectively
 *
 * @return
 * INVALID_ARGUMENT - if src is NULL or color is out-of-range
 * GAME_SUCCESS - otherwise
 */
GAME_MESSAGE SetColor(ChessGame* src,int color);

/**
 * @param
 * src - the source game of which the player's color will be returned
 *
 * @return
 * Undefined value if src == NULL
 * Otherwise, 0 or 1 - for black or white, respectively
 */
int GetUserColor(ChessGame* src);


/**
 * Given a source game returns current player symbol
 * The function is called with the assertion that all arguments are valid.
 * If any of the arguments is invalid then an undefined value is returned.
 *
 * @param
 * src - the source game
 *
 * @return
 * Undefined value if src == NULL
 * Otherwise BLACK_PLAYER_SYMBOL or WHITE_PLAYER_SYMBOL - for black player or white player, respectively
 */
int GetCurrentPlayer(ChessGame* src);


/**
 * Changes the current player to the opposite one, if src == NULL the function does nothing
 * @param
 * src - the source game
 */
void ChangeCurrentPlayer(ChessGame* src);

/**
 * translates decimal number digit to character representing that digit, 0 goes to '0', 7 goes to '7'
 * @param
 * i-decimal digit
 * @return
 * a character that has the specified ascii value
 */
char translateIntToChar2(int i);

/**
 * given a source game, prints the game board as instructed
 */
void printBoard(ChessGame* src);

/*
 * Resets the game setting to the default values
 */
void defaultSettings(ChessGame* src);

/**
 * given a source game, initializes the game board to the starting positions of Chess.
 */
void initBoard(ChessGame* src);

#endif /* SETTING_H_ */
