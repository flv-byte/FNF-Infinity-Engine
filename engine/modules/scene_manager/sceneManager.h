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
#include <any>
#include <string>

class assetManager;
class sceneManager;
struct sceneInfo;

using SceneInit = std::function<void(sceneInfo&, Renderer*, assetManager*, sceneManager*)>;
using SceneTick = std::function<void(sceneInfo&, RenderInfo)>;
using SceneDestroy = std::function<void(sceneInfo&)>;

struct SceneDefinition {
	SceneInit init;
	SceneTick tick;
	SceneDestroy destroy;
};

using SceneFactory = std::function<SceneDefinition()>;

struct sceneInfo
{
	SceneDefinition definition;
	std::any state;

	bool bgProcess = false;
	std::string id;
	int uid = 0;

	~sceneInfo()
	{
		if (definition.destroy)
			definition.destroy(*this);
	}
};

template <typename T>
SceneDefinition makeSceneDefinition()
{
	return {
		[](sceneInfo& info, Renderer* renderer, assetManager* assetM, sceneManager* sceneM) {
			auto& instance = info.state.emplace<T>();
			instance.init();
		},
		[](sceneInfo& info, RenderInfo renderinfo) {
			std::any_cast<T&>(info.state).tick(info, renderinfo);
		},
		[](sceneInfo& info) {
			info.state.reset();
		}
	};
}

class sceneManager {
	Renderer* renderer;
	assetManager* assetM;

public:

	sceneManager();
	virtual ~sceneManager() = default;

	std::vector<std::unique_ptr<sceneInfo>> scenes;
	std::unordered_map<std::string, SceneFactory> list_scenes;
	int currentScene = 0;

	void init();
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
			return makeSceneDefinition<type>(); \
		}); \
		return true; \
	}();
#define REGISTER_SCENE(name, type) REGISTER_SCENE_IMPL(name, type, __COUNTER__)

