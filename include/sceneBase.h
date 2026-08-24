#pragma once
#include <renderer.h>
#include <renderInfo.h>

struct sceneInfo;

class sceneBase
{
public:
	virtual ~sceneBase() = default;
	virtual void tick(sceneInfo& info, RenderInfo renderinfo) = 0;
	virtual void init(Renderer* renderer) = 0;
};
