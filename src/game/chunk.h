#pragma once

#include <vector>

#include "../render/vertex_buffer.h"

class Chunk {
public:
    Chunk();
    void Init(int chunkX, int chunkY);
    void LoadChunk();
    void UnloadChunk();
    void UpdateMesh();
    void AnalyzeChunk();
    int GetXCoord();
    int GetZCoord();
    bool IsLoaded();
    VertexBuffer* GetChunkBuffer();
private:
    VertexBuffer buffer;
    unsigned char data[16][16][16];
    int xCoord, zCoord;
    bool needsUpdate;
    bool isLoaded;
};
