#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <thread>
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

    static Node* createNode(MemorySession* session, std::string name);

    static Node* getNode(MemorySession* session, std::string name);
    static Image* getNodeImage(Node* node);

    int loadIMGPath(MemorySession* session, const char* path, Node* node);
    static void loadIMGPathAsync(MemorySession* session, const char* path, Node* node);

    static void update(Renderer* renderer, MemorySession* session);
};