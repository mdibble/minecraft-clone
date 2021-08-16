#pragma once

#include "chunk.h"

class World {
public:
    World();
    void Init();
    void Generate(int seed);
    Chunk* GetChunk(int x, int z);
private:
    std::vector<std::vector<Chunk>> chunks;
};


