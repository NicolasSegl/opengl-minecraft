#include "Display.h"

#include <iostream>

using namespace std;

Display::Display()
{
	// create context settings for window
	sf::ContextSettings windowSettings;
	windowSettings.depthBits = 24;
	windowSettings.stencilBits = 8;
	windowSettings.antialiasingLevel = 0;
	windowSettings.majorVersion = 3;
	windowSettings.minorVersion = 3;

	// create and initialize window and openGL
	window.create(sf::VideoMode::getDesktopMode(), "new mc", sf::Style::Fullscreen, windowSettings);
	glewInit();
	sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
	
	window.setMouseCursorVisible(false);
	glViewport(0, 0, window.getSize().x, window.getSize().y);
	window.setActive(true);
}