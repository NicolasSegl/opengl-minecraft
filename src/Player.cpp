#include "Player.h"

Player::Player()
{
	chunkXPos = 0;
	chunkZPos = 0;
}

void Player::update(unsigned int shader, sf::RenderWindow& window)
{
	chunkXPos = camera.position.x / 16;
	chunkZPos = camera.position.z / 16;

	camera.update(shader, window);
}