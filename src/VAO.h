#pragma once

#include "VBO.h"
#include <glm.hpp>

class VAO
{
public:
	unsigned int rendererID;
	VAO();
	~VAO();

	void addBuffer(VBO& vbo);
	void addLayout(int index, int countDistance, int glType, int glNormalize, int stride, int offset);
	void bind();
	void unbind();

	void setupForInstances();
};