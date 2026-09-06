#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <MemoryUtil.hpp>
#include <renderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class assetManager;

class memLoad {
	Renderer* renderer;
	assetManager* assetM;
public:
	memLoad(Renderer* renderer, assetManager* assetM);

	static Node& getNode(MemorySession* session, std::string name);
	static Image* getNodeImage(MemorySession* session, std::string name);
	static int loadIMGPath(Renderer* renderer, MemorySession* session, const char* path, std::string name);
};