/*
 * ChessLoadWindow.c
 *
 *  Created on: Sep 23, 2017
 *      Author: Ayah
 */
#include "ChessLoadWindow.h"
#include <stdio.h>
#include <stdlib.h>

Widget** createLoadWindowWidgets(SDL_Renderer* renderer, int numberOfSavedGames) {
	if (renderer == NULL ) {
		return NULL ;
	}
	Widget** widgets = malloc(sizeof(Widget*) * (2+numberOfSavedGames));
	if (widgets == NULL ) {
		return NULL ;
	}
	SDL_Rect backR = { .x = 275, .y = 520, .h = 50, .w = 125 };
	SDL_Rect loadR = { .x = 410, .y = 520, .h = 50, .w = 125 };

	widgets[0] = createSimpleButton(renderer, &loadR, "./images/load.bmp",CHESS_LOAD_WINDOW,LOAD_BUTTON,0);
	widgets[1] = createSimpleButton(renderer, &backR, "./images/back.bmp",CHESS_LOAD_WINDOW,BACK_BUTTON,1);


	SDL_Rect game1R = { .x = 300, .y = 150, .h = 70, .w = 200 };
	SDL_Rect game2R = { .x = 300, .y = 150+50, .h = 70, .w = 200 };
	SDL_Rect game3R = { .x = 300, .y = 150+100, .h = 70, .w = 200 };
	SDL_Rect game4R = { .x = 300, .y = 150+150, .h = 70, .w = 200 };
	SDL_Rect game5R = { .x = 300, .y = 150+200, .h = 70, .w = 200 };
	switch(numberOfSavedGames){
	case 1:
		widgets[2] = createSimpleButton(renderer, &game1R, "./images/GameSlot1.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_1_BUTTON,0);
		break;
	case 2:
		widgets[2] = createSimpleButton(renderer, &game1R, "./images/GameSlot1.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_1_BUTTON,0);
		widgets[3] = createSimpleButton(renderer, &game2R, "./images/GameSlot2.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_2_BUTTON,0);
		break;
	case 3:
		widgets[2] = createSimpleButton(renderer, &game1R, "./images/GameSlot1.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_1_BUTTON,0);
		widgets[3] = createSimpleButton(renderer, &game2R, "./images/GameSlot2.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_2_BUTTON,0);
		widgets[4] = createSimpleButton(renderer, &game3R, "./images/GameSlot3.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_3_BUTTON,0);
		break;
	case 4:
		widgets[2] = createSimpleButton(renderer, &game1R, "./images/GameSlot1.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_1_BUTTON,0);
		widgets[3] = createSimpleButton(renderer, &game2R, "./images/GameSlot2.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_2_BUTTON,0);
		widgets[4] = createSimpleButton(renderer, &game3R, "./images/GameSlot3.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_3_BUTTON,0);
		widgets[5] = createSimpleButton(renderer, &game4R, "./images/GameSlot4.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_4_BUTTON,0);
		break;
	case 5:
		widgets[2] = createSimpleButton(renderer, &game1R, "./images/GameSlot1.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_1_BUTTON,0);
		widgets[3] = createSimpleButton(renderer, &game2R, "./images/GameSlot2.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_2_BUTTON,0);
		widgets[4] = createSimpleButton(renderer, &game3R, "./images/GameSlot3.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_3_BUTTON,0);
		widgets[5] = createSimpleButton(renderer, &game4R, "./images/GameSlot4.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_4_BUTTON,0);
		widgets[6] = createSimpleButton(renderer, &game5R, "./images/GameSlot5.bmp",CHESS_LOAD_WINDOW,GAME_SLOT_5_BUTTON,0);
		break;
	}
	int b=0;
	for (int i=0;i<numberOfSavedGames+2;i++){
		if (widgets[i]==NULL){
			destroyWidget(widgets[i]);
			b=1;
		}
	}
	if (b==1){
		for (int i=0;i<numberOfSavedGames+2;i++){ //need to destory the rest of the widgets
			if (widgets[i]!=NULL){
				destroyWidget(widgets[i]);
			}
		}
		free(widgets);
		printf("ERROR: couldn't create a widget in ChessLoadWindow\n"); fflush(stdout);
		return NULL;
	}
	return widgets;
}

SPWindow* createChessLoadWindow(int numberOfSavedGames) {
	SPWindow* res = malloc(sizeof(SPWindow));
	ChessLoadWindow* data = malloc(sizeof(ChessLoadWindow));
	SDL_Window* window = SDL_CreateWindow("Chess Champion", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);
	Widget** widgets = createLoadWindowWidgets(renderer,numberOfSavedGames);
	if (res == NULL || data == NULL || window == NULL || renderer == NULL
			|| widgets == NULL ) {
		free(res);
		free(data);
		free(widgets);
		//We first destroy the renderer
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		return NULL ;
	}
	SDL_Surface* loadingSurface = NULL;
	// insert background of window here !
	loadingSurface = SDL_LoadBMP("Board brown.bmp");
	if (loadingSurface == NULL ) {
		free(res);
		free(data);
		free(widgets);
		SDL_FreeSurface(loadingSurface);
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		printf("ERROR: couldn't create Board brown.bmp background surface\n");
		return NULL ;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
	if (texture == NULL ) {
		free(res);
		free(data);
		free(widgets);
		SDL_FreeSurface(loadingSurface);
		SDL_DestroyTexture(texture);
		//We first destroy the renderer
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		printf("ERROR: couldn't create Board brown.bmp background  texture\n");
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);
	data->widgets = widgets;
	data->numOfWidgets = 2+numberOfSavedGames;
	data->window = window;
	data->bgTexture = texture;
	data->windowRenderer = renderer;
	data->widgets = widgets;
	res->data = (void*) data;
	res->destroyWindow = destroyChessLoadWindow;
	res->drawWindow = drawChessLoadWindow;
	res->handleEventWindow = handleEventLoadWindow;
	res->hideWindow=hideLoadWindow;
	res->showWindow=showLoadWindow;
	return res;
}

void destroyChessLoadWindow(SPWindow* src) {
	if (src == NULL ) {
		return;
	}
	ChessLoadWindow* data = (ChessLoadWindow*) src->data;
	int i = 0;
	for (; i < data->numOfWidgets; i++) {
		destroyWidget(data->widgets[i]);//
	}
	free(data->widgets);
	if (data->bgTexture != NULL ) {
		SDL_DestroyTexture(data->bgTexture);
	}
	SDL_DestroyRenderer(data->windowRenderer);
	SDL_DestroyWindow(data->window);
	free(data);
	free(src);
}
void drawChessLoadWindow(SPWindow* src) {
	if (src == NULL ) {
		return;
	}
	ChessLoadWindow* data = (ChessLoadWindow*) src->data;
	SDL_Rect bgR = {.h = 600, .w = 800 };
	SDL_Rect optionsR = {.x=25+250, .y=27, .h=600-50-4,.w=250};
	SDL_Rect outlineR = {.x=20+250, .y=27, .h=600-50-4,.w=250+10};
	SDL_RenderCopy(data->windowRenderer, data->bgTexture, NULL, &bgR);
	SDL_SetRenderDrawColor(data->windowRenderer,204,204,204,255);
	SDL_RenderFillRect(data->windowRenderer, &outlineR);
	SDL_SetRenderDrawColor(data->windowRenderer,188,113,43,255);
	SDL_RenderFillRect(data->windowRenderer,&optionsR);
	int i = 0;
	for (; i < data->numOfWidgets; i++) {
		(data->widgets[i])->drawWidget(data->widgets[i]);
	}
	SDL_RenderPresent(data->windowRenderer);
}

BUTTON_NAME handleEventLoadWindow(SPWindow* src, SDL_Event* event){
	BUTTON_NAME res=NONE_BUTTON;
	if(src == NULL || event==NULL){
		return NONE_BUTTON;
	}
	ChessLoadWindow* data = (ChessLoadWindow*)src->data;
	SimpleButton* butt = (SimpleButton*) data->widgets[0]->data;
	int j=0; int b=0;
	for (; j<data->numOfWidgets;j++){
		if (j==0 || j==1) continue; //no need to check the back and load button
		butt = (SimpleButton*) data->widgets[j]->data;
		if (butt->isActive){
			b=1;
			break;
		}  //now I know which other button is active, if no previous game slots were pressed, the button will remain the "load button"
	}
	if (b==0){ //need to return butt to be load button ..
		butt = (SimpleButton*) data->widgets[0]->data;
	}
	int i =0;
	for(;i<data->numOfWidgets;i++){
		res = data->widgets[i]->loadOrSettingHandleEvent(data->widgets[i],event,(void*) butt);
		if (res!=NONE_BUTTON) return res;
	}
	return res;
}

void hideLoadWindow (SPWindow* src){
	ChessLoadWindow* data = (ChessLoadWindow*)src->data;
	SDL_HideWindow(data->window);
}

void showLoadWindow (SPWindow* src){
	ChessLoadWindow* data = (ChessLoadWindow*)src->data;
	SDL_ShowWindow(data->window);
}

