#include "Chunk.h"

Chunk::Chunk(int x, int z, float x1, float y1)
{
	xPos = x;
	zPos = z;
	noiseDataX = x1;
	noiseDataY = y1;

	for (int i = 0; i < TOTAL_BLOCKS; i++)
	{
		chunkRenderNumbers[i + 1] = 0;
		chunkRenderOffsets[i] = 0;
	}
}