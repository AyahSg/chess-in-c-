#include <stdio.h>
#include <stdlib.h>
#include "SimpleButton.h"
#include "SPCommon.h"

Widget* createSimpleButton(SDL_Renderer* windowRender, SDL_Rect* location,
		const char* image,WINDOW_NAME windowName, BUTTON_NAME buttonName, int isActive) {
	if (windowRender == NULL || location == NULL || image == NULL ) {
		return NULL ;
	}
	//Allocate data
	Widget* res = (Widget*) malloc(sizeof(Widget));
	SimpleButton* data = (SimpleButton*) malloc(sizeof(SimpleButton));
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
	data->windowRenderer = windowRender;
	data->isActive=isActive;
	data->isShown=1; //by default, if a button shouldn't be shown I'll handle externally
	data->buttonName=buttonName;
	data->windowName=windowName;
	res->destroyWidget = destroySimpleButton;
	res->drawWidget = drawSimpleButton;
	if (windowName==CHESS_LOAD_WINDOW || windowName==CHESS_SETTING_WINDOW)res->loadOrSettingHandleEvent = handleButtonEventInLoadOrSettingWin;
	else res->handleEvent=handleSimpleButtonEvenet; //for main window
	res->hideWidget=hideButton;
	res->showWidget=showButton;
	res->data = data;
	return res;
}

void destroySimpleButton(Widget* src) {
	if (src == NULL ) {
		return;
	}
	SimpleButton* castData = (SimpleButton*) src->data;
	free(castData->location);
	SDL_DestroyTexture(castData->buttonTexture);
	free(castData);
	free(src);
}

BUTTON_NAME handleButtonEventInMainWin (Widget* src, SDL_Event* event){
	SimpleButton* castData = (SimpleButton*) src->data;
	if (event->type == SDL_MOUSEBUTTONUP) {
		SDL_Point point;
		point.x = event->button.x;
		point.y = event->button.y;
		if (SDL_PointInRect(&point, castData->location)) { //if a button was clicked, I want to know which one it is so that I handle the event accordingly
			switch(castData->buttonName){
			case START_BUTTON:
					return START_BUTTON;
			case LOAD_BUTTON:
					return LOAD_BUTTON;
			case EXIT_BUTTON:
					return EXIT_BUTTON;
			default:
				break;
			}
		}
	}
	return NONE_BUTTON;
}
BUTTON_NAME handleButtonEventInSettingWin(Widget* src, SDL_Event* event,void* button){
	SimpleButton* castData = (SimpleButton*) src->data;
	SimpleButton* butt = (SimpleButton*) button;

	if (event->type == SDL_MOUSEBUTTONUP) {
		SDL_Point point;
		point.x = event->button.x;
		point.y = event->button.y;
		if (SDL_PointInRect(&point, castData->location)) {
			if (!castData->isShown) return NONE_BUTTON;
			BUTTON_NAME name = castData->buttonName;
			if (name==NONE_BUTTON) return NONE_BUTTON; //one of the title widgets
			if (name==BACK_BUTTON || name==BACK_TO_GAME_MODE_BUTTON || name==BACK_TO_DIFFICULTY_BUTTON){
				return name; //we want to be able to go back at anytime
			}
			else if (name==NEXT_DIFFICULTY_BUTTON &&(butt->buttonName==ONE_PLAYER_MODE_BUTTON)){
				return NEXT_DIFFICULTY_BUTTON;
			}
			else if (name==START_BUTTON &&
					(butt->buttonName==TWO_PLAYER_MODE_BUTTON || butt->buttonName==WHITE_COLOR_BUTTON
							|| butt->buttonName==BLACK_COLOR_BUTTON)){
				return name; //the start is shown only when two player mode is selected or one of the colors
			}
			else if (name==NEXT_COLOR_BUTTON&&(butt->buttonName!=BACK_BUTTON)) return name;
			else if (name==START_BUTTON || name==NEXT_DIFFICULTY_BUTTON
					|| name==NEXT_COLOR_BUTTON) return NONE_BUTTON; //clicking one of them without a selected option
			// we get here only if it's an option that was changed from one to another from the same type
			activate((void*) castData);
			if (butt->buttonName!=BACK_BUTTON) deactivate(button);
			return castData->buttonName;
		}
	}
	return NONE_BUTTON;
}
BUTTON_NAME handleButtonEventInLoadOrSettingWin (Widget* src, SDL_Event* event, void* button){
	if (src == NULL || event == NULL ) {
		return NONE_BUTTON; //Better to return an error value
	}
	if (event->type == SDL_WINDOWEVENT) {
		if (event->window.event == SDL_WINDOWEVENT_CLOSE){
			return X_BUTTON;
		}
	}
	SimpleButton* castData = (SimpleButton*) src->data;
	if (castData->windowName==CHESS_SETTING_WINDOW){
		return handleButtonEventInSettingWin(src,event,button);
	}
	SimpleButton* butt = (SimpleButton*) button;
	if (event->type == SDL_MOUSEBUTTONUP) {
		SDL_Point point;
		point.x = event->button.x;
		point.y = event->button.y;
		if (SDL_PointInRect(&point, castData->location)) { //if a button was clicked, I want to know which one it is so that I handle the event accordingly
			switch(castData->buttonName){
			case BACK_BUTTON:
				return BACK_BUTTON;
			case LOAD_BUTTON:
				if (castData->isActive)
					return butt->buttonName;
				break;
				//we will only reach this state, if the user activated some other gameslot button,
				//and then clicked on the load when it was already active (from a previous event)
			 //if it's not the load or the back, it must be one of the slots
			default:
				break;
			}
			BUTTON_NAME name = castData->buttonName;
			if (name==GAME_SLOT_1_BUTTON || name==GAME_SLOT_2_BUTTON || name==GAME_SLOT_3_BUTTON || name==GAME_SLOT_4_BUTTON ||
					name==GAME_SLOT_5_BUTTON	){
								activate(src->data);
								if (butt->buttonName==LOAD_BUTTON) activate(butt);
								else {
									deactivate(button);
								} //happens only if some other gameslot was clicked on before
								return LOAD_BUTTON;
			}
		}
	}
	return NONE_BUTTON;
}

