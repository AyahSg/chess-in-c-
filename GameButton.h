/*
 * GameButton.h
 *
 *  Created on: Sep 24, 2017
 *      Author: Ayah
 */

#ifndef GAMEBUTTON_H_
#define GAMEBUTTON_H_
#include "GameWidget.h"
#include <SDL.h>
#include <SDL_video.h>

typedef struct gamebutton_t GameButton;
struct gamebutton_t{
	SDL_Texture* buttonTexture;
	SDL_Renderer* windowRenderer;
	SDL_Rect* location;
	SDL_Rect* originalLocation; //a button's location on screen changed when it's being dragged, we need to save its original location in case it can't be dropped.
	GAME_BUTTON buttonName;
	int isActive; //is button active and can be clicked
	int isShown; //is button on shown on screen?

	int xDrag; //the x location relative to the button's original position (helps show the piece being dragged right under the mouse)
	int yDrag; // the y location

	int xClick; //the x position when the button was clicked on
	int yClick; // the y  position when the button was clicked - helps know if a buttton was dragged
};
/**
 * helper function
 * updates the widget's location and original field - when a move is done or undone
 * @param
 * src - the widget containing the button
 * x- x point on screen
 * y - y point on screen
 */
void updateWidgetLocation(GameWidget* src,int x, int y);

GameWidget* createGameButton(SDL_Renderer* windowRender, SDL_Rect* location,
		const char* image,GAME_BUTTON buttonName,int isActive);
/**
 * frees all resources related to the button, such as windowRenderer, Texture, locations..
 * then frees the buttons
 */
void destroyGameButton(GameWidget*);
/**
 * This function handles an event in the game window, if a piece is dragged it returns that there's still a dragged piece and updates its location,
 * if she clicks on main menu\exit without saving it shows the msg box, if a piece\button in the panel was clicked it returns its name, etc.
 * and then the rest of the handling goes to the game window handler
 * @param
 * src - the widget
 * event - the event that happened
 * lastUsed - the widget that was last used before
 * isUserInputBlocked - an indicator if user input is blocked, when the computer blocked it's blocked and no button events are handled
 */
GAME_BUTTON handleGameButtonEvent(GameWidget* src, SDL_Event* event, GameWidget* lastUsed, int isUserInputBlocked);
/**
 * draws the button by copying its texture to the window renderer
 * if the button's filed "isShown" is 0, the function doesn't draw it
 * @param
 * src - the widget containing the data of the button
 */
void drawGameButton(GameWidget* src);
/**
 * checks if the given button belongs to the gameboard - a piece in the board, and not in the panel
 * this is a helper function and useful to knowing when a button is dragged or not, we don't want to allow a button in the panel to be dragged,
 * only chess pieces.
 * @param
 * button - the game button, we use its name to recognize which one it is
 * @return
 * 1 if true, 0 if false
 */
int buttonIsNotFromPanel(GameButton* button);


#endif /* GAMEBUTTON_H_ */
