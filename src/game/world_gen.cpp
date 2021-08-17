#include "world_gen.h"

int noise(int x, int z) {
    int y = 0;

    y = rand() % 2 + 8;
    
    return y;
}
