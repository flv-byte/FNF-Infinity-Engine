#include "memory_loading/memload.h"
#include <winRenderer.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <MemoryUtil.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

memLoad::memLoad(Renderer* renderer, assetManager* assetM) {
	this->renderer = renderer;
	this->assetM = assetM;
}

int memLoad::loadIMGTexturePath(Renderer* renderer, MemorySession* session, const char* path, std::string name) {
	Image image;
	Node node;

	SDL_Texture* texture = IMG_LoadTexture(renderer->renderer, path);
	if (texture == NULL) {
		return 3;
	}
	image.texture = texture;
	node.data = image;
	session->nodes[name] = std::make_unique<Node>(std::move(node));
	return 0;
}