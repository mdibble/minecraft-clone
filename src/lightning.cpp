#include "lightning.h"

Lightning::Lightning() {
}

void Lightning::Init() {
    std::cout << "Initializing application" << std::endl;
    renderer.Init();
    std::cout << "App initialization complete" << std::endl;
}

void Lightning::Run() {
    while (true) {
        renderer.BeginFrame();
        renderer.DrawPoly();
        renderer.EndFrame();
    }
}
