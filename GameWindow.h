/*
 * GameWindow.h
 *
 *  Created on: Sep 24, 2017
 *      Author: Ayah
 */

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <SDL.h>
#include <SDL_video.h>

#include "GameWidget.h"
#include "GameButton.h"
#include "setting.h"
#include "minimax.h"
#include "savedGames.h"
typedef enum {
	UNDO_SUCCESS, UNDO_FAILURE,
} UNDO_MSG;
typedef struct gamewindow_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	GameWidget** widgets;
	int numOfWidgets;
	SDL_Texture* bgTexture;
	ChessGame* ChessGame;
	GameWidget* lastUsedWidget; //will help us know when a certain piece is dragged, if the user clicked on main menu\exit after the saved button..etc.
	int isUserInputBlocked; //user input will be blocked when it's computer turn (except for window events)
} GameWindow;
/**
 * creates the widgets associated with the window, by calling for the function which creates the buttons,
 * it assigns the relative fields to them, such as the button texture, the renderer.. etc.
 * widgets in this window include chess pieces, and the buttons in the panel
 * @param
 * renderer - the renderer associated with each widget
 * game - the chess game (will use the gameboard to compute the locations of the pieces on the screen)
 * num - pointer to num, number of widget may change up to 40 widget (in some cases the user will load a game and it will miss some pieces)
 * @return
 * an array of widgets
 * NULL if errors occurred, such as errors of malloc, or creating the textures, of failure in creation one of the widgets
 *
 */
GameWidget** createGameWindowWidgets(SDL_Renderer* renderer, ChessGame* game, int* num);
/**
 * creates the game window, creates its widgets, updates it numOfWidgets, renderer, also loads its background texture
 * points to the right functions for SPWindow, for example DestoryWindow points to DestroysettingWindow and so on..
 * @param
 * game - the chess game to be assigned to the window
 * @return
 * GameWindow on success, NULL if errors happened
 */
GameWindow* createChessGameWindow(ChessGame* game);
/**
 * helper function - called from destryChessGameWindow
 * loops over the widgets and frees each one from memory resources
 */
void destroyChessGameWidgets(GameWindow* src);

void destroyChessGameWindow(GameWindow* src);

void drawChessGameWindow(GameWindow* src);
/**
 * handles an event that happened in the game window - if it's a dropped piece, isValidMove is returned and if the move is valid, set move is called
 * handles switching the turns between the two players,
 * dragging a piece, saving the game, or restarting it with the current setting and so on..
 * when something "crucial" happens in the game such as checkmate or tie, the event is returned to the manager and handled there
 * @param
 * src - the game window
 * event - the event which happened
 * @return
 * NONE_GAME_BUTTON most of the cases except when something that should move us from window to window, or a player wins or is in check, etc., then the name of the event is returned
 */
GAME_BUTTON handleEventGameWindow(GameWindow* src, SDL_Event* event);
/**
 * hides the window
 */
void hideGameWindow (GameWindow* src);
/**
 * shows the window
 */
void showGameWindow (GameWindow* src);
/**
 * helper function
 * maps a position given by a button event to the rectangle the event sat in.
 * used for accurate computation.
 * @param
 * mousepostion - the coordinates (maybe x or y) as known from event.x \ event.y
 * @return
 * the position according to the rectangle's location
 */
int map_from_mouse_position_to_rect_position(int mousePos);
/**
 * returns 1 if two given points are equal, 0 otherwise
 */
int inTheSameLocation(int x, int y, int i, int j);
/**
 * helper function
 * finds the widget that sits in a given location. the widget need to be shown to the screen as well.
 * @param -
 * src - the game window which includes the widgets array
 * XLoaction - the location in x coordinates
 * YLocation - the location in y coordinates
 * @return
 * the widget found
 * NULL if it wasn't found
 */
GameWidget* findWidgetInAGivenLocation(GameWindow* src,int XLocation, int YLocation);
/**
 * shows a certain widget in a given location
 * @param
 * src - the game window including the widgets array
 * x - x location
 * y - y location
 * piece - the name of the widget being searched for
 * when the widget is found, its isShown field is switched to 1
 */
void showWidgetinAgivenLocation(GameWindow* src,int x, int y, GAME_BUTTON piece);
/**
 * returns the name a chess piece according to the game window (as it's named in the enum "GAME_BUTTON")
 * @param
 * piece - the name of the piece according to the console mode ("B", "b", etc.)
 * @return
 * the name of the piece according to GAME_BUTTON
 */
GAME_BUTTON pieceNameAccordingToGameWindow(char piece);
/**
 * helper function
 * returns an irray of int containing data about the last move in the game - where the piece was, and where it right now
 * i.e. the arguements that were given to setmove before -
 * fromX, fromY, and toI, toJ
 * @param
 * src - the chess game, containing the last moves history array
 * @return
 * an array of int where the data is saved
 *
 */
int* undone_moves_gui(ChessGame * src);
/**
 * undoes the last move and updates the widgets related to the move, updates the location of the widget moved back,
 * an shows a widget which was captured and to be shown again..
 * computes the position of the widget on the screen and does the calculations
 * then draws the gamewindow with the new updates
 * @param
 * src - the game window
 * @return
 * UNDO_SUCCESS on success, UNDO_FAILURE otherwise (if there's no history.. etc.)
 */
UNDO_MSG undoMoveGUI(GameWindow* src);
/**
 * "captures" a chess piece by turning its isShown field to 0
 * @param
 * src - the game window - containing the widgets array
 * DestX - the destination x position which contains the pieces
 * DestY - the destination y position
 */
void captureThePiece(GameWindow* src, int DestX,int DestY);
/**
 * when set_move result is something other than ELSE (a check, checkmate, or tie),
 * this function is called to partially handle the result and it's returned to the manager later on to be handled completly
 */
GAME_BUTTON handleMoveResult(GameWindow* src, RESULT_MSG res);
/**
 * in this function the computer plays its turn by calling to the minimax algorithm and setting the move on the board and on the screen
 * @return
 * the result of the move - ELSE, CHECK, CHECKMATE, or TIE
 */
RESULT_MSG computerPlay(GameWindow* src);


#endif /* GAMEWINDOW_H_ */
