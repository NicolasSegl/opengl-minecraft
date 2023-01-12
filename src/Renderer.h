#pragma once

#include <glew.h>
#include <vector>

#include "VAO.h"
#include "VBO.h"
#include "Block.h"
#include "Texture.h"
#include "ShaderHandler.h"
#include "BufferHandler.h"

using namespace std;

class Renderer
{
public:
	Renderer();

	Texture textures[TOTAL_BLOCKS] =
	{
		{"textures\\grass\\config.txt"},
		{"textures\\sand\\config.txt"},
		{"textures\\water\\config.txt"}
	};

	void clear();
	void setClearColour(float r, float g, float b, float a);
	// add overrides to this function later
	void renderCubemapInstanced(Texture& texture, VBO& vbo, int numberOfDraws);
	void renderOpaqueBlocks(BufferHandler& bufferHandler, ShaderHandler& shaderHandler);
};