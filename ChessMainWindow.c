#include <stdio.h>
#include <stdlib.h>
#include "ChessMainWindow.h"

Widget** createSimpleWindowWidgets(SDL_Renderer* renderer) {
	if (renderer == NULL ) {
		return NULL ;
	}
	Widget** widgets = malloc(sizeof(Widget*) * 3);
	if (widgets == NULL ) {
		return NULL ;
	}
	SDL_Rect startR = { .x = 25+250, .y = 65, .h = 100, .w = 250 };
	SDL_Rect loadR = { .x = 25+250, .y = 65+150, .h = 100, .w = 250 };
	SDL_Rect exitR = { .x = 25+250, .y = 65+300, .h = 100, .w = 250 };

	widgets[0] = createSimpleButton(renderer, &startR, "./Start.bmp",CHESS_MAIN_WINDOW,START_BUTTON,1);
	widgets[1] = createSimpleButton(renderer, &loadR, "./Load.bmp",CHESS_MAIN_WINDOW,LOAD_BUTTON,1);
	widgets[2] = createSimpleButton(renderer, &exitR, "./Exit.bmp",CHESS_MAIN_WINDOW,EXIT_BUTTON,1);

	if (widgets[0] == NULL || widgets[1] == NULL || widgets[2] == NULL ) {
		destroyWidget(widgets[0]); //NULL SAFE
		destroyWidget(widgets[1]); //NULL SAFE
		destroyWidget(widgets[2]); //NULL SAFE
		free(widgets);
		return NULL ;
	}
	return widgets;
}
SPWindow* createChessMainWindow() {
	SPWindow* res = malloc(sizeof(SPWindow));
	ChessMainWindow* data = malloc(sizeof(ChessMainWindow));
	SDL_Window* window = SDL_CreateWindow("Chess Champion", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);
	Widget** widgets = createSimpleWindowWidgets(renderer);
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
		printf("couldn't create mainBG.bmp surface\n");
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
		printf("couldn't create mainBG.bmp texture\n");
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);
	data->widgets = widgets;
	data->numOfWidgets = 3;
	data->bgTexture = texture;
	data->window = window;
	data->windowRenderer = renderer;
	res->data = (void*) data;
	res->destroyWindow = destroyChessMainWindow;
	res->drawWindow = drawChessMainWindow;
	res->handleEventWindow = handleEventMainWindow;
	res->hideWindow=hideMainWindow;
	res->showWindow=showMainWindow;
	return res;
}
void destroyChessMainWindow(SPWindow* src) {
	if (src == NULL ) {
		return;
	}
	ChessMainWindow* data = (ChessMainWindow*) src->data;
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
void drawChessMainWindow(SPWindow* src) {
	if (src == NULL ) {
		return;
	}
	ChessMainWindow* data = (ChessMainWindow*) src->data;

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

BUTTON_NAME handleEventMainWindow(SPWindow* src, SDL_Event* event){
	BUTTON_NAME res=NONE_BUTTON;
	if(src == NULL || event==NULL){
		return NONE_BUTTON;
	}
	ChessMainWindow* data = (ChessMainWindow*)src->data;
	int i =0;

	for(;i<data->numOfWidgets;i++){
		res = data->widgets[i]->handleEvent(data->widgets[i],event);
		if (res!=NONE_BUTTON) return res;
		//check the return value,
		//if it's not something like "no event here" continue, else return button's name
		// now that we know where want to go from this window, it should go back to the manager.
	}
	return res;
}

void hideMainWindow (SPWindow* src){
	ChessMainWindow* data = (ChessMainWindow*)src->data;
	SDL_HideWindow(data->window);
}

void showMainWindow (SPWindow* src){
	ChessMainWindow* data = (ChessMainWindow*)src->data;
	SDL_ShowWindow(data->window);
}
