#include <winRenderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

int winRenderer::init(const char* win_text, int w, int h) {

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}

	if (!SDL_CreateWindowAndRenderer(win_text, w, h, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
		return 3;
	}
	return 0;
}

int winRenderer::quit() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

void winRenderer::clearScreen() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void winRenderer::presentScreen() {
	SDL_RenderPresent(renderer);
}