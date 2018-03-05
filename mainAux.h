/*
 * mainAux.h
 *
 *  Created on: Aug 13, 2017
 *      Author: tala
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_

#include "cmdparser.h"
#include "game.h"


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



/**
 * The function prints the settings of the games and then prompts for the user's commands.
 * The user can enter commands regarding the game settings such as "difficulty 1","game_mode 2" and so on..
 *  only if the user enters the command "start" the program exits setting state and
 *  enters the game state. While the user is entering commands other than "start",
 * 	the function keeps taking input from the user.
 * The moment the command "start" is entered, the game's field "isInSetting" is set to false,
 *  and the function game_state is called with the-already-set settings.
 */
void setting_state(ChessGame* game);

/**
 * The function prints the game board whenever it's a user's turn(but not if it's computer's turn),
 * and then prompts for the user's commands.
 * The user can enter commands regarding the game such as "move <x,y> to <i,j>","undo", etc.
 * The function keeps asking the user for commands until the user enters
 *  a valid move command (move one piece from one position to the other).
 * Whenever a valid move was done, the program changes the current player and
 * 	the game goes on with the opposite player being the current.
 *  So the function calls itself in such a case, but with another player.
 * Only if the user enters the command "reset" the program exits game state and
 *  enters the setting state. While the user is entering commands other than "reset",
 * 	the function keeps taking input from the user.
 * The moment the command "reset" is entered, the game's field "isInSetting" is set to true,
 *  and the function setting_state is called.
 */
void game_state(ChessGame* game);

/**
 * the function calculates which is the current best move for the AI player, and then
 * it sets the best move as the AI's current move.
 */
void computer_play_console(ChessGame * game);

/**
 * Given a game and command, checks validity of command, and if valid,
 * performs the actions necessary according to this command.
 * Also prints any needed messages according to the situation.
 * Deals only with setting state commands
 * @param
 * game- given game to be modified according to the command
 * cmd- the command according to which the acrtions will be performed on the game.
 */
void handle_command_setting_state(ChessGame* game, Command *cmd);

/**
 * Given a game and command, checks validity of command, and if valid,
 * performs the actions necessary according to this command.
 * Also prints any needed messages according to the situation.
 * Deals only with game state commands
 * @param
 * game- given game to be modified according to the command
 * cmd- the command according to which the acrtions will be performed on the game.
 */
void handle_command_game_state(ChessGame* game, Command* cmd);



/*
 * prints specified message whenever the game enters setting state
 * note: by specified we mean the msg which the instructor asked us to print
 */
void printSettingState();
/*
 * prints specified message after game mode is set
 * @param mode - the game mode chosen by the user, can be either 1 or 2, for 1-player mode or 2-players mode
 */
void printGameModeSet(int mode);
/*
 * In case a wrong game mode is entered, the program prints a specified message
 */
void printWrongGameMode();

/*
 * prints a specified msg about the difficulty which the user chose
 * if the user asked for difficulty 5 and expert level is not supported, a specified msg is printed
 * if the user enters a difficulty which is not in range 1-5, another specified msg is printed
 *
 * @params
 * dif - the difficulty entered by user
 * supported - a boolean which tells if expert level is supported or not
 */
void printDifficulty(int dif, bool supported);

/*
 * Prints the current game settings to the console
 *
 * @params
 * mode - current game mode
 * dif - current difficulty of game
 * curr_player - current player (for printing the color of the player)
 */
void printSettings(int mode, int dif, int curr_player);

/*
 * If the user tries to save the game state and the specified file can't be created or modified,
 * a specified msg is printed
 */
void printFileCreationError();
/*
 * If in 2-player mode and the user to invoke the undo command, a specified msg is printed
 */
void printUndoUnavailable();

/*
 * If the user tries to invoke the undo command and the history is empty, a specified msg is printed
 */
void printEmptyHistory();

/*
 * In case the undo was successfully executed,
 * a specified msg about the previous two undone moves (one for each player) is printed
 * @params -
 * playerX , <x,y> and <w,z> represent the color of last player (black or white) to play,
 * the position of the piece after the last move executed and the original position of the piece.
 * similarly for playerY, <i,j> and <m,n>
 */
void printUndoneMoves(int playerX,int x, int y, int w, int z, int playerY, int i, int j, int m, int n);

/*
 *  Prints the computer's recently done move in a specified format
 *  @params -
 *  piece - containts the name of the piece
 *  <x,y> - original position
 *  <i,j> - new position
 */
void printComputerMove(char piece,int x, int y, int i, int j);



#endif /* MAINAUX_H_ */
