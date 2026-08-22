#include <vector>
#include <sceneManager.h>
#include <memory>

void sceneManager::init(Renderer* renderer) {
	this->renderer = renderer;
}

sceneManager::sceneManager() {
	scenes.reserve(5);
}