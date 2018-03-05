#ifndef SIMPLEBUTTON_H_
#define SIMPLEBUTTON_H_

#include "Widget.h"


typedef struct simplebutton_t SimpleButton;
struct simplebutton_t{
	SDL_Texture* buttonTexture;
	SDL_Renderer* windowRenderer;
	SDL_Rect* location;
	BUTTON_NAME buttonName;
	WINDOW_NAME windowName;
	int isActive;
	int isShown;
};
/**
 * Creates a button and links it to a widget to be returned.
 * @param
 * windowRender - the window renderer we will be rendering the button to
 * location - a rectangle representing the location of the button on the screen
 * image - a file path to the image that will be the texture of the button
 * windowName - the name of the window that the button belongs to, this is an enum element
 * buttonName - the name of the button itself, helps knowing its functionality and which event is requested upon clicking it
 * isActive - an int representing if the button is Active or not, an inactive button can't be clicked
 * @return
 * a widget whose data field is the button
 * and all its functions are the button's function (for example, destroyWidget points to destroyButton)
 */
Widget* createSimpleButton(SDL_Renderer* windowRender, SDL_Rect* location,
		const char* image, WINDOW_NAME windowName, BUTTON_NAME buttonName,int isActive);
/**
 * frees all resources related to the button, such as windowRenderer, Texture..
 * then frees the buttons
 * @param - the widget to destroy
 */
void destroySimpleButton(Widget*);
/**
 * A helper function.
 * Handles a button event which occurred in main window, returns the button's name which was clicked.
 * The function returns start_button if start was clicked, load button, or exit, according to which one
 * was pressed. If no button was clicked it returns NONE_GAME_BUTTON.
 * @param
 * src - the widget to handle
 * event - the SDL event that occured
 * @return
 * the name of the button clicked or in other words the event which is requested
 */
BUTTON_NAME handleButtonEventInMainWin (Widget* src, SDL_Event* event);
/**
 * * A helper function.
 * Handles a button event which occurred in the setting window, returns the button's name which was clicked.
 * The function returns button names such as game_mode_one, or the difficulty the user wants,
 * or the color she chooses.. according to which button was pressed. If no button was clicked it returns NONE_GAME_BUTTON.
 * @param
 * src - the widget to handle
 * event - the SDL event that occured
 * button - the button that was clicked before the event happened, helps to know if a game should be started for instance.
 * For example, if the button start was clicked after the button "two player mode" then it means that
 * this is a valid request and the event should happen.. same for the rest of the cases
 * @return
 * the name of the button clicked or in other words the event which is requested
 */
BUTTON_NAME handleButtonEventInSettingWin(Widget* src, SDL_Event* event,void* button);

/**
 * Handles button event, this function mainly calls for handleButtonEventInMainWin and the handling continues there..
 * In other words this is a wrapper function
 */
BUTTON_NAME handleSimpleButtonEvenet(Widget* src, SDL_Event* event);
/**
 * Handles an event according to load or setting window.
 * If the event belongs to the setting window the function calls for handleButtonEventInSettingWin
 * a helper function to avoid long lines of code.
 * If not, the function returns the load event that was requested.
 * The function also activates and deactivates other buttons according to what the user pressed,
 * for example if a game slot was chosen the load is activated, if another game slot was chosen afterwards,
 * then the first one is deactivated, etc..
 * When "load" is pressed the function returns the name of the game slot to load, so that the game would be loaded.
 * @param
 * src - the widget containing the event
 * event - sdl event
 * button - the button that was clicked before this event. also very nessecary for activating and deactivating.
 *
 */
BUTTON_NAME handleButtonEventInLoadOrSettingWin(Widget* src, SDL_Event* event, void* button);
/**
 * draw the button by copying its texture to the window renderer
 * if the button's filed "isShown" is 0, the function doesn't draw it
 * @param
 * src - the widget containing the data of the button
 */
void drawSimpleButton(Widget* src);
/**
 * hides a button by assigning 0 to its isShown field
 * @param
 * src - the widget containing the button
 */
void hideButton(Widget* src);
/**
 * shows a button by assigning 1 to its isShown field
 * @param
 * src - the widget containing the button
 */
void showButton(Widget* src);
/**
 * deactivates a button by coloring\filling its "location" rectangle the same as the background's color so that it looks "transparent" and inactive
 * also turns off its "isActive" field.
 * @param
 * button - the button to deactivate
 */
void deactivate(void* button);
/**
 * activates a button by coloring\filling its rectangle location a color different from the background's,
 * emphasizing it and making it look "alive"
 * also turns on it "isActive" field
 * @param
 * button - the button to activate
 */
void activate(void* button);


#endif
