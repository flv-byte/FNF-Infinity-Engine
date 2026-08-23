#include <winRenderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_video.h>

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
	SDL_SetRenderDrawColor(renderer, 20, 20, 20, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_FRect rect;
	int w, h;
	winRenderer::getGameDimensions(w, h);
	rect.x = winRenderer::translateX(0);
	rect.y = winRenderer::translateY(0);
	rect.w = w;
	rect.h = h;
	winRenderer::drawRectangle(rect);
}

void winRenderer::presentScreen() {
	SDL_RenderPresent(renderer);
}

int winRenderer::getWindowDimensions(int& width, int& height) {
	width = 0;
	height = 0;

	if (!SDL_GetWindowSizeInPixels(window, &width, &height)) {
		return 3;
	}

	return 0;
}

int aspectRatio::getViewDimensions(winRenderer& renderer, int& width, int& height) {
	const int result = renderer.getWindowDimensions(windowWidth, windowHeight);
	if (result != 0) {
		return result;
	}

	currentRatio = static_cast<float>(windowWidth) / windowHeight;

	if (currentRatio > targetRatio) {
		gameHeight = windowHeight;
		gameWidth = (int)(windowHeight * targetRatio);
	}
	else {
		gameWidth = windowWidth;
		gameHeight = (int)(windowWidth / targetRatio);
	}
	width = gameWidth;
	height = gameHeight;
	return 0;
}

int winRenderer::getGameDimensions(int& w, int& h) {
	return aspectRatio.getViewDimensions(*this, w, h);
}

int winRenderer::translateX(int x) {
	int width;
	int height;
	if (aspectRatio.getViewDimensions(*this, width, height) != 0) {
		return -1;
	}

	int returnX;
	int offsetX;

	returnX = (float)x / config.width * width;
	offsetX = (aspectRatio.windowWidth - width) / 2;
	returnX += offsetX;

	return returnX;
};

int winRenderer::translateY(int y) {
	int width;
	int height;
	if (aspectRatio.getViewDimensions(*this, width, height) != 0) {
		return 3;
	}

	int returnY;
	int offsetY;

	returnY = (float)y / config.height * height;
	offsetY = (aspectRatio.windowHeight - height) / 2;
	returnY += offsetY;

	return returnY;
};

int winRenderer::setDrawColor(SDL_Color color) {
	if (!SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a)) {
		return 3;
	}
	return 0;
}

int winRenderer::drawRectangle(const SDL_FRect rect) {
	if (!SDL_RenderFillRect(renderer, &rect)) {
		return 3;
	};
	return 0;
}