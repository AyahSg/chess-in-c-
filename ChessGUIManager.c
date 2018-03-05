/*
 * ChessGUIManager.c
 *
 *  Created on: Sep 22, 2017
 *      Author: Ayah
 */

#include <stdio.h>
#include <stdlib.h>
#include "ChessGUIManager.h"


ChessGuiManager* chessManagerCreate(ChessGame* game){
	ChessGuiManager* res = (ChessGuiManager*) malloc(sizeof(ChessGuiManager));
	if (res == NULL ) {
		printf("ERROR: can't create chessGUIManager\n");fflush(stdout);
		return NULL ;
	}
	res->mainWin = createChessMainWindow();
	if (res->mainWin == NULL ) {
		printf("ERROR: can't create main window\n");fflush(stdout);
		free(res);
		return NULL ;
	}
	res->settingWin=NULL;
	res->loadWin=NULL;
	res->gameWin=NULL;
	res->game=game;
	res->activeWin = CHESS_MAIN_WINDOW_ACTIVE;
	return res;
}

void chessManagerDestroy(ChessGuiManager* src){
	if (!src) {
		return;
	}
	GameDestory(src->game);
	if (src->gameWin!=NULL) destroyChessGameWindow(src->gameWin);
	if (src->settingWin!=NULL) src->settingWin->destroyWindow(src->settingWin);
	if (src->loadWin!=NULL) src->loadWin->destroyWindow(src->loadWin);
	if (src->mainWin!=NULL) src->mainWin->destroyWindow(src->mainWin);
	free(src);
}

void chessManagerDraw(ChessGuiManager* src){
	if (!src) {
		return;
	}
	if (src->activeWin == CHESS_MAIN_WINDOW_ACTIVE) {
		src->mainWin->drawWindow(src->mainWin);
	} else if (src->activeWin==CHESS_GAME_WINDOW_ACTIVE) {
		drawChessGameWindow(src->gameWin);
	} else if (src->activeWin==CHESS_SETTING_WINDOW_ACTIVE){
		src->settingWin->drawWindow(src->settingWin);
	} else if (src->activeWin==CHESS_LOAD_WINDOW_ACTIVE || src->activeWin==CHESS_LOAD_FROM_GAME_WINDOW){
		src->loadWin->drawWindow(src->loadWin);
	}
}

CHESS_MANAGER_EVENT handleManagerDueToMainEvent(ChessGuiManager* src, BUTTON_NAME event) {
	if (src == NULL ) {
		return CHESS_MANAGER_NONE;
	}
	if (event == START_BUTTON) {
		src->mainWin->hideWindow(src->mainWin);
		src->settingWin=createChessSettingWindow();
		if (src->settingWin == NULL ) {
			printf("ERROR: Couldn't create setting window\n"); fflush(stdout);
			return CHESS_MANAGER_QUIT;
		}
		src->activeWin=CHESS_SETTING_WINDOW_ACTIVE;
	}
		else if (event == LOAD_BUTTON){
		src->mainWin->hideWindow(src->mainWin);
		if (src->loadWin==NULL){
			int i = numOfSavedGames();
			src->loadWin=createChessLoadWindow(i);
			if (src->loadWin==NULL){
				printf("ERROR: Couldn't create load window\n"); fflush(stdout);
				return CHESS_MANAGER_QUIT;
			}
		}
		else{
			src->loadWin->showWindow(src->loadWin);
		}
		src->activeWin = CHESS_LOAD_WINDOW_ACTIVE;
	}
		else if (event == EXIT_BUTTON) {
		return CHESS_MANAGER_QUIT;
	}
		else if (event==X_BUTTON){
			return CHESS_MANAGER_QUIT;
		}
	return CHESS_MANAGER_NONE;
}

