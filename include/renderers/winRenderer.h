#pragma once

#include <SDL3/SDL.h>

class winRenderer {
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Event event;

	virtual int init(const char* win_text, int w, int h);
	virtual SDL_Event& event_pass();
	virtual int quit();
};