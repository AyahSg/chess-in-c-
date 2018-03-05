/*
 * main.c
 *
 *  Created on: Sep 22, 2017
 *      Author: Ayah
 */
#include "game.h"
#include "setting.h"
#include "mainAux.h"
#include "ChessGUIManager.h"
#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>
#define HISTORY_SIZE 6

int main(int argc, char *argv[]){
	if (argc==0){
		printf("no args are provided");
		return 0;
	}
	ChessGame * game = GameCreate(HISTORY_SIZE);
	if (!game){
	 printf("ERROR: game cannot be created"); fflush(stdout);
	}
	if(argc==1 || (argc==2 && strcmp(argv[1],"-c")==0) ){
		setting_state(game);
		if(game!=NULL){
			GameDestory(game);
		}

	}
	else if(strcmp(argv[1],"-g")==0){
		if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
			printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
			return 1;
		}
		ChessGuiManager* manager = chessManagerCreate(game);
		if (manager == NULL ) {
			SDL_Quit();
			return 0;
		}
		SDL_Event event;
		while (1) {
			SDL_WaitEvent(&event);
			if (chessManagerHandleEvent(manager, &event) == CHESS_MANAGER_QUIT) {
				break;
			}
			chessManagerDraw(manager);
		}
		chessManagerDestroy(manager);
		SDL_Quit();
	}
	return 0;
}


