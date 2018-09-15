#pragma once

#include <SFML/Graphics.hpp>

class Game;

class GameState
{
public:
	GameState(Game &game, sf::RenderWindow &w);

	sf::RenderWindow* pWindow;

	virtual void handlePlayerInput(sf::Keyboard::Key key, bool isPressed) = 0;
	virtual void handlePlayerInput(sf::Mouse::Button button, bool isPressed, const sf::Vector2i mousePosition) = 0;

	virtual void update(sf::Time dt, const sf::Vector2i& mousePosition) = 0;
	virtual void draw() = 0;

protected:
	Game *pGame;
};

