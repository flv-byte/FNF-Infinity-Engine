#pragma once
#include <renderer.h>

struct sceneInfo;

class sceneBase
{
public:
	virtual ~sceneBase() = default;
	virtual void tick(sceneInfo& info) = 0;
	virtual void init(Renderer* renderer) = 0;
};
