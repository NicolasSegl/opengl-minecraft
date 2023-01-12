#include "BufferHandler.h"

BufferHandler::BufferHandler()
{
	VBO* blockBuffer = new VBO; 
	blockBuffer->addBuffer(sizeof(float) * 30 * 6, cubeVertices);

	for (int i = 0; i < numOfBuffers; i++)
	{
		VAO* vao = new VAO;
		vao->addBuffer(*blockBuffer);
		vao->addLayout(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
		blockVAOs.push_back(vao);

		VBO* blockVBO = new VBO;
		blockPosVBOs.push_back(blockVBO);
	}

	matrices.resize(numOfBuffers);
}

void BufferHandler::fillPositionData(int index)
{
	if (matrices[index].size() <= 0)
		return;

	blockPosVBOs[index]->addBuffer(sizeof(glm::mat4) * matrices[index].size(), &matrices[index][0]);
	blockPosVBOs[index]->bind();
	blockVAOs[index]->setupForInstances();
}

void BufferHandler::update()
{
	for (int i = 0; i < TOTAL_BLOCKS; i++)
		fillPositionData(i);
}