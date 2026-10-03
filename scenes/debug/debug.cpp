#include "debug/debug.h"
#include <sceneinclude.h>
#include <iostream>
#include <any>
#include <engine_API.hpp>

void debugScene::init() {
	this->renderer = std::any_cast<Renderer*>(global::gct.table.at("renderer"));
	this->assetM = std::any_cast<assetManager*>(global::gct.table.at("assetManager"));
	this->sceneM = std::any_cast<sceneManager*>(global::gct.table.at("sceneManager"));

	memSession = assetM->createSession("debugScene_scene");
	memLoad::createNode(memSession, "debug_image");
	node = memLoad::getNode(memSession, "debug_image");
	assetM->memload->loadIMGPathAsync(memSession, "assets/debug/lol.png", node);
}

void debugScene::tick(sceneInfo& info, RenderInfo renderinfo) {
	if (test == nullptr) {
		image = memLoad::getNodeImage(node);
		test = image != nullptr ? image->texture : nullptr;
	}
	renderer->drawTexture(test, sourceRect, destinationRect, renderinfo);
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
	if (assetM != nullptr && memSession != nullptr) {
		assetM->destroySession(memSession);
	}
	memSession = nullptr;
}

REGISTER_SCENE("debug_1", debugScene);