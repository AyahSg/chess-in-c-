/*
 * ChessSettingWindow.c
 *
 *  Created on: Sep 23, 2017
 *      Author: Ayah
 */
#include "ChessSettingWindow.h"
#include <stdio.h>

Widget** createSettingWindowWidgets(SDL_Renderer* renderer){

	if (renderer == NULL ) {
		return NULL ;
	}
	Widget** widgets = malloc(sizeof(Widget*) * 18); //can I?
	if (widgets == NULL ) {
		return NULL ;
	}
	SDL_Rect titleR = { .x = 225, .y = 50, .h = 100, .w = 350 };
	SDL_Rect backR = { .x = 275, .y = 520, .h = 50, .w = 125 };
	SDL_Rect nextR = { .x = 410, .y = 520, .h = 50, .w = 125 };
	SDL_Rect startR = { .x = 410, .y = 520, .h = 50, .w = 125 };
	SDL_Rect oneplayerR = { .x = 300, .y = 150+50, .h = 70, .w = 200 };
	SDL_Rect twoplayerR = { .x = 300, .y = 150+120, .h = 70, .w = 200 };
	SDL_Rect noobR = { .x = 300, .y = 150, .h = 70, .w = 200 };
	SDL_Rect easyR = { .x = 300, .y = 150+50, .h = 70, .w = 200 };
	SDL_Rect moderateR = { .x = 300, .y = 150+100, .h = 70, .w = 200 };
	SDL_Rect hardR = { .x = 300, .y = 150+150, .h = 70, .w = 200 };
	SDL_Rect expertR = { .x = 300, .y = 150+200, .h = 70, .w = 200 };
	SDL_Rect whiteR = { .x = 360, .y = 150, .h = 70, .w = 70 };
	SDL_Rect blackR = { .x = 360, .y = 150+100, .h = 70, .w = 70 };

	widgets[0] = createSimpleButton(renderer, &backR, "./images/back.bmp",CHESS_SETTING_WINDOW,BACK_BUTTON,1);
	widgets[1] = createSimpleButton(renderer, &startR, "./images/smallstart.bmp",CHESS_SETTING_WINDOW,START_BUTTON,1); //should not be shown;
	widgets[2] = createSimpleButton(renderer, &oneplayerR, "./images/1player.bmp",CHESS_SETTING_WINDOW,ONE_PLAYER_MODE_BUTTON,0);
	widgets[3] = createSimpleButton(renderer, &twoplayerR, "./images/2player.bmp",CHESS_SETTING_WINDOW,TWO_PLAYER_MODE_BUTTON,0);
	widgets[4] = createSimpleButton(renderer, &nextR, "./images/nextsmall.bmp",CHESS_SETTING_WINDOW,NEXT_DIFFICULTY_BUTTON,1);
	widgets[5] = createSimpleButton(renderer, &backR, "./images/back.bmp",CHESS_SETTING_WINDOW,BACK_TO_GAME_MODE_BUTTON,1);
	widgets[6] = createSimpleButton(renderer, &nextR, "./images/nextsmall.bmp",CHESS_SETTING_WINDOW,NEXT_COLOR_BUTTON,1);
	widgets[7] = createSimpleButton(renderer, &noobR, "./images/noob.bmp",CHESS_SETTING_WINDOW,NOOB_BUTTON,0);
	widgets[8] = createSimpleButton(renderer, &easyR, "./images/easy.bmp",CHESS_SETTING_WINDOW,EASY_BUTTON,0);
	widgets[9] = createSimpleButton(renderer, &moderateR, "./images/moderate.bmp",CHESS_SETTING_WINDOW,MODERATE_BUTTON,0);
	widgets[10] = createSimpleButton(renderer, &hardR, "./images/hard.bmp",CHESS_SETTING_WINDOW,HARD_BUTTON,0);
	widgets[11] = createSimpleButton(renderer, &expertR, "./images/expert.bmp",CHESS_SETTING_WINDOW,EXPERT_BUTTON,0);
	widgets[12] = createSimpleButton(renderer, &backR, "./images/back.bmp",CHESS_SETTING_WINDOW,BACK_TO_DIFFICULTY_BUTTON,1);
	widgets[13] = createSimpleButton(renderer, &whiteR, "./images/YellowK.bmp",CHESS_SETTING_WINDOW,WHITE_COLOR_BUTTON,0);
	widgets[14] = createSimpleButton(renderer, &blackR, "./images/BrownK.bmp",CHESS_SETTING_WINDOW,BLACK_COLOR_BUTTON,0);
	widgets[15] = createSimpleButton(renderer, &titleR, "./images/gamemode.bmp",CHESS_SETTING_WINDOW,NONE_BUTTON,0);
	widgets[16] = createSimpleButton(renderer, &titleR, "./images/difficulty.bmp",CHESS_SETTING_WINDOW,NONE_BUTTON,0);
	widgets[17] = createSimpleButton(renderer, &titleR, "./images/chooseyourcolor.bmp",CHESS_SETTING_WINDOW,NONE_BUTTON,0);

	for (int i=1;i<18;i++){
		if (i==2|| i==3 || i==4 || i==15) continue;
		SimpleButton* button = (SimpleButton*) widgets[i]->data;
		button->isShown=0;
	} //hiding the buttons that should not be shown at the beginning

	int b=0;
	for (int i=0; i<18;i++){
		if (widgets[i]==NULL){
			b=1; break;
		}
	}
	if (b==1){
		for (int i=0; i<18;i++){
			destroyWidget(widgets[i]);
		}
		free(widgets);
		printf("ERROR: couldn't create setting window widgets\n");
		return NULL;
	}
	return widgets;
}

