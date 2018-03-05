/*
 * setting.c
 *
 *  Created on: Aug 13, 2017
 *      Author: tala
 */


#include "setting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


ChessGame* GameCreate(int historySize){
	ChessGame* src = (ChessGame*)malloc(sizeof(ChessGame));
	if(!src){
		printf("ERROR: memory allocation fail in game creation\n");fflush(stdout);
		return NULL;
	}
	src->gameMode = GAME_MODE_1;
	src->isInSetting = true;
	src->gameDifficulty = 2;
	src->playerColor = WHITE_PLAYER_SYMBOL;
	src->currentPlayer = WHITE_PLAYER_SYMBOL;
	ChessArrayList* history=ChessArrayListCreate(historySize);
	ChessArrayList* Player1D=ChessArrayListCreate(historySize/2);
	ChessArrayList* Player2D=ChessArrayListCreate(historySize/2);

	if (!src || !history || historySize<=0 || !Player1D || !Player2D ){
		printf("ERROR: null pointer in game creation\n");fflush(stdout);
		return NULL;
	}
	src->historySize=historySize;
	src->movesHistory=history;
	src->Player1LastDestinations=Player1D;
	src->Player2LastDestinations=Player2D;
	initBoard(src);
	src->shouldGoToNextTurn=false;
	src->undoCountPerTurn=0;
	src->supported=false;
	return src;
}

ChessGame* GameCopy(ChessGame* src){
	if(!src){
		printf("ERROR: null pointer in game copying\n");fflush(stdout);
		return NULL;
	}
	ChessGame* copy = (ChessGame*)malloc(sizeof(ChessGame));
	if(!copy){
		printf("ERROR: null pointer in game copying\n");fflush(stdout);
		return NULL;
	}
	ChessArrayList* HistoryC = ChessArrayListCopy(src->movesHistory);
	ChessArrayList* Player1D=ChessArrayListCopy(src->Player1LastDestinations);
	ChessArrayList* Player2D=ChessArrayListCopy(src->Player2LastDestinations);
	if (!HistoryC || !Player1D || !Player2D){
		printf("ERROR: null pointer in game copying\n");fflush(stdout);
		return NULL;
	}
	copy->gameMode=src->gameMode;
	copy->isInSetting = src->isInSetting;
	copy->gameDifficulty = src->gameDifficulty;
	copy->playerColor = src->playerColor;
	copy->currentPlayer=src->currentPlayer;
	copy->shouldGoToNextTurn=src->shouldGoToNextTurn;
	copy->historySize=src->historySize;
	copy->supported=src->supported;
	copy->undoCountPerTurn=src->undoCountPerTurn;
	memcpy(copy->gameBoard,src->gameBoard,sizeof(src->gameBoard));
	copy->movesHistory=HistoryC;
	copy->Player1LastDestinations=Player1D;
	copy->Player2LastDestinations=Player2D;
	return copy;
}

void ClearGame(ChessGame* src){
	if(!src){
		printf("ERROR: null pointer in game clearing\n");fflush(stdout);
		return;
	}
	CHESS_ARRAY_LIST_MESSAGE msg1=ChessArrayListClear(src->movesHistory); //clears the moves history array
	CHESS_ARRAY_LIST_MESSAGE msg2=ChessArrayListClear(src->Player1LastDestinations);
	CHESS_ARRAY_LIST_MESSAGE msg3=ChessArrayListClear(src->Player2LastDestinations);
	if(msg1==CHESS_ARRAY_LIST_INVALID_ARGUMENT || msg2==CHESS_ARRAY_LIST_INVALID_ARGUMENT || msg3==CHESS_ARRAY_LIST_INVALID_ARGUMENT){
		printf("ERROR: null pointer in game clearing\n");fflush(stdout);
	}
	initBoard(src);
	defaultSettings(src);
}

void ClearGameWithoutChangingSetting(ChessGame* src){
	if(!src){
		printf("ERROR: null pointer in game clearing\n");fflush(stdout);
		return;
	}
	CHESS_ARRAY_LIST_MESSAGE msg1=ChessArrayListClear(src->movesHistory); //clears the moves history array
	CHESS_ARRAY_LIST_MESSAGE msg2=ChessArrayListClear(src->Player1LastDestinations);
	CHESS_ARRAY_LIST_MESSAGE msg3=ChessArrayListClear(src->Player2LastDestinations);
	if(msg1==CHESS_ARRAY_LIST_INVALID_ARGUMENT || msg2==CHESS_ARRAY_LIST_INVALID_ARGUMENT || msg3==CHESS_ARRAY_LIST_INVALID_ARGUMENT){
		printf("ERROR: null pointer in game clearing\n");fflush(stdout);
	}
	initBoard(src);
	src->undoCountPerTurn=0;
}

void GameDestory(ChessGame* src){
	if (!src)
		return;
	ChessArrayListDestroy(src->movesHistory);
	ChessArrayListDestroy(src->Player1LastDestinations);
	ChessArrayListDestroy(src->Player2LastDestinations);
	free(src);
}

