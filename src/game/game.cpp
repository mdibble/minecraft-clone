#include "game.h"

Game::Game() {
}

void Game::Init() {
    std::cout << "Initializing game" << std::endl;

    world.Init(12345);
    world.Generate();
}
