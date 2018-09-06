#include "InputManager.h"



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

sf::Vector2i InputManager::getMousePosition(sf::RenderWindow & window)
{
	return sf::Mouse::getPosition(window);
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		return true;
	}
	return false;
}