CHESS_MANAGER_EVENT handleManagerDueToSettingEvent (ChessGuiManager* src, BUTTON_NAME event){
	switch (event){
	case X_BUTTON:
		return CHESS_MANAGER_QUIT;
	case BACK_BUTTON:
		src->settingWin->hideWindow(src->settingWin);
		src->mainWin->showWindow(src->mainWin);
		src->activeWin = CHESS_MAIN_WINDOW_ACTIVE;
		break;
	case ONE_PLAYER_MODE_BUTTON:
		SetMode(src->game,GAME_MODE_1);
		break;
	case TWO_PLAYER_MODE_BUTTON:
		SetMode(src->game,GAME_MODE_2);
		break;
	case START_BUTTON:
		src->settingWin->hideWindow(src->settingWin);
		if (src->gameWin==NULL){
			src->gameWin=createChessGameWindow(src->game);
			if (src->gameWin == NULL ) {
				printf("ERROR: Couldn't create game window\n"); fflush(stdout);
				return CHESS_MANAGER_QUIT;
			}
		}
		else {
			destroyChessGameWindow(src->gameWin);
			src->gameWin=createChessGameWindow(src->game);
			showGameWindow(src->gameWin);
		}
		src->activeWin=CHESS_GAME_WINDOW_ACTIVE;
		break;
	case NOOB_BUTTON:
		SetDifficulty(src->game,1);
		break;
	case EASY_BUTTON:
		SetDifficulty(src->game,2);
		break;
	case MODERATE_BUTTON:
		SetDifficulty(src->game,3);
		break;
	case HARD_BUTTON:
		SetDifficulty(src->game,4);
		break;
	case WHITE_COLOR_BUTTON:
		SetColor(src->game,WHITE_PLAYER_SYMBOL);
		break;
	case BLACK_COLOR_BUTTON:
		SetColor(src->game,BLACK_PLAYER_SYMBOL);
		break;
	default:
		break;
	}
	return CHESS_MANAGER_NONE;
}
CHESS_MANAGER_EVENT showMsgBoxForExpertNotSupported(){
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Error!","Can't load game, expert level not supported",NULL);
	return CHESS_MANAGER_NONE;
}

CHESS_MANAGER_EVENT handleManagerDueToLoadEvent(ChessGuiManager* src, BUTTON_NAME event){
	FILE_MSG res;
	switch(event){
	case X_BUTTON:
		return CHESS_MANAGER_QUIT;
	case BACK_BUTTON:
		src->loadWin->hideWindow(src->loadWin);
		src->mainWin->showWindow(src->mainWin);
		src->activeWin=CHESS_MAIN_WINDOW_ACTIVE;
		return CHESS_MANAGER_NONE;
	case LOAD_BUTTON:
		return CHESS_MANAGER_NONE;
	case NONE_BUTTON:
		return CHESS_MANAGER_NONE;
	case GAME_SLOT_1_BUTTON:
		res = load(src->game,"0.xml");
		if (res==EXPERT_NOT_SUPPORTED){
			return showMsgBoxForExpertNotSupported();
		}
		break;
	case GAME_SLOT_2_BUTTON:
		 res =load(src->game,"1.xml");
		if (res==EXPERT_NOT_SUPPORTED){
			return showMsgBoxForExpertNotSupported();
		}
		break;
	case GAME_SLOT_3_BUTTON:
		 res =load(src->game,"2.xml");
		if (res==EXPERT_NOT_SUPPORTED){
			return showMsgBoxForExpertNotSupported();
		}
		break;
	case GAME_SLOT_4_BUTTON:
		 res =load(src->game,"3.xml");
		if (res==EXPERT_NOT_SUPPORTED){
			return showMsgBoxForExpertNotSupported();
		}
		break;
	case GAME_SLOT_5_BUTTON:
		 res =load(src->game,"4.xml");
		if (res==EXPERT_NOT_SUPPORTED){
			return showMsgBoxForExpertNotSupported();
		}
		break;
	default:
		return CHESS_MANAGER_NONE;
	} //if we get here then it's definitely a case where a game should be loaded
		if (src->gameWin!=NULL) {
			destroyChessGameWindow(src->gameWin); //we need to destroy so that it updates the game win right
			src->gameWin=NULL;
		}
		src->gameWin=createChessGameWindow(src->game);
		if (src->gameWin == NULL ) {
			printf("ERROR: Couldn't create game window\n"); fflush(stdout);
			return CHESS_MANAGER_QUIT;
		}
		src->loadWin->destroyWindow(src->loadWin);
		src->loadWin=NULL;
		src->activeWin=CHESS_GAME_WINDOW_ACTIVE;
	return CHESS_MANAGER_NONE;
}

