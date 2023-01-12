#pragma once
#include <vector>
#include <string>
#include <glew.h>
#include <sstream>
#include <fstream>
#include <iostream>

#define TEST_SHADER shaderHandler.shaderIDs[(int)ShaderHandler::Shader::TEST]
#define BLOCK_SHADER shaderHandler.shaderIDs[(int)ShaderHandler::Shader::BLOCK]
#define WATER_SHADER shaderHandler.shaderIDs[(int)ShaderHandler::Shader::WATER]

using namespace std;

class ShaderHandler
{
public:

	enum class Shader
	{
		TEST = 0,
		BLOCK = 1,
		WATER = 2,
		SKYBOX = 3,
	};

	vector<unsigned int> shaderIDs;

	ShaderHandler();

	void parseShader(const string& filepath, string* vertexShader, string* fragmentShader);
	unsigned int compileShader(unsigned int shaderType, const string& shaderSrc);
	unsigned int createShader(const string& filepath);
	void useShader(int id);
};