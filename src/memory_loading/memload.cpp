#include "memory_loading/memload.h"
#include <winRenderer.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <thread>
#include "MemoryUtil.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

memLoad::memLoad(Renderer* renderer, assetManager* assetM) {
	this->renderer = renderer;
	this->assetM = assetM;
}

// creating

Node* memLoad::createNode(MemorySession* session, std::string name) {
    auto node = std::make_unique<Node>();
    node->name = name;

    auto [it, inserted] = session->nodes.emplace(name, std::move(node));
    return it->second.get();
}

// getting

Node* memLoad::getNode(MemorySession* session, std::string name) {
	return session->nodes.at(name).get();
}

Image* memLoad::getNodeImage(Node* node) {

    if (node->state.state.load() != progressStates::Ready) {
        return nullptr;
    }

    try {
        return std::any_cast<const std::shared_ptr<Image>&>(node->data).get();
    }
    catch (const std::bad_any_cast&) {
        return nullptr;
    }
}

// loading

int memLoad::loadIMGPath(MemorySession* session, const char* path, Node* node) {
	auto image = std::make_shared<Image>();

	SDL_Surface* surface = IMG_Load(path);
	if (surface == NULL) {
		return 3;
	}
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer->renderer, surface);
	if (texture == NULL) {
		SDL_DestroySurface(surface);
		return 3;
	}

	image->surface = surface;
	image->texture = texture;
    node->data = image;
    node->state.state = progressStates::Ready;
	return 0;
}

void memLoad::loadIMGPathAsync(MemorySession* session, const char* path, Node* node) {
    node->path = path;
    node->state.state.store(progressStates::Loading);

    std::thread([path, node]() {
        SDL_Surface* surface = IMG_Load(path);
        if (!surface) {
            node->state.state.store(progressStates::Empty);
            return;
        }

        auto image = std::make_shared<Image>();
        image->surface = surface;

        node->data = image;

        node->state.state.store(progressStates::uPending);
    }).detach();
}

void memLoad::update(Renderer* renderer, MemorySession* session) {
    for (auto& [name, node] : session->nodes) {
        if (node->state.state.load() == progressStates::uPending) {

            auto image = std::any_cast<std::shared_ptr<Image>>(node->data);
            if (image && image->surface && !image->texture) {
                image->texture = SDL_CreateTextureFromSurface(renderer->renderer, image->surface);

                if (image->texture) {
                    node->state.state.store(progressStates::Ready);
                    // YOOOO
                }
                else {
                    node->state.state.store(progressStates::Empty);
                    // awh :c
                }
            }
        }
    }
}