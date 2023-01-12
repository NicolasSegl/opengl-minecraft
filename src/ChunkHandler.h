#pragma once

#include <vector>
#include <thread>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Block.h"
#include "NoiseGenerator.h"
#include "BufferHandler.h"
#include "Chunk.h"
#include "Camera.h"
#include "Player.h"

using namespace std;

// if the rendering doesn't work, make it render on the main thread
class ChunkHandler
{
public:
	vector<Block*> blocks;
	vector<Chunk*> chunks;
	NoiseGenerator noiseGenerator;
	BufferHandler* bufferHandler;

	ChunkHandler() {};
	ChunkHandler(BufferHandler* bufferHandler);

	void createChunk(Chunk& chunk);
	void deleteChunk(Chunk& chunk);
	void generateChunkData(int x, int z);
	int generateChunks(Player& player);

	void generateThread(bool finished, Player& p);

	int renderDistance = 8;
	int chunkRenderNumber = 0;
	float chunkNoiseDataIncrease = 0.05;
};
