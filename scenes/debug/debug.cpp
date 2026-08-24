#include "debug/debug.h"
#include <sceneinclude.h>

void debugScene::init(Renderer* renderer) {
	this->renderer = renderer;
}

void debugScene::tick(sceneInfo& info, RenderInfo renderinfo) {
	renderer->setDrawColor(SDL_Color{255,0,0,255});
	renderer->drawLine(Point{0,1080}, Point{1920,0}, renderinfo);
	renderer->setDrawColor(SDL_Color{0,255,0,255});
	renderer->drawLine(Point{0,0}, Point{ 1920,1080}, renderinfo);
	renderer->setDrawColor(SDL_Color{0,0,255,255});
	renderer->drawLine(Point{940,520}, Point{980,560}, renderinfo);
	renderer->drawLine(Point{940,560}, Point{980,520}, renderinfo);
	renderer->drawRectangleF(SDL_FRect{ 50, 50, 50, 50 }, renderinfo);
}