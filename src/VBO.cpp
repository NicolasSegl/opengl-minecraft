#include "VBO.h"

VBO::VBO()
{
	glGenBuffers(1, &rendererID);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &rendererID);
}

VBO::VBO(unsigned int size, void* data)
{
	// bind and fill the buffer with data
	glGenBuffers(1, &rendererID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void VBO::addBuffer(unsigned int size, const void* data)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}