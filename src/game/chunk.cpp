#include "chunk.h"

Chunk::Chunk() {
    for (int x = 0; x < 16; x += 1) {
        for (int y = 0; y < 15; y += 1) {
            for (int z = 0; z < 16; z += 1) {
                data[x][y][z] = 2;
            }
        }
    }

    for (int x = 0; x < 16; x += 1) {
        for (int y = 15; y < 16; y += 1) {
            for (int z = 0; z < 16; z += 1) {
                data[x][y][z] = 1;
            }
        }
    }

    needsUpdate = true;
	isLoaded = false;
	xCoord = 0;
	zCoord = 0;
}

void Chunk::Init(int chunkX, int chunkZ) {
	xCoord = chunkX;
	zCoord = chunkZ;
}

void Chunk::UpdateMesh() {
	std::vector<float> verticies = { };
	std::vector<unsigned int> indicies = { };

	std::vector<float> normal = { };
	unsigned int indexCounter = 0;

	// Top side

	normal = { 0.0f, 1.0f, 0.0f };

	for (int x = 0; x < 16; x += 1) {
		for (int y = 0; y < 16; y += 1) {
			for (int z = 0; z < 16; z += 1) {
				if (data[x][y][z] == 0) {
					continue;
				}

				if (y == 15 || data[x][y + 1][z] == 0) {
					unsigned int blockTexIndex = data[x][y][z] - 1;

					float texX, texY;
					texX = 0.0625 * (blockTexIndex % 16);
					texY = 0.0625 * 3 * floor(blockTexIndex / 16);
					texY += 0.0625; // Top texture

					std::vector<float> coords;
					std::vector<unsigned int> ind;
					std::vector<float> tex00 = { texX, texY };
					std::vector<float> tex01 = { texX, texY + 0.0625f };
					std::vector<float> tex10 = { texX + 0.0625f, texY };
					std::vector<float> tex11 = { texX + 0.0625f, texY + 0.0625f };

					coords = { (float)x, (float)y + 1, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex00.begin(), tex00.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y + 1, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex10.begin(), tex10.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y + 1, (float)z + 1};
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex11.begin(), tex11.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x, (float)y + 1, (float)z + 1 };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex01.begin(), tex01.end());
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

	// Bottom side

	normal = { 0.0f, -1.0f, 0.0f };
	for (int x = 0; x < 16; x += 1) {
		for (int y = 0; y < 16; y += 1) {
			for (int z = 0; z < 16; z += 1) {
				if (data[x][y][z] == 0) {
					continue;
				}

				if (y == 0 || data[x][y - 1][z] == 0) {
					unsigned int blockTexIndex = data[x][y][z] - 1;

					float texX, texY;
					texX = 0.0625 * (blockTexIndex % 16);
					texY = 0.0625 * 3 * floor(blockTexIndex / 16);
					texY += 0.000; // Bottom texture

					std::vector<float> coords;
					std::vector<unsigned int> ind;
					std::vector<float> tex00 = { texX, texY };
					std::vector<float> tex01 = { texX, texY + 0.0625f };
					std::vector<float> tex10 = { texX + 0.0625f, texY };
					std::vector<float> tex11 = { texX + 0.0625f, texY + 0.0625f };

					coords = { (float)x, (float)y, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex00.begin(), tex00.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex10.begin(), tex10.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y, (float)z + 1 };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex11.begin(), tex11.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x, (float)y, (float)z + 1 };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex01.begin(), tex01.end());
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

	// Left side

	normal = { -1.0f, 0.0f, 0.0f };
	for (int x = 0; x < 16; x += 1) {
		for (int y = 0; y < 16; y += 1) {
			for (int z = 0; z < 16; z += 1) {
				if (data[x][y][z] == 0) {
					continue;
				}

				if (x == 0 || data[x][x - 1][z] == 0) {
					unsigned int blockTexIndex = data[x][y][z] - 1;

					float texX, texY;
					texX = 0.0625 * (blockTexIndex % 16);
					texY = 0.0625 * 3 * floor(blockTexIndex / 16);
					texY += 0.125; // Side texture

					std::vector<float> coords;
					std::vector<unsigned int> ind;
					std::vector<float> tex00 = { texX, texY };
					std::vector<float> tex01 = { texX, texY + 0.0625f };
					std::vector<float> tex10 = { texX + 0.0625f, texY };
					std::vector<float> tex11 = { texX + 0.0625f, texY + 0.0625f };

					coords = { (float)x, (float)y, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex00.begin(), tex00.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x, (float)y + 1, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex01.begin(), tex01.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x, (float)y + 1, (float)z + 1};
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex11.begin(), tex11.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x, (float)y, (float)z + 1};
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex10.begin(), tex10.end());
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

	// Right side

	normal = { 1.0f, 0.0f, 0.0f };
	for (int x = 0; x < 16; x += 1) {
		for (int y = 0; y < 16; y += 1) {
			for (int z = 0; z < 16; z += 1) {
				if (data[x][y][z] == 0) {
					continue;
				}

				if (x == 15 || data[x][x + 1][z] == 0) {
					unsigned int blockTexIndex = data[x][y][z] - 1;

					float texX, texY;
					texX = 0.0625 * (blockTexIndex % 16);
					texY = 0.0625 * 3 * floor(blockTexIndex / 16);
					texY += 0.125; // Side texture

					std::vector<float> coords;
					std::vector<unsigned int> ind;
					std::vector<float> tex00 = { texX, texY };
					std::vector<float> tex01 = { texX, texY + 0.0625f };
					std::vector<float> tex10 = { texX + 0.0625f, texY };
					std::vector<float> tex11 = { texX + 0.0625f, texY + 0.0625f };

					coords = { (float)x + 1, (float)y, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex00.begin(), tex00.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y + 1, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex01.begin(), tex01.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y + 1, (float)z + 1 };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex11.begin(), tex11.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y, (float)z + 1 };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex10.begin(), tex10.end());
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

	// Front side

	normal = { 0.0f, 0.0f, 1.0f };
	for (int x = 0; x < 16; x += 1) {
		for (int y = 0; y < 16; y += 1) {
			for (int z = 0; z < 16; z += 1) {
				if (data[x][y][z] == 0) {
					continue;
				}

				if (z == 15 || data[x][z + 1][z] == 0) {
					unsigned int blockTexIndex = data[x][y][z] - 1;

					float texX, texY;
					texX = 0.0625 * (blockTexIndex % 16);
					texY = 0.0625 * 3 * floor(blockTexIndex / 16);
					texY += 0.125; // Side texture

					std::vector<float> coords;
					std::vector<unsigned int> ind;
					std::vector<float> tex00 = { texX, texY };
					std::vector<float> tex01 = { texX, texY + 0.0625f };
					std::vector<float> tex10 = { texX + 0.0625f, texY };
					std::vector<float> tex11 = { texX + 0.0625f, texY + 0.0625f };

					coords = { (float)x, (float)y, (float)z + 1 };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex00.begin(), tex00.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x, (float)y + 1, (float)z + 1 };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex01.begin(), tex01.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y + 1, (float)z + 1 };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex11.begin(), tex11.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y, (float)z + 1 };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex10.begin(), tex10.end());
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

	// Back side

	normal = { 0.0f, 0.0f, -1.0f };
	for (int x = 0; x < 16; x += 1) {
		for (int y = 0; y < 16; y += 1) {
			for (int z = 0; z < 16; z += 1) {
				if (data[x][y][z] == 0) {
					continue;
				}

				if (z == 0 || data[x][z - 1][z] == 0) {
					unsigned int blockTexIndex = data[x][y][z] - 1;

					float texX, texY;
					texX = 0.0625 * (blockTexIndex % 16);
					texY = 0.0625 * 3 * floor(blockTexIndex / 16);
					texY += 0.125; // Side texture

					std::vector<float> coords;
					std::vector<unsigned int> ind;
					std::vector<float> tex00 = { texX, texY };
					std::vector<float> tex01 = { texX, texY + 0.0625f };
					std::vector<float> tex10 = { texX + 0.0625f, texY };
					std::vector<float> tex11 = { texX + 0.0625f, texY + 0.0625f };

					coords = { (float)x, (float)y, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex00.begin(), tex00.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x, (float)y + 1, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex01.begin(), tex01.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y + 1, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex11.begin(), tex11.end());
					verticies.insert(verticies.end(), normal.begin(), normal.end());

					coords = { (float)x + 1, (float)y, (float)z };
					verticies.insert(verticies.end(), coords.begin(), coords.end());
					verticies.insert(verticies.end(), tex10.begin(), tex10.end());
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

bool Chunk::IsLoaded() {
	return isLoaded;
}

void Chunk::LoadChunk() {
	if (isLoaded) {
		return;
	}

	isLoaded = true;
	buffer.Init();
	UpdateMesh();
}

void Chunk::UnloadChunk() {
	if (!isLoaded) {
		return;
	}

	buffer.Bind();
	buffer.Delete();
	buffer.Unbind();
	isLoaded = false;
}

void Chunk::AnalyzeChunk() {
    if (needsUpdate) {
        UpdateMesh();
    }
}

int Chunk::GetXCoord() {
	return xCoord;
}

int Chunk::GetZCoord() {
	return zCoord;
}

VertexBuffer* Chunk::GetChunkBuffer() {
    return &buffer;
}
