#include <iostream>
#include <renderer.h>
#include <runtime.h>

int main(int argc, char* argv[]) {
    Renderer* renderer = new Renderer();
    renderer->init("FLV FNF", 960, 540);
    SDL_Event& evt = renderer->event_pass();
    runtime* rt = new runtime();
    rt->init(renderer, evt);
    renderer->quit();
    delete renderer;
    delete rt;

    return 0;
}