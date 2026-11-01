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

using SceneInit = std::function<void(sceneInfo&)>;
using SceneTick = std::function<void(sceneInfo&, RenderInfo)>;
using SceneDestroy = std::function<void(sceneInfo&)>;

// The three functions needed to run one scene.
struct SceneDefinition {
	SceneInit init;
	SceneTick tick;
	SceneDestroy destroy;
};

// Creates a new definition when a scene is added.
using SceneFactory = std::function<SceneDefinition()>;

struct sceneInfo
{
	SceneDefinition definition;
	std::any state;

	bool bgProcess = false;
	std::string id;
	int uid = 0;

	// Destroy the scene's stored state before the scene is removed.
	~sceneInfo()
	{
		if (definition.destroy)
			definition.destroy(*this);
	}
};

// Connects a scene class to the generic scene callbacks.
template <typename T>
SceneDefinition makeSceneDefinition()
{
	return {
		[](sceneInfo& info) {
			info.state.emplace<T>().init();
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
	// Stores factories that can create scene definitions.
	inline static std::unordered_map<std::string, SceneFactory> list_scenes;
	int currentScene = 0;

	void init();
	void tick();
	// Creates a scene from its registered factory and adds it to the scene list.
	void create_scene(std::string id, bool bgTask);
	// Adds a factory to the list used when scenes are created.
	static void register_scene(const std::string& name, SceneFactory factory);

	// Registers a scene class by automatically creating its factory.
	template <typename T>
	static bool register_scene(const std::string& name)
	{
		register_scene(name, []() {
			return makeSceneDefinition<T>();
		});
		return true;
	}
	int switch_sceneUID(int uid);
	int switch_sceneRight(int t);
	int switch_sceneLeft(int t);
	int switch_sceneID(std::string id);
	int delete_sceneUID(int uid);
};

// Registers a scene before the scene manager is created.
#define REGISTER_SCENE(name, type) \
	static const bool reg_scene_##type = sceneManager::register_scene<type>(name);

