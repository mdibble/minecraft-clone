#pragma once

#include <vector>

#include "../render/vertex_buffer.h"
#include "world_gen.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 32
#define CHUNK_SIZE_Z 16

class Chunk {
public:
    Chunk();
    void Init(int chunkX, int chunkY);
    void Generate();
    void LoadChunk();
    void UnloadChunk();
    void UpdateMesh();
    int GetXCoord();
    int GetZCoord();
    bool IsLoaded();
    bool NeedsUpdate();
    void SetBlock(int x, int y, int z, int block);
    int GetHighestBlockOfCoord(int x, int z);
    VertexBuffer* GetChunkBuffer();
private:
    VertexBuffer buffer;
    unsigned char data[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
    int xCoord, zCoord;
    bool needsUpdate;
    bool isLoaded;
};
