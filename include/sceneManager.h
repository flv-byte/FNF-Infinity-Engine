#pragma once
#include <vector>
#include <renderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <memory>
#include <sceneBase.h>
#include <renderInfo.h>
#include <unordered_map>
#include <functional>

class assetManager;

using SceneFactory = std::function<std::unique_ptr<sceneBase>()>;

struct sceneInfo
{
	std::unique_ptr<sceneBase> instance;

	bool bgProcess = false;
	std::string id;
	int uid = 0;
};

class sceneManager {
	Renderer* renderer;
	assetManager* assetM;

public:

	sceneManager();
	virtual ~sceneManager() = default;

	std::vector<std::unique_ptr<sceneInfo>> scenes;
	std::unordered_map<std::string, SceneFactory> list_scenes;
	int currentScene = 0;

	void init(Renderer* renderer, assetManager* assetM);
	void tick();
	void create_scene(std::string id, bool bgTask);
	static void register_scene(const std::string& name, SceneFactory factory);
	int switch_sceneUID(int uid);
	int switch_sceneRight(int t);
	int switch_sceneLeft(int t);
	int switch_sceneID(std::string id);
	int delete_sceneUID(int uid);
};

#define SCENE_REGISTER_CONCAT_IMPL(left, right) left##right
#define SCENE_REGISTER_CONCAT(left, right) SCENE_REGISTER_CONCAT_IMPL(left, right)
#define REGISTER_SCENE_IMPL(name, type, id) \
	static bool SCENE_REGISTER_CONCAT(reg_scene_, id) = []() { \
		sceneManager::register_scene(name, []() { \
            return std::make_unique<type>(); \
        }); \
        return true; \
	}();
#define REGISTER_SCENE(name, type) REGISTER_SCENE_IMPL(name, type, __COUNTER__)
