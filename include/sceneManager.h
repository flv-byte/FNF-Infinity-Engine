#pragma once
#include <vector>
#include <renderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <memory>
#include <sceneBase.h>

struct sceneInfo
{
	std::unique_ptr<sceneBase> instance;

	bool bgProcess = false;
	int id = 0;
	int uid = 0;
};

class sceneManager {
	Renderer* renderer;

public:
	std::vector<std::unique_ptr<sceneBase>> scenes;
	sceneManager();

	void init(Renderer* renderer);
};
