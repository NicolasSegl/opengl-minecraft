#pragma once

#include <vector>
#include <glew.h>
#include <iostream>
#include <glm.hpp>

#include "VAO.h"
#include "VBO.h"
#include "Block.h"

using namespace std;

class BufferHandler
{
public:
	BufferHandler();

	// this is essentially just the number of blocks in the game
	int numOfBuffers = 3;
	
	vector<VAO*> blockVAOs;
	vector<VBO*> blockPosVBOs;
	vector<vector<glm::mat4>> matrices;

	void fillPositionData(int index);
	void update();
};