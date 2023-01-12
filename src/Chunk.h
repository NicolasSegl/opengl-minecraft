#pragma once

#include <glm.hpp>

#include "Block.h"

class Chunk
{
public:
	// simply change loaded to true if the chunk is loaded, this will prevent the reloading of chunks.
	bool loaded = false;

	int xPos, zPos;
	float noiseDataX, noiseDataY;
	int chunkRenderNumbers[TOTAL_BLOCKS + 1];
	int chunkRenderOffsets[TOTAL_BLOCKS];

	Chunk(int x, int z, float noiseDataX, float noiseDataY);
};