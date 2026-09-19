#pragma once

#include <sceneinclude.h>
#include <any>

class debugScene : public sceneBase
{
    Renderer* renderer = nullptr;
    assetManager* assetM = nullptr;
    sceneManager* sceneM = nullptr;

    MemorySession* memSession;

    Node* node = nullptr;
    Image* image = nullptr;
    SDL_Texture* test = nullptr;

public:
    void init(Renderer* renderer, assetManager* assetM, sceneManager* sceneM) override;
    void tick(sceneInfo& info, RenderInfo renderinfo) override;

    ~debugScene();
};