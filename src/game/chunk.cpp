#include "chunk.h"

Chunk::Chunk() {
    for (int x = 0; x < 16; x += 1) {
        for (int y = 0; y < 15; y += 1) {
            for (int z = 0; z < 16; z += 1) {
                data[x][y][z] = 1;
            }
        }
    }

    for (int x = 0; x < 16; x += 1) {
        for (int y = 15; y < 16; y += 1) {
            for (int z = 0; z < 16; z += 1) {
                data[x][y][z] = 2;
            }
        }
    }

	for (int x = 0; x < 16; x += 1) {
		for (int y = 4; y < 5; y += 1) {
			for (int z = 0; z < 16; z += 1) {
				data[x][y][z] = 0;
			}
		}
	}

    needsUpdate = true;
}

void Chunk::Init() {
    buffer.Init();
    UpdateMesh();
}

void Chunk::UpdateMesh() {
	std::vector<float> verticies = { };
	std::vector<unsigned int> indicies = { };

	/*

	verticies = {
		// Bottom
		-0.5f,  -0.5f,	-0.5f,       1.0f,   1.0f,       0.0f,  -1.0f,   0.0f,
		-0.5f,  -0.5f,	 0.5f,       1.0f,   0.0f,       0.0f,  -1.0f,   0.0f,
		 0.5f,  -0.5f,	 0.5f,       0.0f,   0.0f,       0.0f,  -1.0f,   0.0f,
		 0.5f,  -0.5f,	-0.5f,       1.0f,   0.0f,       0.0f,  -1.0f,   0.0f,

		 // Top
		 -0.5f,   0.5f,	-0.5f,       1.0f,   1.0f,       0.0f,   1.0f,   0.0f,
		 -0.5f,   0.5f,	 0.5f,       1.0f,   0.0f,       0.0f,   1.0f,   0.0f,
		  0.5f,   0.5f,	 0.5f,       0.0f,   0.0f,       0.0f,   1.0f,   0.0f,
		  0.5f,   0.5f,	-0.5f,       1.0f,   0.0f,       0.0f,   1.0f,   0.0f,

		  // Left side
		  -0.5f,  -0.5f,	-0.5f,       1.0f,   1.0f,      -1.0f,   0.0f,   0.0f,
		  -0.5f,   0.5f,	-0.5f,       1.0f,   0.0f,      -1.0f,   0.0f,   0.0f,
		  -0.5f,   0.5f,	 0.5f,       0.0f,   0.0f,      -1.0f,   0.0f,   0.0f,
		  -0.5f,  -0.5f,	 0.5f,       1.0f,   0.0f,      -1.0f,   0.0f,   0.0f,

		  // Right side
		   0.5f,  -0.5f,	 0.5f,       1.0f,   1.0f,       1.0f,   0.0f,   0.0f,
		   0.5f,   0.5f,	 0.5f,       1.0f,   0.0f,       1.0f,   0.0f,   0.0f,
		   0.5f,   0.5f,	-0.5f,       0.0f,   0.0f,       1.0f,   0.0f,   0.0f,
		   0.5f,  -0.5f,	-0.5f,       1.0f,   0.0f,       1.0f,   0.0f,   0.0f,

		   // Back side
			0.5f,  -0.5f,	-0.5f,       1.0f,   1.0f,       0.0f,   0.0f,  -1.0f,
			0.5f,   0.5f,	-0.5f,       1.0f,   0.0f,       0.0f,   0.0f,  -1.0f,
		   -0.5f,   0.5f,	-0.5f,       0.0f,   0.0f,       0.0f,   0.0f,  -1.0f,
		   -0.5f,  -0.5f,	-0.5f,       1.0f,   0.0f,       0.0f,   0.0f,  -1.0f,

		   // Front side
		   -0.5f,  -0.5f,	 0.5f,       1.0f,   1.0f,       0.0f,   0.0f,   1.0f,
		   -0.5f,   0.5f,	 0.5f,       1.0f,   0.0f,       0.0f,   0.0f,   1.0f,
			0.5f,   0.5f,	 0.5f,       0.0f,   0.0f,       0.0f,   0.0f,   1.0f,
			0.5f,  -0.5f,	 0.5f,       1.0f,   0.0f,       0.0f,   0.0f,   1.0f,
	};

	indicies = {
		// Bottom
		0, 1, 2,
		0, 2, 3,

		// Top
		4, 5, 6,
		4, 6, 7,

		// Left
		8, 9, 10,
		8, 10, 11,

		// Right
		12, 13, 14,
		12, 14, 15,

		// Back
		16, 17, 18,
		16, 18, 19,

		// Front
		20, 21, 22,
		20, 22, 23,
	};

	*/

	std::vector<float> normal = { };
	std::vector<float> tex = { };
	unsigned int indexCounter = 0;

	// Top side

	normal = { 0.0f, 1.0f, 0.0f };
	tex = { 1.0f, 1.0f };

	for (int x = 0; x < 16; x += 1) {
		for (int y = 0; y < 16; y += 1) {
			for (int z = 0; z < 16; z += 1) {
				if (data[x][y][z] == 0) {
					continue;
				}

				if (y == 15 || data[x][y + 1][z] == 0) {
					std::vector<float> coords;
					std::vector<unsigned int> ind;

					coords = { (float)x, (float)y + 1, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex.begin(), tex.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y + 1, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex.begin(), tex.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y + 1, (float)z + 1};
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex.begin(), tex.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x, (float)y + 1, (float)z + 1 };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex.begin(), tex.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					ind = { indexCounter, indexCounter + 1, indexCounter + 2 };
					indicies.insert(indicies.end(), ind.begin(), ind.end());
					ind = { indexCounter, indexCounter + 2, indexCounter + 3 };
					indicies.insert(indicies.end(), ind.begin(), ind.end());
					
					indexCounter += 4;
				}
			}
		}
	}

    buffer.Bind();
    buffer.SendVerticies(&verticies[0], verticies.size() * sizeof(float));
    buffer.SendIndicies(&indicies[0], indicies.size() * sizeof(unsigned int));
    buffer.Unbind();
}

void Chunk::AnalyzeChunk() {
    if (needsUpdate) {
        UpdateMesh();
    }
}

VertexBuffer* Chunk::GetChunkBuffer() {
    return &buffer;
}
