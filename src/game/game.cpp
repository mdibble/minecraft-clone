#include "game.h"

Game::Game() {
    inputHandler = nullptr;
}

void Game::Init(InputHandler* inputHandlerPointer) {
    std::cout << "Initializing game" << std::endl;

    inputHandler = inputHandlerPointer;

    world.Init(12345);
    world.Generate();

    int x = 26;
    int z = 26;
    int y = world.GetHighestBlockOfCoord(x, z);

    player.Init(x, y + 1, z, inputHandler, &world);
}
