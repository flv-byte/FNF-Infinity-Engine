#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <MemoryUtil.hpp>
#include <renderer.h>
#include "memory_loading/memload.h"

class assetManager {
private:
    Renderer* renderer = nullptr;

    std::unique_ptr<memLoad> memload;
	std::unordered_map<std::string, std::unique_ptr<MemorySession>> sessions;

public:
    assetManager(Renderer* renderer);

    MemorySession* createSession(const std::string& name);
    MemorySession* getSession(const std::string& name);
    void destroySession(const std::string& name);
};