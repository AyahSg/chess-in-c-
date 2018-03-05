#ifndef SPWINDOW_H_
#define SPWINDOW_H_
#include <SDL.h>
#include <SDL_video.h>
#include "Widget.h"

typedef struct spwindow_t SPWindow;
struct spwindow_t {
	void* data;
	void (*drawWindow)(SPWindow* );
	BUTTON_NAME (*handleEventWindow)(SPWindow* , SDL_Event* );
	void (*destroyWindow)(SPWindow* );
	void (*hideWindow) (SPWindow*);
	void (*showWindow) (SPWindow*);
};
/**
 * This function calls for the function which destroys a SPWidnow
 * and frees it from all memory resources. And it is NULL safe.
 */
void destroyWindow(SPWindow* src);

#endif
