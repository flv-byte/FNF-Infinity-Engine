#pragma once

#include <renderer.h>
#include <renderInfo.h>

struct sceneInfo;
class assetManager;
class sceneManager;

class sceneBase
{
public:
	virtual ~sceneBase() = default;
	virtual void tick(sceneInfo& info, RenderInfo renderinfo) = 0;
	virtual void init(Renderer* renderer, assetManager* assetM, sceneManager* sceneM) = 0;
};
