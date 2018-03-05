#ifndef SPSIMPLEMAINWINDOW_H_
#define SPSIMPLEMAINWINDOW_H_
#include "SPWindow.h"
#include "SimpleButton.h"

typedef struct sp_simplewindow_t  ChessMainWindow;
struct sp_simplewindow_t {
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
 * @param
 * renderer - the renderer the widgets will be rendered to
 * @return
 * an array of widgets
 * NULL if errors occurred, such as errors of malloc, or creating the textures, of failure in creation one of the widgets
 */
Widget** createSimpleWindowWidgets(SDL_Renderer* renderer);
/**
 * creates main menu window, creates its widgets, updates it numOfWidgets, renderer, also loads its background texture
 * points to the right functions for SPWindow, for example DestoryWindow points to DestroysettingWindow and so on..
 * @return
 * SPWindow of type main window on success, NULL if errors happened
 */
SPWindow* createChessMainWindow();
/**
 * frees all resources related to the window, destroys the window's widgets, the background texture,
 * the renderer, the SDL_Window, and all other field which used memory
 * @param
 * src -the window to destroy
 */
void destroyChessMainWindow(SPWindow* src);
/**
 * draws the window to the renderer by calling for drawWidget for each widget in the window,
 * also draws the background texture to the screen
 * and then calls for renderpresent
 * @param
 * src - the window to draw
 */
void drawChessMainWindow(SPWindow* src);
/**
 * Handles an event in the main window,
 * by looping over widgets and calls for handleEvent for each one, when one of the widgets returns something other than NONE_GAME_BUTTON
 * (an indicator that no event happened with that button), the button name is returned and handled in the chessGUImanager accordingly
 * @param
 * src - the window in which the event happened
 * event - the event
 * @return
 * name of the button that was clicked \ the event requested
 */
BUTTON_NAME handleEventMainWindow(SPWindow* src, SDL_Event* event);
/**
 * hides the window
 */
void hideMainWindow (SPWindow* src);
/**
 * shows the window
 */
void showMainWindow (SPWindow* src);

#endif
