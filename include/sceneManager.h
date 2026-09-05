#pragma once
#include <vector>
#include <renderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <memory>
#include <sceneBase.h>
#include <renderInfo.h>

class assetManager;

struct sceneInfo
{
	std::unique_ptr<sceneBase> instance = nullptr;

	bool bgProcess = false;
	int id = 0;
	int uid = 0;
};

class sceneManager {
	Renderer* renderer;
	assetManager* assetM;

public:

	virtual ~sceneManager() = default;

	std::vector<std::unique_ptr<sceneInfo>> scenes;
	int currentScene = 0;
	sceneManager();

	void init(Renderer* renderer, assetManager* assetM);
	void tick();
	void create_scene(int id, bool bgTask);
	int switch_sceneUID(int uid);
	int switch_sceneRight(int t);
	int switch_sceneLeft(int t);
	int switch_sceneID(int id);
	int delete_sceneUID(int uid);
};
