#include "game.h"

Game::Game() {
    inputHandler = nullptr;
}

void Game::Init(InputHandler* inputHandlerPointer) {
    std::cout << "Initializing game" << std::endl;

    inputHandler = inputHandlerPointer;

    srand(time(0));
    int seed = rand();
    std::cout << seed << std::endl;

    world.Init(seed);
    world.Generate();

    player.Init(1, 2, 1, inputHandler);
}
