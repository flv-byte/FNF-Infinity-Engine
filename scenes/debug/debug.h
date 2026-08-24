#pragma once

#include <sceneinclude.h>

class debugScene : public sceneBase
{
    Renderer* renderer = nullptr;

public:
    void init(Renderer* renderer) override;
    void tick(sceneInfo& info, RenderInfo renderinfo) override;
};