SPWindow* createChessSettingWindow(){

	SPWindow* res = malloc(sizeof(SPWindow));
	ChessSettingWindow* data = malloc(sizeof(ChessSettingWindow));
	SDL_Window* window = SDL_CreateWindow("Chess Champion", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);
	Widget** widgets = createSettingWindowWidgets(renderer);

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
		//We first destroy the renderer
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		printf("couldn't create Board brown.bmp background surface\n");
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
		printf("couldn't create Board brown.bmp background texture\n");
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);

	data->numOfWidgets = 18;
	data->window = window;
	data->windowRenderer = renderer;
	data->widgets = widgets;
	data->bgTexture=texture;
	res->data = (void*) data;
	res->destroyWindow = destroyChessSettingWindow;
	res->drawWindow = drawChessSettingWindow;
	res->handleEventWindow = handleEventSettingWindow;
	res->hideWindow=hideSettingWindow;
	res->showWindow=showSettingWindow;
	return res;
}

void destroyChessSettingWindow(SPWindow* src){
	if (src == NULL ) {
		return;
	}
	ChessSettingWindow* data = (ChessSettingWindow*) src->data;
	int i = 0;
	for (; i < data->numOfWidgets; i++) {
		destroyWidget(data->widgets[i]);
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
void drawChessSettingWindow(SPWindow* src){
	if (src == NULL ) {
		return;
	}
	ChessSettingWindow* data = (ChessSettingWindow*) src->data;
	SDL_Rect bgR = {.h = 600, .w = 800 };
	SDL_Rect optionsR = {.x=275, .y=27, .h=600-50-4,.w=250};
	SDL_Rect outlineR = {.x=270, .y=27, .h=600-50-4,.w=250+10};
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

void hideSettingWindow (SPWindow* src){
	ChessSettingWindow* data = (ChessSettingWindow*)src->data;
	SDL_HideWindow(data->window);
}
void showSettingWindow (SPWindow* src){
	ChessSettingWindow* data = (ChessSettingWindow*)src->data;
	SDL_ShowWindow(data->window);
}
void showDifficultyWindowButtons(ChessSettingWindow* data){
	SimpleButton* butt;
	for (int i=0;i<data->numOfWidgets;i++){
		butt = (SimpleButton*) data->widgets[i]->data;
		if ((i>=0 && i<=4) || (i>=12&&i<=14)){
			butt->isActive=0; butt->isShown=0;
		}
		if (i>=5 && i<11){
			if (i==5 || i==6) butt->isActive=1;
			 butt->isShown=1;
		}
		if (i==15 || i==17){
			butt->isShown=0;
		}
		if (i==16){
			butt->isShown=1;
		}

	}
}
void showGameModeWindowButtons(ChessSettingWindow* data){
	SimpleButton* butt;
	for (int i=0;i<data->numOfWidgets;i++){
		butt = (SimpleButton*) data->widgets[i]->data;
		if (i>=0 && i<=4){
			if (i!=3 && i!=2) butt->isActive=1;
			butt->isShown=1;
		}
		if (i>=5 && i<=11){
			butt->isActive=0;
			 butt->isShown=0;
		}
		if (i==15){
			butt->isShown=1;
		}
		if (i==16){
			butt->isShown=0;
		}

	}
}
void showColorWindowButtons(ChessSettingWindow* data){
	SimpleButton* butt;
	for (int i=0;i<data->numOfWidgets;i++){
		butt = (SimpleButton*) data->widgets[i]->data;
		if ((i>=0 && i<=4 && i!=1) || i==15){
			continue;
		}
		if (i>=5 && i<=11){
			butt->isActive=0;
			 butt->isShown=0;
		}
		if ((i>=12 && i<=14) || i==1){
			if (i!=13 && i!=14) butt->isActive=1;
			 butt->isShown=1;
		}
		if (i==16){
			butt->isShown=0;
		}
		if (i==17){
			butt->isShown=1;
		}
	}
}
BUTTON_NAME handleEventSettingWindow(SPWindow* src, SDL_Event* event){
	BUTTON_NAME res=NONE_BUTTON;
	if(src == NULL || event==NULL){
		return NONE_BUTTON;
	}
	ChessSettingWindow* data = (ChessSettingWindow*)src->data;
	SimpleButton* butt = (SimpleButton*) data->widgets[0]->data; //always the back button
	int j=0; int b=0;
	for (; j<data->numOfWidgets;j++){
		butt = (SimpleButton*) data->widgets[j]->data;
		if (j==0 || j==1 || j==4 || j==5 || j==6 || j==12) continue; //no need to check the back and next and start buttons
		if (butt->isActive && butt->isShown){
			b=1;
			break;
		}  //now I know which other button is active, if no previous game slots were pressed, the button will remain the "load button"
	}
	if (b==0){ //need to return butt to be back button ..
		butt = (SimpleButton*) data->widgets[0]->data;
	}
	int i =0;
	for(;i<data->numOfWidgets;i++){
		res = data->widgets[i]->loadOrSettingHandleEvent(data->widgets[i],event,(void*) butt);
		if (res!=NONE_BUTTON){
			switch(res){
			case ONE_PLAYER_MODE_BUTTON:
				butt = (SimpleButton*) data->widgets[1]->data;
				if (butt->isShown==1){
					butt->isShown=0; butt->isActive=0;
				}
				butt = (SimpleButton*) data->widgets[4]->data; //the next_difficulty_button
				butt->isShown=1; butt->isActive=1;
				break; //no need to do something else because I already have the "next" butt active
			case TWO_PLAYER_MODE_BUTTON:
				//here I should "unshow" the next difficulty button and show the start button
				butt = (SimpleButton*) data->widgets[4]->data; //the next_difficulty_button
				butt->isActive=0; butt->isShown=0;
				butt=(SimpleButton*) data->widgets[1]->data; //the start button
				butt->isActive=1; butt->isShown=1;
				break;
			case BACK_BUTTON: //should then go back to the main window
				break;
			case START_BUTTON:
				break;
			case NEXT_DIFFICULTY_BUTTON: //now should hide the 5 buttons of the game mode and show the 8 of the difficulty
				showDifficultyWindowButtons(data);
				break;
			case BACK_TO_GAME_MODE_BUTTON:
				showGameModeWindowButtons(data);
				break;
			case NEXT_COLOR_BUTTON:
				showColorWindowButtons(data);
				break;
			case BACK_TO_DIFFICULTY_BUTTON:
				showDifficultyWindowButtons(data);
				break;
			default:
				break;
			}
			return res;
		}
	}
	return res;
}
