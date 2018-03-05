/*
 * ChessLoadWindow.h
 *
 *  Created on: Sep 23, 2017
 *      Author: Ayah
 */

#ifndef CHESSLOADWINDOW_H_
#define CHESSLOADWINDOW_H_

#include "SPWindow.h"
#include "SimpleButton.h"

typedef struct loadwindow_t  ChessLoadWindow;
struct loadwindow_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	Widget** widgets;
	int numOfWidgets;
	SDL_Texture* bgTexture;
};
/**
 * helper function
 * creates the widgets associated with the window, by calling for the function which creates the buttons,
 * it assigns the relative fields to them, such as the button texture, the renderer.. etc.
 * @param
 * renderer - the renderer the widgets will be rendered to
 * numberOsSavedGames - as it's named, used to knowing how many game slots are to be shown
 * @return
 * an array of widgets
 * NULL if errors occurred, such as errors of malloc, or creating the textures, of failure in creation one of the widgets
 */
Widget** createLoadWindowWidgets(SDL_Renderer* renderer, int numberOfSavedGames);
/**
 * creates LoadWindow, creates its widgets, updates it numOfWidgets, renderer, also loads its background texture
 * points to the right functions for SPWindow, for example DestoryWindow points to DestroyLoadWindow and so on..
 * @param
 * number of saved games, the number of the saved games in the directory, in order to specify how many game slots to show
 * @return
 * SPWindow on success
 * NULL if errors happened
 */
SPWindow* createChessLoadWindow(int numberOfSavedGames);
/**
 * frees all resources related to the window, destroys the window's widgets, the background texture,
 * the renderer, the SDL_Window, and all other field which used memory
 * @param
 * src - the window to destroy
 */
void destroyChessLoadWindow(SPWindow* src);
/**
 * draws the window to the renderer by calling for drawWidget for each widget in the window,
 * also draws the background texture to the screen
 * and then calls for renderpresent
 * @param
 * src - the window to draw
 */
void drawChessLoadWindow(SPWindow* src);
/**
 * Handles an event in the load windows, before that it loops over the widgets to see which one was the last active
 * then loops over widgets and calls for handleEvent for each one, when one of the widgets returns something other than NONE_GAME_BUTTON
 * (an indicator that no event happened with that button), it is returned to the chessGUImanager
 * to be handled.
 * @param
 * src - the window (the load window)
 * event - the event to handle
 *
 * @return
 * button_name - the name of the button clicked, or NONE_BUTTON if no button was clicked
 *
 */
BUTTON_NAME handleEventLoadWindow(SPWindow* src, SDL_Event* event);
/**
 * hides the window
 */
void hideLoadWindow (SPWindow* src);
/**
 * shows the window
 */
void showLoadWindow (SPWindow* src);


#endif /* CHESSLOADWINDOW_H_ */
