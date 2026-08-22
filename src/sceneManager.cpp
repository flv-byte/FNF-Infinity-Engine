#include <vector>
#include <sceneManager.h>
#include <memory>
#include <sceneBase.h>
#include <scenes/debug/debug.h>
#include <random>
#include <algorithm>


void sceneManager::init(Renderer* renderer) {
	this->renderer = renderer;
}

sceneManager::sceneManager() {
	scenes.reserve(5);
}

void sceneManager::tick() {
	for (const auto& scene : scenes) {
		scene->instance->tick(*scene);
	}
}

void sceneManager::create_scene(int id, bool bgTask)
{
    switch (id) {
    case -1: {
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

        curScene->instance = std::make_unique<debugScene>();
        curScene->id = -1;
        curScene->uid = uid;
        curScene->bgProcess = bgTask;

        curScene->instance->init();

        scenes.push_back(std::move(curScene));

        break;
    }
    }
}