#include "debug/debug.h"
#include <sceneinclude.h>
#include "memory_loading/memload.h"
#include <iostream>
#include <any>

void debugScene::init(Renderer* renderer, assetManager* assetM, sceneManager* sceneM) {
	this->renderer = renderer;
	this->assetM = assetM;
	this->sceneM = sceneM;

	memSession = assetM->createSession("debugScene_scene");
	memLoad::loadIMGPath(renderer, memSession, "assets/debug/lol.png", "debug_image");
	Image* image = memLoad::getNodeImage(memSession, "debug_image");
	test = image->texture;
}

void debugScene::tick(sceneInfo& info, RenderInfo renderinfo) {
	renderer->drawTexture(test, { NULL }, {0,0,1920,1080});
	renderer->setDrawColor(SDL_Color{255,0,0,255});
	renderer->drawLine(Point{0,1080}, Point{1920,0}, renderinfo);
	renderer->setDrawColor(SDL_Color{0,255,0,255});
	renderer->drawLine(Point{0,0}, Point{ 1920,1080}, renderinfo);
	renderer->setDrawColor(SDL_Color{0,0,255,255});
	renderer->drawLine(Point{940,520}, Point{980,560}, renderinfo);
	renderer->drawLine(Point{940,560}, Point{980,520}, renderinfo);
	renderer->drawRectangleF(SDL_FRect{ 50, 50, 50, 50 }, renderinfo);
}

debugScene::~debugScene() {
	assetM->destroySession(memSession->name);
}