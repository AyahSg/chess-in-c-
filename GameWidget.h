/*
 * GameGameWidget.h
 *
 *  Created on: Sep 24, 2017
 *      Author: Ayah
 */

#ifndef GAMEWIDGET_H_
#define GAMEWIDGET_H_
#include <SDL.h>
#include <SDL_video.h>
/**
 * this enum includes:
 * names of each piece in the chess board, helps knowing which piece was chosen
 * names of the buttons in the panel of the game window (main menu,exit.. etc.),
 * an indicator of a dragged\dropped piece (usually returned from the handle function)
 * and the name of two little widgets on the side of the screen which switch every time the turn changes in game
 */
typedef enum {WHITE_PAWN_BUTTON,WHITE_BISHOP_BUTTON,WHITE_KING_BUTTON,WHITE_QUEEN_BUTTON,WHITE_KNIGHT_BUTTON,WHITE_ROOK_BUTTON,
BLACK_PAWN_BUTTON,BLACK_BISHOP_BUTTON,BLACK_KING_BUTTON,BLACK_QUEEN_BUTTON,BLACK_KNIGHT_BUTTON,BLACK_ROOK_BUTTON,
UNDO_BUTTON,MAIN_MENU_BUTTON,EXIT_GAME_BUTTON,RESTART_BUTTON,SAVE_BUTTON,LOAD_GAME_BUTTON, NONE_GAME_BUTTON, X_GAME_BUTTON,
GAME_CHECKMATE, GAME_CHECK, GAME_TIE,
DRAGGED_PIECE,DROPPED_PIECE,
CURRENT_TURN_BLACK, CURRENT_TURN_WHITE} GAME_BUTTON;


typedef struct gamewidget_t GameWidget;
struct gamewidget_t {
	void (*drawGameWidget)(GameWidget*);
	GAME_BUTTON (*handleEvent)(GameWidget*, SDL_Event*,GameWidget*,int);
	void (*destroyGameWidget)(GameWidget*);
	void* data;
	void (*hideGameWidget) (GameWidget*);
	void (*showGameWidget) (GameWidget*);
	int isDragged; //is widget being dragged by user?
};
/**
 * destroys the widget by calling for the function which points to the correct destroy function.
 * NULL safe
 */
void destroyGameWidget(GameWidget* src);

#endif /* GAMEWIDGET_H_ */
