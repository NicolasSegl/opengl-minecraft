#pragma once

#include <glew.h>
#include <string>
#include <iostream>
#include <fstream>

#include "stb.h"

using namespace std;

class Texture
{
public:
	unsigned int rendererID;
	unsigned char* data;
	int uniformLoc;
	string filepath;

	Texture(const string& filepath);
	Texture() {}
	~Texture();

	unsigned int loadCubemap(string* faces);
	string* loadConfig(const string& filepath);

	void bind();
	void unbind();
};