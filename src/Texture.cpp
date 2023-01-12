#include "Texture.h"

Texture::Texture(const string& filepath)
{
	string* faces = loadConfig(filepath);
	rendererID = loadCubemap(faces);
}

Texture::~Texture()
{
	glDeleteTextures(1, &rendererID);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, rendererID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

string* Texture::loadConfig(const string& filepath)
{
	fstream file(filepath);
	string line;
	string* faces = new string[6];
	int counter = 0;

	while (getline(file, line))
	{
		faces[counter] = line;
		counter++;
	}

	return faces;
}

unsigned int Texture::loadCubemap(string* faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	// < 6 because a cube has 6 sides
	for (unsigned int i = 0; i < 6; i++)
	{
		// configure stbi and load the face's image
		stbi_set_flip_vertically_on_load(false);
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 4);
		if (data)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			cout << "Error loading cubemap image.\n";
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	return textureID;
}