#pragma once

#include <SDL3/SDL.h>

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

	int getViewDimensions(winRenderer& renderer, int& width, int& height);
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
	virtual int getGameDimensions(int& w, int& h);
	virtual int translateX(int x);
	virtual int translateY(int y);

	virtual int setDrawColor(SDL_Color color);
	virtual int drawRectangle(const SDL_FRect rect);
};