#include "Camera.h"

Camera::Camera()
{
	position = glm::vec3(0, 10, 0);
}

void Camera::computeMatricesFromInputs(sf::RenderWindow& window)
{
	// use this so it updates based off of time not the number of frames
	// this is to calculate delta time
	static sf::Clock clock;
	sf::Time time = clock.getElapsedTime();
	static double lastTime = (double)time.asSeconds();
	double currentTime = (double)time.asSeconds();
	float deltaTime = float(currentTime - lastTime);

	// gets the mouse position
	static double xPos = window.getSize().x / 2;
	static double yPos = window.getSize().y / 2;

	// because of sfml, i have to find delta mouse positions and then add them to the x-Position and y-Position
	double mx = sf::Mouse::getPosition(window).x;
	double my = sf::Mouse::getPosition(window).y;

	double dx = window.getSize().x / 2 - mx;
	double dy = window.getSize().y / 2 - my;

	xPos -= dx;
	yPos -= dy;

	// compute the new orientation of the camera (the angle at which it is looking)
	horizontalAngle = mouseSpeed * float(window.getSize().x / 2 - xPos);
	verticalAngle = mouseSpeed * float(window.getSize().y / 2 - yPos);

	// calculate the direction; spherical coordinates to cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// calculate the right vector. complicated camera 3d math shit...
	glm::vec3 right = glm::vec3
	(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// calculate the up vector. also very complicated 3d camera shit
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		position += direction * deltaTime * speed;
	// Move backward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
		position -= direction * deltaTime * speed;
	// Strafe right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
		position += right * deltaTime * speed;
	// Strafe left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		position -= right * deltaTime * speed;

	float fov = initialFOV;

	// projection matrix : 90 degree field of view, 4:3 ratio, display range : 0.1 units to 200 units
	projectionMatrix = glm::perspective(glm::radians(fov), 4.0f / 3.0f, 0.1f, 200.0f);

	// camera matrix
	viewMatrix = glm::lookAt
	(
		position, // camera is here
		position + direction, // and looks here
		up // head is up
	);

	sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));

	lastTime = currentTime;
}

void Camera::update(unsigned int shader, sf::RenderWindow& window)
{
	computeMatricesFromInputs(window);
	
	// get shader uniforms and fill them with the appropriate matrices
	int viewLoc = glGetUniformLocation(shader, "view");
	int projectionLoc = glGetUniformLocation(shader, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
}