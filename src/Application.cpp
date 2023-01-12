#include "Application.h"

void Application::handleEvents()
{
	sf::Event event;
	while (display.window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			display.window.close();
		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Escape)
				display.window.close();
	}
}

Application::Application()
{
	// ye fam poom poom
	chunkHandler = ChunkHandler(&bufferHandler);
	chunkHandler.generateChunkData(0, 0);
	chunkHandler.generateChunks(player);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void Application::run()
{
	shaderHandler.useShader(BLOCK_SHADER);
	int alphaLoc = glGetUniformLocation(BLOCK_SHADER, "alpha");
	glUniform1f(alphaLoc, 1.0f);

	while (display.window.isOpen())
	{
		handleEvents();
		renderer.clear();
		player.update(BLOCK_SHADER, display.window);

		chunkHandler.generateChunks(player);

		// fuck you multithreading
		//chunkHandler.generateThread(false, player);
		bufferHandler.update();

		renderer.renderOpaqueBlocks(bufferHandler, shaderHandler);

		display.window.display();
	}
}