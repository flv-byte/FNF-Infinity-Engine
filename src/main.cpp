#include <iostream>
#include <memory>
#include <renderer.h>
#include <runtime.h>

int main(int argc, char* argv[]) {
    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
    renderer->init("FLV FNF", 960, 540);
    std::unique_ptr<runtime> rt = std::make_unique<runtime>();
    rt->init(renderer.get());
    renderer->quit();

    return 0;
}