void initBoard(ChessGame* src){
	if(!src){
		printf("ERROR: null pointer in gameboard initialization\n");fflush(stdout);
		return;
	}
	for (int i=0; i<ROWS;i++){
		for (int j=0; j<COLUMNS; j++){
			src->gameBoard[i][j] = EMPTY_ENTRY;
		}
	}
	src->gameBoard[7][0]=BLACK_ROOK;
	src->gameBoard[7][1]=BLACK_KNIGHT;
	src->gameBoard[7][2]=BLACK_BISHOP;
	src->gameBoard[7][3]=BLACK_QUEEN;
	src->gameBoard[7][4]=BLACK_KING;
	src->gameBoard[7][5]=BLACK_BISHOP;
	src->gameBoard[7][6]=BLACK_KNIGHT;
	src->gameBoard[7][7]=BLACK_ROOK;
	src->gameBoard[0][0]=WHITE_ROOK;
	src->gameBoard[0][1]=WHITE_KNIGHT;
	src->gameBoard[0][2]=WHITE_BISHOP;
	src->gameBoard[0][3]=WHITE_QUEEN;
	src->gameBoard[0][4]=WHITE_KING;
	src->gameBoard[0][5]=WHITE_BISHOP;
	src->gameBoard[0][6]=WHITE_KNIGHT;
	src->gameBoard[0][7]=WHITE_ROOK;
	for(int i=0;i<COLUMNS;i++){
		src->gameBoard[1][i]=WHITE_PAWN;
	}
	for(int i=0;i<COLUMNS;i++){
		src->gameBoard[ROWS-2][i]=BLACK_PAWN;
	}
}

GAME_MESSAGE SetMode(ChessGame* src, int mode){
	if( !src || ((mode!=GAME_MODE_1)&&(mode!=GAME_MODE_2))){
			return INVALID_ARGUMENT;
	}
	src->gameMode=mode;
	return GAME_SUCCESS;
}

int GetMode(ChessGame* src){
	if(!src){
		printf("ERROR: null pointer in GetMode function\n");fflush(stdout);
	}
	return src->gameMode;
}

GAME_MESSAGE SetDifficulty(ChessGame* src, int diff){
	if(!src || diff<MIN_DIFFICULTY || diff>MAX_DIFFICULTY){
		printf("ERROR: null pointer in SetDifficulty function\n");fflush(stdout);
		return INVALID_ARGUMENT;
	}
	src->gameDifficulty = diff;
	return GAME_SUCCESS;
}

int GetDifficulty(ChessGame* src){
	if(!src){
		printf("ERROR: null pointer in GetDifficulty function\n");fflush(stdout);
	}
	return src->gameDifficulty;
}

GAME_MESSAGE SetColor(ChessGame* src,int color){
	if(!src|| color <0 || color>1){
		printf("ERROR: null pointer in SetColor function\n");fflush(stdout);
		return INVALID_ARGUMENT;
	}
	src->playerColor = color;
	return GAME_SUCCESS;
}

int GetUserColor(ChessGame* src){
	if(!src){
		printf("ERROR: null pointer in GetUsetColor function\n");fflush(stdout);
	}
	return src->playerColor;
}

int GetCurrentPlayer(ChessGame* src){
	if(!src){
		printf("ERROR: null pointer in GetCurrentPlayer function\n");fflush(stdout);
	}
	return src->currentPlayer;
}

void ChangeCurrentPlayer(ChessGame* src){
	if(!src){
		printf("ERROR: null pointer in ChangeCurrentPlayer function\n");fflush(stdout);
		return;
	}
	if(src->currentPlayer == BLACK_PLAYER_SYMBOL){
		src->currentPlayer = WHITE_PLAYER_SYMBOL;
	}
	else{
		src->currentPlayer = BLACK_PLAYER_SYMBOL;
	}
}

void printBoard(ChessGame* src){
	if(!src){
		printf("ERROR: null pointer in printboard function\n");fflush(stdout);
		return;
	}
	for(int i=0;i<ROWS;i++){
		printf("%d| ",8-i);
		for(int j=0;j<COLUMNS;j++){
			printf("%c ",src->gameBoard[7-i][j]);
		}
		printf("|\n");
	}
	printf("  ");
	for(int i=0; i<17;i++){
		printf("%c",DASH);
	}
	printf("\n   ");
	for(int j=0;j<COLUMNS-1;j++){
		printf("%c ",translateIntToChar2(j));
	}
	printf("%c",translateIntToChar2(COLUMNS-1));
	printf("\n");
}


char translateIntToChar2(int i){
	char res=65+i;
	return res;
}

void defaultSettings(ChessGame* src){
		if(!src){
			printf("ERROR: null pointer in defaultSettings function\n");fflush(stdout);
			return;
		}
		src->gameMode = GAME_MODE_1;
		src->isInSetting = true;
		src->gameDifficulty = 2;
		src->playerColor = WHITE_PLAYER_SYMBOL;
		src->currentPlayer = WHITE_PLAYER_SYMBOL;
		src->shouldGoToNextTurn=0;
		src->undoCountPerTurn=0;
}
