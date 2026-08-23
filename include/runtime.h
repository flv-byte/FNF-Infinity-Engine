#pragma once
#include <renderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <sceneManager.h>

class runtime {
	Renderer* renderer;
	sceneManager* sceneM;

	public:
		virtual ~runtime() = default;

		int fpsTarget = 60;
		float fps;

		void init(Renderer* renderer);
};