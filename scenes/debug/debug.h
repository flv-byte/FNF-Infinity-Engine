#pragma once

#include <renderer.h>
#include <sceneBase.h>

class debugScene : public sceneBase
{
    Renderer* renderer = nullptr;

public:
    void init(Renderer* renderer) override;
    void tick(sceneInfo& info) override;
};