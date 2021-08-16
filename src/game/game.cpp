#include "game.h"

Game::Game() {
}

void Game::Init() {
    std::cout << "Initializing game" << std::endl;

    world.Init();
    world.Generate(12345);
}
