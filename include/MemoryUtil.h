#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <any>
#include <SDL3/SDL.h>

struct Image {
	SDL_Texture* texture;
};

struct Node {
	std::any data;
};

struct MemorySession {
	std::string name;
	std::unordered_map<std::string, std::unique_ptr<Node>> nodes;
};