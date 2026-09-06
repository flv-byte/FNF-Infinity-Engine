#include "memory_loading/memload.h"
#include <winRenderer.h>
#include <unordered_map>
#include <string>
#include <memory>
#include "MemoryUtil.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

memLoad::memLoad(Renderer* renderer, assetManager* assetM) {
	this->renderer = renderer;
	this->assetM = assetM;
}

// getting

Node& memLoad::getNode(MemorySession* session, std::string name) {
	return *session->nodes.at(name).get();
}

Image* memLoad::getNodeImage(MemorySession* session, std::string name) {
	return std::any_cast<const std::shared_ptr<Image>&>(memLoad::getNode(session, name).data).get();
}

// loading

int memLoad::loadIMGPath(Renderer* renderer, MemorySession* session, const char* path, std::string name) {
	auto image = std::make_shared<Image>();
	auto nodePtr = std::make_unique<Node>();

	SDL_Surface* surface = IMG_Load(path);
	if (surface == NULL) {
		return 3;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer->renderer, surface);
	if (texture == NULL) {
		SDL_DestroySurface(surface);
		return 3;
	}

	image->surface = surface;
	image->texture = texture;
	nodePtr->data = image;
	nodePtr->state.state = progressStates::Ready;
	session->nodes[name] = std::move(nodePtr);
	return 0;
}