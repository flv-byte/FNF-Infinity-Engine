#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <any>
#include <SDL3/SDL.h>
#include <filesystem>
#include <future>

struct Image {
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = nullptr;

	~Image() {
		SDL_DestroyTexture(texture);
		SDL_DestroySurface(surface);
	}
};

enum class progressStates { Empty, Loading, uPending, Ready };

struct nodeState {
	std::atomic<progressStates> state{ progressStates::Empty };
	bool stream = false;
};

struct Node {
	std::string name;
	std::filesystem::path path;
	std::any data;
	uint64_t size;
	nodeState state;
};

struct MemorySession {
	std::string name;
	std::unordered_map<std::string, std::unique_ptr<Node>> nodes;
};