CHESS_MANAGER_EVENT handleManagerDueToLoadFromGameWinEvent(ChessGuiManager* src, BUTTON_NAME event){
	if (event!=BACK_BUTTON){
		return handleManagerDueToLoadEvent(src,event);
	}
	else {
		src->loadWin->hideWindow(src->loadWin);
		showGameWindow(src->gameWin);
		src->activeWin=CHESS_GAME_WINDOW_ACTIVE;
	}
	return CHESS_MANAGER_NONE;
}

CHESS_MANAGER_EVENT handleManagerDueToGameEvent(ChessGuiManager* src, GAME_BUTTON event){
	if (event==X_GAME_BUTTON||event==EXIT_GAME_BUTTON) return CHESS_MANAGER_QUIT;
	else if (event==LOAD_GAME_BUTTON){
		if (!src->loadWin){
			int num=numOfSavedGames();
			src->loadWin=createChessLoadWindow(num);
		}
		else {
			src->loadWin->showWindow(src->loadWin);
		}
		hideGameWindow(src->gameWin);
		src->activeWin=CHESS_LOAD_FROM_GAME_WINDOW;
	}
	else if (event==MAIN_MENU_BUTTON){
		destroyChessGameWindow(src->gameWin);
		ClearGame(src->game);
		src->gameWin=NULL;
		src->mainWin->showWindow(src->mainWin);
		src->activeWin=CHESS_MAIN_WINDOW_ACTIVE;
	}
	else if (event==GAME_CHECK){
		if (GetCurrentPlayer(src->gameWin->ChessGame)==WHITE_PLAYER_SYMBOL){
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"CHECK","Check: white King is threatened!",NULL);
		}
		else{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"CHECK","Check: black King is threatened!",NULL);
		}
	}
	else if (event==GAME_CHECKMATE || event==GAME_TIE) {
		if (event==GAME_CHECKMATE){
			const char* whiteWon = "Checkmate! white player wins the game";
			const char* blackWon = "Checkmate! black player wins the game";
			const char* res;
			if (GetCurrentPlayer(src->gameWin->ChessGame)==WHITE_PLAYER_SYMBOL){
				res=whiteWon;
			}
			else{
				res=blackWon;
			}
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,"Game Over!",res,NULL);
		}
		else {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,"Game Over!","The Game ends in a tie..",NULL);
		}
		destroyChessGameWindow(src->gameWin);
		src->gameWin=NULL;
		ClearGame(src->game);
		src->activeWin=CHESS_MAIN_WINDOW_ACTIVE;
		src->mainWin->showWindow(src->mainWin);
	}

	return CHESS_MANAGER_NONE;
}

CHESS_MANAGER_EVENT chessManagerHandleEvent(ChessGuiManager* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		return CHESS_MANAGER_NONE;
	}
	if (src->activeWin == CHESS_MAIN_WINDOW_ACTIVE) {
		BUTTON_NAME mainEvent = src->mainWin->handleEventWindow(src->mainWin, event);
		return handleManagerDueToMainEvent(src, mainEvent);
	} else if (src->activeWin==CHESS_GAME_WINDOW_ACTIVE) {
		GAME_BUTTON gameEvent = handleEventGameWindow(src->gameWin, event);
		return handleManagerDueToGameEvent(src, gameEvent);
	} else if (src->activeWin==CHESS_LOAD_WINDOW_ACTIVE){
		BUTTON_NAME loadEvent = src->loadWin->handleEventWindow(src->loadWin,event);
		return handleManagerDueToLoadEvent(src, loadEvent);
	} else if (src->activeWin==CHESS_LOAD_FROM_GAME_WINDOW){
		BUTTON_NAME loadEvent = src->loadWin->handleEventWindow(src->loadWin,event);
		return handleManagerDueToLoadFromGameWinEvent(src, loadEvent);
	} else if (src->activeWin==CHESS_SETTING_WINDOW_ACTIVE){
		BUTTON_NAME settingEvent = src->settingWin->handleEventWindow(src->settingWin, event);
		return handleManagerDueToSettingEvent(src, settingEvent);
	}
	return CHESS_MANAGER_NONE;
}



