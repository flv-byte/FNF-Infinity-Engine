#include <winRenderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_video.h>
#include <renderInfo.h>
#include <point.h>

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
	rect.x = 0;
	rect.y = 0;
	rect.w = 1920;
	rect.h = 1080;
	winRenderer::drawRectangleF(rect);
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

void winRenderer::resize(int width, int height) {
	aspectRatio.windowWidth = width;
	aspectRatio.windowHeight = height;
	aspectRatio.getViewDimensions(*this);
}

int aspectRatio::getViewDimensions(winRenderer& renderer) {
	currentRatio = static_cast<float>(windowWidth) / windowHeight;

	if (currentRatio > targetRatio) {
		gameHeight = windowHeight;
		gameWidth = (int)(windowHeight * targetRatio);
	}
	else {
		gameWidth = windowWidth;
		gameHeight = (int)(windowWidth / targetRatio);
	}
	return 0;
}

Window winRenderer::getGameDimensions() {
	Window window;
	window.width = aspectRatio.gameWidth;
	window.height = aspectRatio.gameHeight;
	return window;
}

int winRenderer::translateX(int x) {
	int width = aspectRatio.gameWidth;
	int height = aspectRatio.gameHeight;

	int returnX;
	int offsetX;

	returnX = (float)x / config.width * width;
	offsetX = (aspectRatio.windowWidth - width) / 2;
	returnX += offsetX;

	return returnX;
};

int winRenderer::translateY(int y) {
	int width = aspectRatio.gameWidth;
	int height = aspectRatio.gameHeight;

	int returnY;
	int offsetY;

	returnY = (float)y / config.height * height;
	offsetY = (aspectRatio.windowHeight - height) / 2;
	returnY += offsetY;

	return returnY;
};

int winRenderer::translateW(int w) {
	int width = aspectRatio.gameWidth;
	int height = aspectRatio.gameHeight;

	int returnX;

	returnX = (float)w / config.width * width;

	return returnX;
};

int winRenderer::translateH(int h) {
	int width = aspectRatio.gameWidth;
	int height = aspectRatio.gameHeight;

	int returnY;

	returnY = (float)h / config.height * height;

	return returnY;
};

int winRenderer::setDrawColor(SDL_Color color) {
	if (!SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a)) {
		return 3;
	}
	return 0;
}

int winRenderer::drawRectangleF(const SDL_FRect& rect, RenderInfo info) {
	if (!info.render) {
		return 2;
	}
	SDL_FRect translated{
		(float)translateX(rect.x+info.offset.x),
		(float)translateY(rect.y+info.offset.y),
		(float)translateW(rect.w),
		(float)translateH(rect.h)
	};

	return SDL_RenderFillRect(renderer, &translated) ? 0 : 3;
}

int winRenderer::drawRectangle(const SDL_FRect& rect, RenderInfo info) {
	if (!info.render) {
		return 2;
	}
	SDL_FRect translated{
		(float)translateX(rect.x+info.offset.x),
		(float)translateY(rect.y+info.offset.y),
		(float)translateW(rect.w),
		(float)translateH(rect.h)
	};

	return SDL_RenderRect(renderer, &translated) ? 0 : 3;
}

int winRenderer::drawLine(const Point& point1, const Point& point2, RenderInfo info) {
	if (!info.render) {
		return 2;
	}
	return SDL_RenderLine(renderer, (float)translateX(point1.x + info.offset.x), (float)translateY(point1.y + info.offset.y), (float)translateX(point2.x + info.offset.x), (float)translateY(point2.y + info.offset.y)) ? 0 : 3;
};