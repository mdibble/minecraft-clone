#include "game.h"

Game::Game() {
}

void Game::Init() {
    std::cout << "Initializing game" << std::endl;

    srand(time(0));
    int seed = rand();
    std::cout << seed << std::endl;


    world.Init(seed);
    world.Generate();
}
