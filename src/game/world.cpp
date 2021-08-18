#include "world.h"

World::World() {
    seed = 0;
}

void World::Init(int seedVal) {
    std::cout << "Initializing world" << std::endl;

    seed = seedVal;
    Generator::SetSeed(seed);

    chunks.resize(16);
    for (int i = 0; i < 16; i += 1) {
        chunks[i].resize(16);
    }
    for (int i = 0; i < 16; i += 1) {
        for (int j = 0; j < 16; j += 1) {
            chunks[i][j].Init(i, j);
        }
    }
}

void World::Generate() {
    for (int i = 0; i < 16; i += 1) {
        for (int j = 0; j < 16; j += 1) {
            chunks[i][j].Generate();
        }
    }
}

Chunk* World::GetChunk(int x, int z) {
    return &chunks[x][z];
}
