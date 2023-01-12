#pragma once

#include "Display.h"
#include "ShaderHandler.h"
#include "VAO.h"
#include "VBO.h"
#include "Player.h"
#include "Block.h"
#include "Renderer.h"
#include "Texture.h"
#include "BufferHandler.h"
#include "ChunkHandler.h"

#include <thread>

using namespace std;

class Application
{
public:
	Display display;
	ShaderHandler shaderHandler;
	Renderer renderer;
	Camera camera;

	BufferHandler bufferHandler;
	ChunkHandler chunkHandler;
	Player player;

	Application();
	void run();
	void handleEvents();

	void foo() {}
};