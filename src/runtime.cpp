#include <renderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <thread>
#include <chrono>
#include <runtime.h>
#include <sleep.h>
#include <iostream>
#include <sceneManager.h>

void runtime::init(Renderer* renderer, SDL_Event& event) {
    this->renderer = renderer;
    sceneM = new sceneManager;
    sceneM->init(renderer);

    sceneM->create_scene(-1, false);

    using double_ms = std::chrono::duration<double, std::milli>;
    auto frameDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(double_ms(1000.0 / fpsTarget));

    bool running = true;
     
    while (running) {
        auto frameStart = std::chrono::steady_clock::now();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
                break;
            }
        }

        if (!running) break;

        renderer->clearScreen();

        // rendering loop
        sceneM->tick();

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
    }
}