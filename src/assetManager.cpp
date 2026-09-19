#include <assetManager.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <MemoryUtil.hpp>

class memLoad;

assetManager::assetManager(Renderer* renderer) {
    this->renderer = renderer;
    memload = std::make_unique<memLoad>(renderer, this);
}

MemorySession* assetManager::createSession(const std::string& name) {
    auto session = std::make_unique<MemorySession>(name);
    MemorySession* rawPtr = session.get();

    sessions[name] = std::move(session);
    return rawPtr;
}

MemorySession* assetManager::getSession(const std::string& name) {
    auto it = sessions.find(name);
    if (it != sessions.end()) {
        return it->second.get();
    }
    return nullptr;
}

void assetManager::destroySession(const std::string& name) {
    sessions.erase(name);
}

int assetManager::uploadTextures() {
    for (auto& [name, session] : sessions) {
        memload->update(renderer, session.get());
    }

    return 0;
}