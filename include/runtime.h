#pragma once
#include <renderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <sceneManager.h>

class runtime {
	Renderer* renderer;
	SDL_Event event;
	sceneManager* sceneM;

	public:
		int fpsTarget = 60;
		float fps;

		virtual void init(Renderer* renderer, SDL_Event& event);
};