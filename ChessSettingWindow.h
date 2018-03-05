/*
 * ChessSettingWindow.h
 *
 *  Created on: Sep 23, 2017
 *      Author: Ayah
 */

#ifndef CHESSSETTINGWINDOW_H_
#define CHESSSETTINGWINDOW_H_
#include "SPWindow.h"
#include "SimpleButton.h"

typedef struct settingwindow_t  ChessSettingWindow;
struct settingwindow_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	//All widgets in our window
	Widget** widgets;
	int numOfWidgets;
	SDL_Texture* bgTexture;
};
/**
 * creates the widgets associated with the window, by calling for the function which creates the buttons,
 * it assigns the relative fields to them, such as the button texture, the renderer.. etc.
 * and then returns an array of widgets
 * NULL if errors occurred, such as errors of malloc, or creating the textures, of failure in creation one of the widgets
 */
Widget** createSettingWindowWidgets(SDL_Renderer* renderer);
/**
 * creates settingWindow, creates its widgets, updates it numOfWidgets, renderer, also loads its background texture
 * points to the right functions for SPWindow, for example DestoryWindow points to DestroysettingWindow and so on..
 * returns SPWindow on success, NULL if errors happened
 */
SPWindow* createChessSettingWindow();
/**
 * frees all resources related to the window, destroys the window's widgets, the background texture,
 * the renderer, the SDL_Window, and all other field which used memory
 */
void destroyChessSettingWindow(SPWindow* src);
/**
 * draws the window to the renderer by calling for drawWidget for each widget in the window,
 * also draws the background texture to the screen
 * and then calls for renderpresent
 */
void drawChessSettingWindow(SPWindow* src);
/**
 * Handles an event in the setting window, before that it loops over the widgets to see which one was the last active
 * then loops over widgets and calls for handleEvent for each one, when one of the widgets returns something other than NONE_GAME_BUTTON
 * (an indicator that no event happened with that button), it is returned and handled partly in the function:
 * so for instance if the player clicked on two player mode, the button at the bottom of the window should change from "next" to "start"
 * this function handles such issues, also activates and deactivates buttons according to which one was clicked and so on..
 *
 */
BUTTON_NAME handleEventSettingWindow(SPWindow* src, SDL_Event* event);
/**
 * hides the window
 */
void hideSettingWindow (SPWindow* src);
/**
 * shows the window
 */
void showSettingWindow (SPWindow* src);
/**
 * Helper function
 * turns on the "isShown" field to the buttons which are in the subwindow of setting window
 * which is responsible for showing the difficulty buttons (noob, easy, hard..)
 * And hides the buttons in the sub window that was before, in this case, the "game mode" subwindow
 * @param
 * data - the window which includes the widgets\buttons
 */
void showDifficultyWindowButtons(ChessSettingWindow* data);
/**
 * Helper function
 * turns on the "isShown" field to the buttons which are in the subwindow of setting window
 * which is responsible for showing the game mode buttons (game mode 1 \ 2),
 * in case the user clicked back after being in the difficulty subwindow then we need to show the buttons again
 * and hide the buttons of the difficulty sub window
 * @param
 * data - the window which includes the widgets\buttons
 */
void showGameModeWindowButtons(ChessSettingWindow* data);
/**
 * Helper function
 * on moving from the difficulty subwindow to the "Choose your color" subwindow, we need to turn on the isShown field
 * of the colors button, and hide difficulty buttons.
 * So mainly these three helper functions are the ones responsible for transition between the 3 subwindows of the setting window
 * We decide which window we should be in according to which buttons are shown\hidden
 * @param
 * data - the window which includes the widgets\buttons
 */
void showColorWindowButtons(ChessSettingWindow* data);

#endif /* CHESSSETTINGWINDOW_H_ */
