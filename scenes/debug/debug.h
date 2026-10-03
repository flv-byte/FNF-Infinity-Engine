#pragma once

#include <sceneinclude.h>
#include <any>

class debugScene
{
    Renderer* renderer = nullptr;
    assetManager* assetM = nullptr;
    sceneManager* sceneM = nullptr;

    MemorySession* memSession;

    Node* node = nullptr;
    Image* image = nullptr;
    SDL_Texture* test = nullptr;

    SDL_FRect sourceRect{ 0, 0, 300, 300 };
    SDL_FRect destinationRect{ 0, 0, 1920, 1080 };

public:
    void init();
    void tick(sceneInfo& info, RenderInfo renderinfo);

    ~debugScene();
};