#include <assetManager.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <MemoryUtil.hpp>
#include <GCT.hpp>

class memLoad;

assetManager::assetManager() {
    renderer = std::any_cast<Renderer*>(global::gct.table.at("renderer"));
    global::gct.table["assetManager"] = this;
    memload = std::make_unique<memLoad>();
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

void assetManager::destroySession(MemorySession* session) {
    if (session == nullptr) {
        return;
    }

    for (auto it = sessions.begin(); it != sessions.end(); ++it) {
        if (it->second.get() == session) {
            sessions.erase(it);
            return;
        }
    }
}

int assetManager::uploadTextures() {
    for (auto& [name, session] : sessions) {
        memload->update(renderer, session.get());
    }

    return 0;
}