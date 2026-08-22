#pragma once
#include <renderer.h>
#include <sceneBase.h>

class debugScene : sceneBase {
	Renderer* renderer;
public:
	virtual override void init(Renderer* renderer);
	virtual override void tick(sceneInfo& info);
};