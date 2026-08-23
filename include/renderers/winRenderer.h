#pragma once

#include <SDL3/SDL.h>

class winRenderer {
public:
	SDL_Window* window;
	SDL_Renderer* renderer;

	virtual ~winRenderer() = default;

	virtual int init(const char* win_text, int w, int h);
	virtual int quit();
	virtual void clearScreen();
	virtual void presentScreen();
};