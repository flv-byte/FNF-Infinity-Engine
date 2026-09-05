#pragma once

#include <SDL3/SDL.h>
#include <renderInfo.h>
#include <point.h>

struct Window {
	int width;
	int height;
};

struct Config {
	int width = 1920;
	int height = 1080;
};

inline constexpr Config config{};

class winRenderer;

class aspectRatio {

public:
	float targetRatio = static_cast<float>(config.width) / config.height;
	float currentRatio;
	int windowWidth;
	int windowHeight;
	int gameWidth;
	int gameHeight;

	int getViewDimensions(winRenderer& renderer);
};

class winRenderer {
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	aspectRatio aspectRatio;

	virtual ~winRenderer() = default;

	virtual int init(const char* win_text, int w, int h);
	virtual int quit();
	virtual void clearScreen();
	virtual void presentScreen();
	virtual int getWindowDimensions(int& width, int& height);
	virtual Window getGameDimensions();

	virtual void resize(int width, int height);

	virtual int translateX(int x);
	virtual int translateY(int y);
	virtual int translateW(int w);
	virtual int translateH(int h);

	virtual int setDrawColor(SDL_Color color);
	virtual int drawRectangleF(const SDL_FRect& rect, RenderInfo info = {});
	virtual int drawRectangle(const SDL_FRect& rect, RenderInfo info = {});
	virtual int drawLine(const Point& point1, const Point& point2, RenderInfo info = {});

	virtual int drawTexture(SDL_Texture* texture, const SDL_FRect* srcrect, const SDL_FRect& dstrect, RenderInfo info = {});
};
