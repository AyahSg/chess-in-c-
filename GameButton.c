/*
 * GameButton.c
 *
 *  Created on: Sep 24, 2017
 *      Author: Ayah
 */

#include "GameButton.h"
#include "SPCommon.h"
#include <stdio.h>

void updateWidgetLocation(GameWidget* src,int x, int y){
	GameButton* button = (GameButton*) src->data;
	button->location->x=x;
	button->location->y=y;
	button->originalLocation->x=x;
	button->originalLocation->y=y;
}

GameWidget* createGameButton(SDL_Renderer* windowRender, SDL_Rect* location,
		const char* image,GAME_BUTTON buttonName,int isActive){
	if (windowRender == NULL || location == NULL || image == NULL ) {
		return NULL ;
	}
	//Allocate data
	GameWidget* res = (GameWidget*) malloc(sizeof(GameWidget));
	GameButton* data = (GameButton*) malloc(sizeof(GameButton));
	SDL_Surface* loadingSurface = SDL_LoadBMP(image);
	SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(windowRender,
			loadingSurface);
	if (res == NULL || data == NULL || loadingSurface == NULL
			|| buttonTexture == NULL) {
		free(res);
		free(data);
		SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
		SDL_DestroyTexture(buttonTexture); ////It is safe to pass NULL
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	data->buttonTexture = buttonTexture;
	data->location = spCopyRect(location);
	data->originalLocation= spCopyRect(location);
	data->windowRenderer = windowRender;
	data->isActive=isActive;
	data->buttonName=buttonName;
	data->xDrag=0;
	data->yDrag=0;
	data->xClick=0;
	data->yClick=0;
	data->isShown=1;
	res->destroyGameWidget = destroyGameButton;
	res->drawGameWidget = drawGameButton;
	res->handleEvent=handleGameButtonEvent;
	res->isDragged=0;
	res->data = data;
	return res;
}

void destroyGameButton(GameWidget* src){
	if (src == NULL ) {
		return;
	}
	GameButton* castData = (GameButton*) src->data;
	free(castData->location);
	free(castData->originalLocation);
	SDL_DestroyTexture(castData->buttonTexture);
	free(castData);
	free(src);
}

int buttonIsNotFromPanel(GameButton* button){
	GAME_BUTTON name = button->buttonName;
	if (name==RESTART_BUTTON || name==UNDO_BUTTON || name==LOAD_GAME_BUTTON
			|| name == SAVE_BUTTON || name==MAIN_MENU_BUTTON || name==EXIT_GAME_BUTTON
			|| name==CURRENT_TURN_BLACK || name==CURRENT_TURN_WHITE){
		return 0;
	}
	return 1;
}

GAME_BUTTON handleGameButtonEvent(GameWidget* src, SDL_Event* event,GameWidget* lastUsed, int isUserInputBlocked){
	if (src == NULL || event == NULL ) {
		return NONE_GAME_BUTTON; //Better to return an error value
	}
	if (event->type == SDL_WINDOWEVENT) {
		if (event->window.event == SDL_WINDOWEVENT_CLOSE){
			return X_GAME_BUTTON;
		}
	}
	if (isUserInputBlocked) return NONE_GAME_BUTTON; //we don't want to handle events while the computer's playing
	GameButton* castData = (GameButton*) src->data;
	if (!castData->isShown) return NONE_GAME_BUTTON; //we don't want to handle events of a hidden piece
	if (lastUsed!=NULL  && event->type != SDL_MOUSEBUTTONUP ){
		if (lastUsed->isDragged){
			GameButton* lastButton = (GameButton*) lastUsed->data;
			lastButton->location->x=event->motion.x-lastButton->xDrag;
			lastButton->location->y=event->motion.y-lastButton->yDrag;
			return DRAGGED_PIECE; //in other words: there's a piece being dragged and here's the location
		}
	}
	if (event->type == SDL_MOUSEBUTTONUP) {
		SDL_Point point;
		point.x = event->button.x;
		point.y = event->button.y;
		if (lastUsed!=NULL && lastUsed->isDragged){
			GameButton* button=(GameButton*) lastUsed->data;
			if (point.x==button->xClick && point.y==button->yClick){
				lastUsed->isDragged=0; //if it was a simple click, then need to turn drag mode off
			}
		}
		if (lastUsed!=NULL && lastUsed->isDragged){
				lastUsed->isDragged=0;
				GameButton* button=(GameButton*) lastUsed->data;
				button->location->x=point.x;
				button->location->y=point.y;
				return DROPPED_PIECE;
				//So.. by now we know the piece that was dragged
				//we know where it was and we know where it is
				//so, before it stays there, we need to make sure that the move is valid.
				//otherwise, it'll have to go back to its original place, this will be handled in game window handle function
		}
		if (SDL_PointInRect(&point, castData->location)) {
			GAME_BUTTON name = castData->buttonName;
			if (name==RESTART_BUTTON || name==SAVE_BUTTON || name==LOAD_GAME_BUTTON)
				return name;
			else if ((name==EXIT_GAME_BUTTON || name == MAIN_MENU_BUTTON)){
				if (lastUsed!=NULL){
					GameButton* lastUsedB=(GameButton*) lastUsed->data;
					if (lastUsedB->buttonName==SAVE_BUTTON) {
						return name;
					}
				}
				SDL_MessageBoxData data; SDL_MessageBoxButtonData buttons[2];
				data.title=":(";
				data.message="Are you sure you wan't to leave without saving?";
				data.numbuttons=2;
				buttons[0].buttonid=0; buttons[0].text="No";
				buttons[1].buttonid=1; buttons[1].text="Yes";
				data.buttons=buttons;
				int id; SDL_ShowMessageBox(&data,&id);
				if (id==1) return name;
				if (id==0) return NONE_GAME_BUTTON;
			}
			else if (name==UNDO_BUTTON && castData->isActive){
				return name;
			}
			else if (name==UNDO_BUTTON && !(castData->isActive)) {
				return NONE_GAME_BUTTON;
			}
			else{ //else it means that a piece was chosen! so now we need to see where it goes..
				return name;
			}
			}
	}
	else
	{	if (event->button.state==SDL_PRESSED ){
			if (lastUsed==NULL){
				return NONE_GAME_BUTTON;
			}
			GameButton* lastUsedB=(GameButton*)lastUsed->data;
			SDL_Point point;
			point.x = event->button.x;
			point.y = event->button.y;
			if (SDL_PointInRect(&point, lastUsedB->location) && buttonIsNotFromPanel(lastUsedB)){
				lastUsed->isDragged=1;
				lastUsedB->xDrag=point.x-lastUsedB->location->x;
				lastUsedB->yDrag=point.y-lastUsedB->location->y;
				lastUsedB->xClick=point.x;
				lastUsedB->yClick=point.y;
			}
		}
	}
	return NONE_GAME_BUTTON;
}

void drawGameButton(GameWidget* src){
	if (src == NULL ) {
		return;
	}
	GameButton* castData = (GameButton*) src->data;
	if (castData->isActive){
		SDL_SetRenderDrawColor(castData->windowRenderer,221,142,68,255);
		SDL_RenderFillRect(castData->windowRenderer,castData->location);
	}
	if (!castData->isShown) return;
	SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,
			castData->location);
}



