#pragma once

#include <vector>

#include "../render/vertex_buffer.h"

class Chunk {
public:
    Chunk();
    void Init();
    void UpdateMesh();
    void AnalyzeChunk();
    VertexBuffer* GetChunkBuffer();
private:
    VertexBuffer buffer;
    unsigned char data[16][16][16];
    bool needsUpdate;
};
