/*
 * cmdparser.h
 *
 *  Created on: Aug 13, 2017
 *      Author: tala
 */

#ifndef CMDPARSER_H_
#define CMDPARSER_H_


#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024

/* a type used to represent a command taken by user inpu:
*  both state game commands and setting state commands
*/
typedef enum {
	GAME_MODE,
	DIFFICULTY,
	USER_COLOR,
	LOAD,
	DEFAULT,
	PRINT_SETTING,
	QUIT,
	START,
	MOVE,
	GET_MOVES,
	SAVE,
	UNDO,
	RESET,
	CASTLE,
	INVALID_COMMAND,
} SP_COMMAND;


/* Command:
 * a new type that is used to encapsulate a parsed line
 * fields:
 * cmd- enum used to hold the name of the command as could be entered by user
 * thereIsAnArg-is set to true if there's an argument in user's input
 * arg-the argument taken from user's input
 * fromX,fromY,toI,toJ - when parsing a command "move <x,y> to <i,j>" or "get_moves <x,y>" from user, these fields save the coordinates accordingly
 * ToisValid- an index set to true if the word "to" was inserted correctly in user input
 * filepath- a string containing whatever comes after the first word in user input. it is relevant in the "save" and "load" commands taken by user
 */
typedef struct command_t {
	SP_COMMAND cmd;
	bool thereIsAnArg;
	int arg;
	int fromX;
	int fromY;
	int toI;
	int toJ;
	int TOisValid; //in case the command is move <x,y> to <i,j> then this is an indicator of validity of word "to"
	char* filepath;
} Command;



/**
 * creates a new Command and initializes its fields to default.
 */
Command* createCommand();


/**
 * Parses a specified line.
 * @return
 * A parsed line such that:
 * cmd - a SP_COMMAND type containing the name of the command.
 * 		 can have the value of {GAME_MODE,START,UNDO,etc}
 * arg - the integer argument in case thereIsAnArg is set to true
 * fromX - relative only the following commands: { move <x,y> to <i,j>, get_moves <x,y>, castle <x,y> }
 * 		saves the x integer coordinate given by user.
 * fromY - relative only the following commands: { move <x,y> to <i,j>, get_moves <x,y>, castle <x,y> }
 * 		saves the parsed int value of the y character coordinate given by user.
 * 		for example if y=='A' then fromY==0, if y=='C' then fromY=='2'
 * toI - relative only the command move <x,y> to <i,j>
 * 		saves the i coordinate given by the user.
 * toJ - relative only the command move <x,y> to <i,j>
 * 		saves the parsed int value of the j character coordinate given by user.
 * 		for example if j=='A' then toJ==0, if j=='C' then toJ=='2'
 * TOisValid - boolean indicator set to true iff (cmd==MOVE && the word "to" was typed properly)
 * 				purpose: to recognize a correct command in the format move <x,y> to <i,j>
 */
Command* ParseLine(char* str);

/**
 * checks if given number is a valid index (0-7)
 * @param
 * i - the given index
 * @return
 * true- if 0<i<7
 * false- otherwise
 */
bool notInRange(int i);

/**
 *
 * checks if the passed string is a decimal digit character.
 * @param
 * str -  string to be checked
 * @return
 * true- if str is a decimal digit character
 * false- othewise
 */
bool ParserIsInt(char* str);

/**
 * 	given a pointer to Command struct cmd, sets its fields with the following defaullt values:
 * 	cmd->TOisValid=false;
	cmd->arg=-1;
	cmd->cmd=INVALID_COMMAND;
	cmd->fromX=-1;
	cmd->fromY=-1;
	cmd->thereIsAnArg=false;
	cmd->toI=-1;
	cmd->toJ=-1;
 */
void initialize(Command *cmd);

/**
 * parses a given string. compares between given string and possible commands options
 * @param
 * pch - a string
 * @return
 * one of the possible commands of the type SP_COMMAND, according to the given string.
 */
SP_COMMAND getCommand(char *pch);

/**
 * translates decimal number digit to character representing that digit, 0 goes to '0', 7 goes to '7'
 * @param
 * i-decimal digit
 * @return
 * a character that has the specified ascii value
 */
char translateIntToChar(int i);

/**
 * translates character digit to a decimal integer according to the game's indices as follows:
 * 'A' goes to 0, 'B' goes to 1, 'C' goes to 2, 'D' goes to 3 and so on.
 */
int translateCharToInt(char c);


/**
 * frees the command's field "filepath" if not null, and then frees the command cmd if it's not null
 */
void destroyCommand(Command* cmd);

#endif /* CMDPARSER_H_ */
