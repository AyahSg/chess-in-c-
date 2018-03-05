/*
 * savedGames.h
 *
 *  Created on: Aug 23, 2017
 *      Author: Ayah
 */

#ifndef SAVEDGAMES_H_
#define SAVEDGAMES_H_

#include <stdio.h>
#include <stdlib.h>
//#include "game.h"
#include "setting.h"
#define GAME_SLOTS 5

/*
 * a type used to represent messages about files creation and loading and other relevant features.
 */
typedef enum file_message_t {
	FILE_ERROR,
	FILE_SUCCESS,
	EXPERT_NOT_SUPPORTED,
} FILE_MSG;



/**
 * Saves the current game state to the file specified by its relative or full path
 * If the file cannot be created or modified, the function announces this and does nothing else.
 *
 * @param
 * src - the source game to be saved.
 * filepath - file relative or full path , where the game state will be saved.
 *
 * @return
 * FILE_ERROR - If the file cannot be created or modified,
 * FILE_SUCCESS - otherwise.
 */
FILE_MSG save(ChessGame * src , char* filepath);

/*
 * This function is used for GUI. 
 * It returns the number of currently saved games in the directory by scanning the pre allocated files for the 5 game slots,
 * if a file doesn't exist it creates it and doesn't increment the counter, 
 * if it exists it counts the number of words in it (by calling to fsize).
 */
int numOfSavedGames();

/**
 * Updates the array which contains the saved games filepaths
 * @param
 * cnt- updated number of saved games in a game
 */
void updateSavedSlots(int cnt);

/**
 * Copies the contents of the file with the filepath saved in "from"
 * to the file file with the filepath saved in "to"
 * @params
 * from - filepath of the file which will be copied from
 * to - filepath of the file which will be copied to
 *
 * @return
 * FILE_ERROR - if file can't be opened or modified
 * FILE_SUCCESS - otherwise
 *
 */
FILE_MSG fileCopy(char* from, char* to);

/*
 * Creates an XML file which contains the current game setting and writes it to file.
 * @params
 * src - the source game which will be saved
 * file - the file which will be written to
 */
void createXML(ChessGame* src, FILE* file);

/*
 * Returns the size of a file
 * @params
 * file - the file whose size will be returned
 * @return
 * size of the file
 */
long fsize(FILE * file);

/*
 * Parses an xml file which contains information about a previously saved game
 * and updates the game's setting and the gameboard according to the info from ifp file.
 * @params
 * src - the game which will be modified and updated
 * ifp - the xml file which will be parsed
 */
void XMLparser(ChessGame *src, FILE* ifp);

/*
 * Reads input about pieces from a given raw and updates the gameboard of the source game
 * @params
 * index - index of row, in range 0-7
 * rowInfo - char array which includes the info about the pieces
 * src - the game source whose gameboard will be modified
 */
void getInfoFromRowI(int index,char *rowInfo,ChessGame * src);

/**
 * same as function save that is used for gui.
 * this function is used in console mode, as we take the filepath string as an input from user.
 * assumption: the user enters the filepath with the extension "xml"
 */
FILE_MSG consoleSave(ChessGame * src , char* filepath);

/*
 * Loads the game setting from a file, using xmlParser
 * @params
 * src - the source game which will be updated according to the settings in file in filepath
 * filepath - the filepath of the file which includes the data of the game setting
 *
 * @return
 * FILE_ERROR - if file can't be opened
 * FILE_SUCCESS - otherwise
 */
FILE_MSG load (ChessGame* src, char* filepath);


/*
 * if the user tries to load a game with difficulty 5, and current game
 * doesn’t support this difficulty then a specified error should be printed
 */
void printExpertLevelNotSupportedInLoad();

/*
 * If the user tries to load a game and the file doesn't open, a specified error msg is printed
 */
void printFileLoadError();

#endif /* SAVEDGAMES_H_ */
