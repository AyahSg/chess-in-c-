#ifndef WIDGET_H_
#define WIDGET_H_
#include <SDL.h>
#include <SDL_video.h>
/**
 * enum to assigning the window of a button
 */
typedef enum {
	CHESS_MAIN_WINDOW, CHESS_LOAD_WINDOW, CHESS_SETTING_WINDOW, CHESS_GAME_WINDOW,
} WINDOW_NAME;

typedef enum {
	START_BUTTON, LOAD_BUTTON, EXIT_BUTTON, NONE_BUTTON, X_BUTTON,
	GAME_SLOT_1_BUTTON,GAME_SLOT_2_BUTTON,GAME_SLOT_3_BUTTON,
	GAME_SLOT_4_BUTTON, GAME_SLOT_5_BUTTON, NEXT_BUTTON, BACK_BUTTON,ONE_PLAYER_MODE_BUTTON,
	TWO_PLAYER_MODE_BUTTON, NEXT_DIFFICULTY_BUTTON, NOOB_BUTTON, EASY_BUTTON,HARD_BUTTON,MODERATE_BUTTON,EXPERT_BUTTON,
	BACK_TO_GAME_MODE_BUTTON,NEXT_COLOR_BUTTON,WHITE_COLOR_BUTTON,BLACK_COLOR_BUTTON,BACK_TO_DIFFICULTY_BUTTON
} BUTTON_NAME; //will be used to knowing which event is requested


typedef struct widget_t Widget;
struct widget_t {
	void (*drawWidget)(Widget*);
	BUTTON_NAME (*handleEvent)(Widget*, SDL_Event*);
	BUTTON_NAME (*loadOrSettingHandleEvent)(Widget*, SDL_Event*, void*);
	void (*destroyWidget)(Widget*);
	void* data;
	void (*hideWidget) (Widget*);
	void (*showWidget) (Widget*); //probably won't need
};

/**
 * This function calls for the function which destroys a specific widget
 * and frees it from all memory resources. And it is NULL safe.
 */
void destroyWidget(Widget* src);
#endif
