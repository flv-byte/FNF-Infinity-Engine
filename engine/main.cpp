#include <iostream>
#include <memory>
#include <renderer.h>
#include <runtime.h>
#include <wrapper/engine_API.hpp>

int main(int argc, char* argv[]) {
    global::engine engine;

    std::vector<std::string> args(argv, argv + argc);
    bool isDebugMode = false;

    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--debug") {
            isDebugMode = true;
        }
    }

    engine.init(isDebugMode, argv);
    return 0;
}