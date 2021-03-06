#pragma once

#include "chunk.h"
#include "world_gen.h"

class World {
public:
    World();
    void PlaceBlock(int x, int y, int z, int block);
    int GetHighestBlockOfCoord(int x, int z);
    int GetBlockOfCoord(int x, int y, int z);
    void Init(int seed);
    void Generate();
    Chunk* GetChunk(int x, int z);
    Chunk* GetChunkFromCoords(int x, int z);
private:
    int seed;
    std::vector<std::vector<Chunk>> chunks;
};


