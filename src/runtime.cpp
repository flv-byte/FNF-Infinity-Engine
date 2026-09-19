#include <renderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <thread>
#include <chrono>
#include <runtime.h>
#include <sleep.h>
#include <iostream>
#include <sceneManager.h>
#include <assetManager.h>
#include <GCT.hpp>

void runtime::init(Renderer* renderer) {
    this->renderer = renderer;
    std::unique_ptr<assetManager> assetM = std::make_unique<assetManager>(renderer);
    std::unique_ptr<sceneManager> sceneM = std::make_unique<sceneManager>();
    global::gct.table["runtime"] = this;
    sceneM->init(renderer, assetM.get());
    global::gct.table["assetManager"] = assetM.get();
    global::gct.table["sceneManager"] = sceneM.get();

    sceneM->create_scene(-1, false);

    using double_ms = std::chrono::duration<double, std::milli>;
    auto frameDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(double_ms(1000.0 / fpsTarget));

    bool running = true;

    Window windowDimensions;
     
    while (running) {
        auto frameStart = std::chrono::steady_clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                renderer->resize(
                    event.window.data1,
                    event.window.data2
                );
                break;
            }
        }

        if (!running) break;

        renderer->clearScreen();

        // rendering loop
        sceneM->tick();
        assetM->uploadTextures();

        renderer->presentScreen();

        auto workTime = std::chrono::steady_clock::now() - frameStart;
        auto sleepTime = frameDuration - workTime;

        if (sleepTime > std::chrono::nanoseconds::zero()) {
            sleepPrecise(sleepTime);
        }
        auto frameEnd = std::chrono::steady_clock::now();
        auto frameTime = frameEnd - frameStart;
        fps = 1.0 / std::chrono::duration<double>(frameTime).count();
        std::cout << fps << '\n';
        windowDimensions = renderer->getGameDimensions();
        std::cout << windowDimensions.width << 'x' << windowDimensions.height << '\n';
    }
}