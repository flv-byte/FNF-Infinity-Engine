#pragma once
#include <vector>
#include <renderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <memory>
#include <sceneBase.h>

struct sceneInfo
{
	std::unique_ptr<sceneBase> instance = nullptr;

	bool bgProcess = false;
	int id = 0;
	int uid = 0;
};

class sceneManager {
	Renderer* renderer;

public:
	std::vector<std::unique_ptr<sceneInfo>> scenes;
	int curScene;
	sceneManager();

	void init(Renderer* renderer);
	void tick();
	void create_scene(int id, bool bgTask);
};
