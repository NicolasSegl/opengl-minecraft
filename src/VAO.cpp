#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &rendererID);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &rendererID);
}

void VAO::addBuffer(VBO& vbo)
{
	bind();
	vbo.bind();
}

void VAO::addLayout(int index, int countDistance, int glType, int glNormalize, int stride, int offset)
{
	bind();
	glVertexAttribPointer(index, countDistance, glType, glNormalize, stride, (const void*)offset);
	glEnableVertexAttribArray(index);
}

void VAO::bind()
{
	glBindVertexArray(rendererID);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

void VAO::setupForInstances()
{
	// add the various variables needed in the cubemap shader to allow it to work with instanced draw calls
	for (int i = 0; i < 4; i++)
	{
		addLayout(i + 3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), i * sizeof(glm::vec4));
		glVertexAttribDivisor(i + 3, 1);
	}
}