BUTTON_NAME handleSimpleButtonEvenet(Widget* src, SDL_Event* event) { //so mainly this function handles main window events only
	if (src == NULL || event == NULL ) {
		return NONE_BUTTON;
	}
	if (event->type == SDL_WINDOWEVENT) {
		if (event->window.event == SDL_WINDOWEVENT_CLOSE){
			return X_BUTTON;
		}
	}
	SimpleButton* castData = (SimpleButton*) src->data;
	if (castData->windowName==CHESS_MAIN_WINDOW)
		return handleButtonEventInMainWin(src,event);
	return NONE_BUTTON;
}

void activate(void* data){
	SimpleButton* button = (SimpleButton*) data;
	button->isActive=1;
	SDL_SetRenderDrawColor(button->windowRenderer,221,142,68,255);
	SDL_RenderFillRect(button->windowRenderer,button->location);
}

void deactivate(void* data){
	SimpleButton* button = (SimpleButton*) data;
	button->isActive=0;
	SDL_SetRenderDrawColor(button->windowRenderer,188,113,43,255);
	SDL_RenderFillRect(button->windowRenderer,button->location);
	SDL_RenderPresent(button->windowRenderer);
}

void drawSimpleButton(Widget* src) {
	if (src == NULL ) {
		return;
	}
	SimpleButton* castData = (SimpleButton*) src->data;

	if (castData->isActive && castData->isShown) activate(castData);
	if (castData->windowName==CHESS_SETTING_WINDOW && !(castData->isShown)) return;
	SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,
			castData->location);
}

void hideButton(Widget* src){
	SimpleButton* button = (SimpleButton*) src->data;
	button->isShown=0;
}

void showButton(Widget* src){
	SimpleButton* button = (SimpleButton*) src->data;
	button->isShown=1;
}
