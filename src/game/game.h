#pragma once

#include "world.h"
#include "player.h"

#include <iostream>
#include <stdlib.h>

class Game {
public:
    Game();
    void Init(InputHandler* inputHandlerPointer);
    World world;
    Player player;
private:
    InputHandler* inputHandler;
};
