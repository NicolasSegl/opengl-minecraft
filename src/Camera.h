#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <SFML/Graphics.hpp>
#include <glew.h>
#include <iostream>

#include "ShaderHandler.h"

using namespace std;

class Camera
{
public:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	// lots of boiler plate high-level math shit right here
	float horizontalAngle = 3.14;
	float verticalAngle = 0.0f;
	float initialFOV = 90.0f;

	glm::vec3 position;
	Camera();

	// units per second
	float speed = 30.0f;
	// change this to change the sensitivity
	float mouseSpeed = 0.001f;

	void computeMatricesFromInputs(sf::RenderWindow& window);
	void update(unsigned int shader, sf::RenderWindow& window);
};