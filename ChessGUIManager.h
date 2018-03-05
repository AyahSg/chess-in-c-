/*
 * ChessGUIManager.h
 *
 *  Created on: Sep 22, 2017
 *      Author: Ayah
 */

#ifndef CHESSGUIMANAGER_H_
#define CHESSGUIMANAGER_H_

#include <SDL.h>
#include "ChessMainWindow.h"
#include "ChessLoadWindow.h"
#include "ChessSettingWindow.h"
#include "GameWindow.h"

typedef enum{
	CHESS_MAIN_WINDOW_ACTIVE,
	CHESS_GAME_WINDOW_ACTIVE,
	CHESS_LOAD_WINDOW_ACTIVE,
	CHESS_SETTING_WINDOW_ACTIVE,
	CHESS_LOAD_FROM_GAME_WINDOW,
} ACTIVE_WINDOW;

typedef enum{
	CHESS_MANAGER_QUIT,
	CHESS_MANAGER_NONE,
}CHESS_MANAGER_EVENT;

typedef struct {
	SPWindow* mainWin;
	SPWindow* loadWin;
	SPWindow* settingWin;
	GameWindow* gameWin;
	ChessGame* game;
	ACTIVE_WINDOW activeWin;
} ChessGuiManager;

/**
 * Creates a chessGUIManger with a given chess game.
 * It manages all events in a chess GUI game, using different functions from different modules, it mainly depends on SDL functions.
 * When a game is exited, or some error happens, CHESS_MANAGER_QUIT is returned, the manager is destroyed and SDL_Quit gets called.
 * Upon creation, the main game window is created and shown, and it's assigned as the active window of the manager.
 * @param
 * game - the chess game to be assigned to the manager, which events' will be handled and played
 * @return
 * ChessGUIManager if all memory allocating and creation was successful, NULL otherwise
 */
ChessGuiManager* chessManagerCreate(ChessGame* game);
/**
 * Frees all memory resources related to a chessGUIManager
 * @param
 * ChessGuiManager to be destroyed
 */
void chessManagerDestroy(ChessGuiManager* src);
/**
 * Draws the active window in the manager and renders it to the screen
 * @param
 * src - the ChessGUIManager which includes all the windows and a pointer to the active window which should be drawn
 */
void chessManagerDraw(ChessGuiManager* src);
/**
 * helper function
 * shows message box if the user tries to load a game with a game with difficulty level 5 and
 * the current game doesn't support it.
 * returns CHESS_MANAGER_NONE
 */
CHESS_MANAGER_EVENT showMsgBoxForExpertNotSupported();
/**
 * Handles an event according to an event that was requested by user in main window
 * For example, if the event was "start", the function hides the main window and creates a setting window
 * and shows it to the user. then return CHESS_MANAGER_NULL, if the event was exit, CHESS_MANAGER_QUIT is returned and the game is terminated
 * The function is mainly responsible for updating the active window and transition from one to another
 * @param
 * src - the event related to the game and in which the event happened
 * event - the event which happened in the main window
 * @return
 * CHESS_MANAGER_NONE after suitable changes and updates were made
 * CHESS_MANAGER_QUIT if the user invoked the X button or Exit
 */
CHESS_MANAGER_EVENT handleManagerDueToMainEvent(ChessGuiManager* src, BUTTON_NAME event) ;
/**
 * Handles an event that was requested in the setting window, and updates the game accordingly
 * For example, it sets the game difficulty that was chosen by the user, transfers from setting window to game window when the user presses start..etc.
 * Active window is updated and creation of relevant windows as well.
 * @param
 * src - the event related to the game and in which the event happened
 * event - the event which happened in the setting window
 * @return
 * chess_manager_none on success
 * CHESS_MANAGER_QUIT if the user invoked the "X" button..
 */
CHESS_MANAGER_EVENT handleManagerDueToSettingEvent (ChessGuiManager* src, BUTTON_NAME event);
/**
 * Handles an event that was requested in load window and updates the rest of the windows according.
 * If a game slot was chosen, it is loaded and the window transfer to the game window,
 * if back was chosen, it goes back to the main menu by assigning the active window as the main menu.
 * @param
 * src - the event related to the game and in which the event happened
 * event - the event which happened in the load window
 * @return
 * CHESS_MANAGER_NONE on success
 * CHESS_MANAGER_QUIT if the user invoked the "X" button
 */
CHESS_MANAGER_EVENT handleManagerDueToLoadEvent(ChessGuiManager* src, BUTTON_NAME event);
/**
 * This is a helper function in case load was requested from the game window,
 * if the event requested was "BACK", the active window switches back to the game window,
 * and CHESS_MANAGER_NONE is returned
 * otherwise it calls for handleManagerDueToLoadEvent
 * @param
 * src - the event related to the game and in which the event happened
 * event - the event which happened in the window
 */
CHESS_MANAGER_EVENT handleManagerDueToLoadFromGameWinEvent(ChessGuiManager* src, BUTTON_NAME event);
/**
 * Event handler according to a game event which occured in the game window,
 * the event can be one of the buttons that are in the panel, such as "main menu", "load", or "save"
 * or it can be a result of some move which made a difference in the game, such as check, tie, or checkmate
 * if the event was check, a simple msg box is shown to warn the threatened king and then the game continues,
 * if it was tie or checkmate, the game window is destroyed and the active window switches to the main menu window.
 * @param
 * src - the event related to the game and in which the event happened
 * event - the event which happened in the game window
 * @return
 * CHESS_MANAGER_NONE on success
 * CHESS_MANAGER_QUIT if the user invoked the X button or Exit
 */
CHESS_MANAGER_EVENT handleManagerDueToGameEvent(ChessGuiManager* src, GAME_BUTTON event);
/**
 * Wrapper function - calls for the right function to handle the event according to which window is active.
 */
CHESS_MANAGER_EVENT chessManagerHandleEvent(ChessGuiManager* src, SDL_Event* event) ;



#endif /* CHESSGUIMANAGER_H_ */
