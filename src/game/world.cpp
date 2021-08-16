#include "world.h"

World::World() {

}

void World::Init() {
    std::cout << "Initializing world" << std::endl;

    chunks.resize(16);
    for (int i = 0; i < 16; i += 1) {
        chunks[i].resize(16);
    }

    Generate(12345);
}

void World::Generate(int seed) {
    for (int i = 0; i < 8; i += 1) {
        for (int j = 0; j < 8; j += 1) {
            chunks[i][j].Init(i, j);
        }
    }
}

Chunk* World::GetChunk(int x, int z) {
    return &chunks[x][z];
}
