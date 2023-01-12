#pragma once

#include <glm.hpp>

#include "Camera.h"

class Player
{
public:
	Player();
	Camera camera;

	int chunkXPos;
	int chunkZPos;

	void update(unsigned int shader, sf::RenderWindow& window);
};