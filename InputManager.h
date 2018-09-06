#pragma once

#include <SFML/Graphics.hpp>

class InputManager
{
public:
	InputManager();
	~InputManager();

	sf::Vector2i getMousePosition(sf::RenderWindow &window);
	bool isKeyPressed(sf::Keyboard::Key);
};

