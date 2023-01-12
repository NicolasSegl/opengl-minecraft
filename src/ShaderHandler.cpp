#include "ShaderHandler.h"

// reads through the shader files and puts them into strings
void ShaderHandler::parseShader(const string& filepath, string* vertexShader, string* fragmentShader)
{
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
	};

	ShaderType type = ShaderType::NONE;
	stringstream ss[2];
	string line;
	ifstream file(filepath);

	// search for keywords to indicate the end of the files.
	while (getline(file, line))
	{
		if (line.find("shader") != string::npos)
		{
			if (line.find("fragment") != string::npos)
				type = ShaderType::FRAGMENT;
			else if (line.find("vertex") != string::npos)
				type = ShaderType::VERTEX;
		}
		else
			ss[(int)type] << line << '\n';
	}

	// change the output arguments to the strings read in from the filepath
	*vertexShader = ss[(int)ShaderType::VERTEX].str();
	*fragmentShader = ss[(int)ShaderType::FRAGMENT].str();
}

unsigned int ShaderHandler::compileShader(unsigned int shaderType, const string& shaderSrc)
{
	// create a shader then fill it with the source code parsed in from the file then compile it
	unsigned int shaderID = glCreateShader(shaderType);
	const char* src = &shaderSrc[0];
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);

	// error checking for the shader file
	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		// find the error message produced
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(shaderID, length, &length, message);
		
		// output message to the console and delete the shader and message
		cout << message << endl;
		delete[] message;
		glDeleteShader(shaderID);
		return 0;
	}

	return shaderID;
}

unsigned int ShaderHandler::createShader(const string& filepath)
{
	unsigned int programID = glCreateProgram();
	
	// store shader file's source code into strings and compile them
	string vertexShader, fragmentShader;
	parseShader(filepath, &vertexShader, &fragmentShader);
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	// compile and create the shader program
	glAttachShader(programID, vs);
	glAttachShader(programID, fs);
	glLinkProgram(programID);
	glValidateProgram(programID);

	// cleanup
	glDeleteShader(vs);
	glDeleteShader(fs);
	shaderIDs.push_back(programID);
	return programID;
}

// this construcor makes a basic shader. used for early testing, can be deleted later
ShaderHandler::ShaderHandler()
{
	createShader("testShader.shader");
	createShader("cubemapShader.shader");
	createShader("waterShader.shader");
}

void ShaderHandler::useShader(int id)
{
	glUseProgram(id);
}