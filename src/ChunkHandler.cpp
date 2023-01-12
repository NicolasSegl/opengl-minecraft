#include "ChunkHandler.h"

void ChunkHandler::createChunk(Chunk& chunk)
{
	double* blockData = noiseGenerator.createData
	(
		chunk.noiseDataX,
		chunk.noiseDataX + chunkNoiseDataIncrease,
		chunk.noiseDataY,
		chunk.noiseDataY + chunkNoiseDataIncrease
	);
	// iterate through block data and assign the values to blocks
	for (int i = 0; i < CHUNK_WIDTH * CHUNK_LENGTH; i++)
	{
		Block* block = new Block(i % 16 + (chunk.xPos * 16), (int)(blockData[i] * 40), i / 16 + (chunk.zPos * 16));
		blocks.push_back(block);
	}

	static bool fillDeletionData = true;

	for (int i = 0; i < CHUNK_WIDTH * CHUNK_LENGTH; i++)
	{
		// crate matrices for each block
		int index = -1;
		if (blocks[blocks.size() - i - 1]->position.y > -7)
			index = GRASS_BLOCK;
		else if (blocks[blocks.size() - i - 1]->position.y < -6)
			index = SAND_BLOCK;

		if (fillDeletionData)
		{
			for (int j = 0; j < TOTAL_BLOCKS; j++)
				chunk.chunkRenderNumbers[j + 1] = bufferHandler->matrices[j].size();

		//	cout << chunk.chunkRenderNumbers[1] << endl;
			fillDeletionData = false;
		}

		if (index > -1)
		{
			// add a position to the matrices vector of the particular block 
			bufferHandler->matrices[index].push_back(glm::mat4(1.0f));
			bufferHandler->matrices[index][bufferHandler->matrices[index].size() - 1] =
				glm::translate
				(
					bufferHandler->matrices[index][bufferHandler->matrices[index].size() - 1],
					blocks[blocks.size() - i - 1]->position
				);
			blocks[blocks.size() - i - 1]->type = "water";
		}

		if (index == SAND_BLOCK && blocks[blocks.size() - i - 1]->position.y < -8)
		{
			glm::vec3 waterBlockPos = glm::vec3(blocks[blocks.size() - i - 1]->position);
			while (waterBlockPos.y + 1 < -8)
			{
				waterBlockPos.y++;

				bufferHandler->matrices[WATER_BLOCK].push_back(glm::mat4(1.0f));
				bufferHandler->matrices[WATER_BLOCK][bufferHandler->matrices[WATER_BLOCK].size() - 1] =
					glm::translate
					(
						bufferHandler->matrices[WATER_BLOCK][bufferHandler->matrices[WATER_BLOCK].size() - 1],
						waterBlockPos
					);
			}
		}
	}

	// fill offsets data.
	// should be 256 at the most
	for (int i = 0; i < TOTAL_BLOCKS; i++)
		chunk.chunkRenderOffsets[i] = bufferHandler->matrices[i].size() - chunk.chunkRenderNumbers[i + 1];

	chunk.loaded = true;
	chunk.chunkRenderNumbers[0] = chunkRenderNumber;
	fillDeletionData = true;
	chunkRenderNumber++;
}

// delete chunks by deleting all the relevant data currently being held (in memory)
void ChunkHandler::deleteChunk(Chunk& chunk)
{
	chunk.loaded = false;
	chunkRenderNumber--;

	blocks.erase(blocks.begin() + chunk.chunkRenderNumbers[0] * 256, blocks.begin() + chunk.chunkRenderNumbers[0] * 256 + 256);

	// change the offsets of the chunks' data because they have changed
	for (int i = 0; i < chunks.size(); i++)
	{
		if (!chunks[i]->loaded)
			continue;

		if (!(chunks[i]->chunkRenderNumbers[0] == chunk.chunkRenderNumbers[0]))
			if (chunks[i]->chunkRenderNumbers[0] >= chunk.chunkRenderNumbers[0])
				chunks[i]->chunkRenderNumbers[0]--;
	}

	// same but for the matrix buffers
	for (int i = 0; i < TOTAL_BLOCKS; i++)
	{
		if (chunk.chunkRenderNumbers[i + 1] < 0)
			continue;

		bufferHandler->matrices[i].erase
		(
			bufferHandler->matrices[i].begin() + chunk.chunkRenderNumbers[i + 1],
			bufferHandler->matrices[i].begin() + chunk.chunkRenderNumbers[i + 1] + chunk.chunkRenderOffsets[i]
		);

		for (int j = 0; j < chunks.size(); j++)
		{
			if (chunks[j]->loaded)			
				if (chunks[j]->chunkRenderNumbers[i + 1] >= chunk.chunkRenderNumbers[i + 1])
					chunks[j]->chunkRenderNumbers[i + 1] -= chunk.chunkRenderOffsets[i];
		}
	}

	// this way it will throw an error if there is one
	chunk.chunkRenderNumbers[0] = -1;
}

// make the 50 values higher, when the rendering is being multithreaded
void ChunkHandler::generateChunkData(int x, int z)
{
	// noise data x, noise data y

	// i = -50 * (x + 1)?
	// j = -50 * (z + 1)?

	for (int i = -50; i < 50; i++)
		for (int j = -50; j < 50; j++)
		{
			Chunk* chunk = new Chunk(i, j, i * chunkNoiseDataIncrease, j * chunkNoiseDataIncrease);
			chunks.push_back(chunk);
		}
}

// calculate which chunk should be rendered, then render it on the main thread
int ChunkHandler::generateChunks(Player& player)
{
	int index = 0;

	for (int i = 0; i < chunks.size(); i++)
	{
		// thank you ms fish, very cool
		int distance = sqrt
		(
			(player.chunkXPos - chunks[i]->xPos) * (player.chunkXPos - chunks[i]->xPos) +
			(player.chunkZPos - chunks[i]->zPos) * (player.chunkZPos - chunks[i]->zPos)
		);

		if (distance < renderDistance && !chunks[i]->loaded)
			createChunk(*chunks[i]);
		else if (distance > renderDistance && chunks[i]->loaded)
			deleteChunk(*chunks[i]);
	}

	return index;
}

ChunkHandler::ChunkHandler(BufferHandler* bh)
{
	bufferHandler = bh;
}