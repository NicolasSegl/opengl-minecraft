#pragma once

#include <glew.h>

class VBO
{
public:
	unsigned int rendererID;

	VBO();
	~VBO();
	VBO(unsigned int size, void* data);

	void addBuffer(unsigned int size, const void* data);
	void bind();
	void unbind();
};