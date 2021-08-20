#include "game.h"

Game::Game() {
    inputHandler = nullptr;
}

void Game::Init(InputHandler* inputHandlerPointer) {
    std::cout << "Initializing game" << std::endl;

    inputHandler = inputHandlerPointer;

    world.Init(12345);
    world.Generate();

    player.Init(1, 2, 1, inputHandler);
}
