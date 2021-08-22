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

void World::PlaceBlock(int x, int y, int z, int block) {
    Chunk* chunk = GetChunkFromCoords(x, z);
    int localX = x % CHUNK_SIZE_X;
    int localZ = z % CHUNK_SIZE_Z;
    
    chunk->SetBlock(localX, y, localZ, block);
}

int World::GetHighestBlockOfCoord(int x, int z) {
    Chunk* chunk = GetChunkFromCoords(x, z);
    int localX = x % CHUNK_SIZE_X;
    int localZ = z % CHUNK_SIZE_Z;

    return chunk->GetHighestBlockOfCoord(localX, localZ);
}

int World::GetBlockOfCoord(int x, int y, int z) {
    Chunk* chunk = GetChunkFromCoords(x, z);
    int localX = x % CHUNK_SIZE_X;
    int localZ = z % CHUNK_SIZE_Z;

    return chunk->GetBlock(localX, y, localZ);
}

Chunk* World::GetChunk(int x, int z) {
    return &chunks[x][z];
}

Chunk* World::GetChunkFromCoords(int x, int z) {
    return &chunks[x / 16][z / 16];
}
