#include "Renderer.h"

Renderer::Renderer()
{
	glEnable(GL_DEPTH_TEST);

	// sizeof(float) * 30 * 6 is the size of the cube vertices array
	setClearColour(0.3f, 0.5f, 0.6f, 1.0f);
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setClearColour(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::renderCubemapInstanced(Texture& texture, VBO& vbo, int numberOfDraws)
{
	vbo.bind();
	texture.bind();
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, numberOfDraws);
}

void Renderer::renderOpaqueBlocks(BufferHandler& bufferHandler, ShaderHandler& shaderHandler)
{
	shaderHandler.useShader(BLOCK_SHADER);

	for (int i = 0; i < TOTAL_BLOCKS; i++)
	{
		bufferHandler.blockVAOs[i]->bind();
		renderCubemapInstanced(textures[i], *bufferHandler.blockPosVBOs[i], bufferHandler.matrices[i].size());
	}
}