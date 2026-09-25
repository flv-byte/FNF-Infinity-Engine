#include <vector>
#include <sceneManager.h>
#include <memory>
#include <sceneBase.h>
#include <random>
#include <algorithm>
#include <renderInfo.h>
#include <assetManager.h>

namespace {
	std::unordered_map<std::string, SceneFactory>& registeredScenes() {
		static std::unordered_map<std::string, SceneFactory> scenes;
		return scenes;
	}
}

void sceneManager::init(Renderer* renderer, assetManager* assetM) {
	this->renderer = renderer;
	this->assetM = assetM;
}

sceneManager::sceneManager() {
	scenes.reserve(5);
	list_scenes = registeredScenes();
}

void sceneManager::tick() {
	auto it = std::find_if(scenes.begin(), scenes.end(), [this](const auto& item) {
		return item->uid == currentScene;
		});

	if (it != scenes.end()) {
		currentScene = 0;
	}

	for (const auto& scene : scenes) {
		if (currentScene == 0) {
			currentScene = scene->uid;
		}
		RenderInfo renderinfo;
		renderinfo.render = (currentScene = scene->uid) ? true : false;
		renderinfo.offset.x = 0;
		renderinfo.offset.y = 0;
		if (currentScene != scene->uid && scene->bgProcess) {
			scene->instance->tick(*scene, renderinfo);
		}
		else if (currentScene == scene->uid) {
			scene->instance->tick(*scene, renderinfo);
		}
	}
}

int sceneManager::switch_sceneUID(int targetUid) {
	auto it = std::find_if(scenes.begin(), scenes.end(), [targetUid](const auto& item) {
		return item->uid == targetUid;
		});

	if (it == scenes.end()) {
		currentScene = targetUid;
		return 0;
	}
	else {
		return 3;
	}
}

int sceneManager::switch_sceneRight(int t) {
	if (scenes.empty())
		return 3;

	auto it = std::find_if(
		scenes.begin(),
		scenes.end(),
		[this](const auto& s) {
			return s->uid == currentScene;
		}
	);

	if (it == scenes.end())
		return 3;

	const int index = static_cast<int>(
		std::distance(scenes.begin(), it)
		);

	const int newIndex =
		(index + (t % static_cast<int>(scenes.size()))
			+ static_cast<int>(scenes.size()))
		% static_cast<int>(scenes.size());

	currentScene = scenes[newIndex]->uid;
	return 0;
}

int sceneManager::switch_sceneLeft(int t) {
	if (scenes.empty())
		return 3;

	auto it = std::find_if(
		scenes.begin(),
		scenes.end(),
		[this](const auto& s) {
			return s->uid == currentScene;
		}
	);

	if (it == scenes.end())
		return 3;

	const int index = static_cast<int>(
		std::distance(scenes.begin(), it)
		);

	const int newIndex =
		(index - (t % static_cast<int>(scenes.size()))
			+ static_cast<int>(scenes.size()))
		% static_cast<int>(scenes.size());

	currentScene = scenes[newIndex]->uid;
	return 0;
}

int sceneManager::switch_sceneID(std::string id) {
	if (scenes.empty()) return 3;

	auto currentIt = std::find_if(
		scenes.begin(),
		scenes.end(),
		[this](const auto& s) {
			return s->uid == currentScene;
		}
	);

	if (currentIt == scenes.end())
		return 3;

	const int currentIndex = static_cast<int>(std::distance(scenes.begin(), currentIt));

	auto targetIt = std::find_if(
		scenes.begin(),
		scenes.end(),
		[id](const auto& s) {
			return s->id == id;
		}
	);

	if (targetIt == scenes.end())
		return 3;

	const int targetIndex = static_cast<int>(std::distance(scenes.begin(), targetIt));

	if (scenes[currentIndex]->id != scenes[targetIndex]->id)
	{
		currentScene = scenes[targetIndex]->uid;
		return 0;
	}

	for (size_t n = 1; n <= scenes.size(); ++n)
	{
		const size_t j = (static_cast<size_t>(currentIndex) + n) % scenes.size();

		if (scenes[j]->id == scenes[currentIndex]->id)
		{
			currentScene = scenes[j]->uid;
			return 0;
		}
	}

	return 3;
}

int sceneManager::delete_sceneUID(int targetUid) {
	if (scenes.empty()) return 3;

	auto it = std::find_if(
		scenes.begin(),
		scenes.end(),
		[targetUid](const auto& s) {
			return s->uid == targetUid;
		}
	);

	if (it == scenes.end())
		return 3;

	scenes.erase(it);
	return 0;
}

void sceneManager::create_scene(std::string id, bool bgTask)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, 9999);

	int uid;

	do
	{
		uid = dist(gen);
	} while (
		std::find_if(
			scenes.begin(),
			scenes.end(),
			[uid](const auto& scene)
			{
				return scene->uid == uid;
			}
		) != scenes.end()
		);

	auto curScene = std::make_unique<sceneInfo>();

	curScene->instance = list_scenes.at(id)();
	curScene->id = id;
	curScene->uid = uid;
	curScene->bgProcess = bgTask;

	curScene->instance->init(renderer, assetM, this);

	scenes.push_back(std::move(curScene));
}

void sceneManager::register_scene(const std::string& name, SceneFactory factory) {
	registeredScenes()[name] = std::move(factory);
}