#pragma once

#include "GameState.h"
#include "World.h"

class PlayState : public GameState
{
private:
	World world;

	sf::Text stateText;
	sf::Font font;

public:
	PlayState(Game &game, sf::RenderWindow &window);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void handlePlayerInput(sf::Mouse::Button button, bool isPressed, sf::Vector2i mousePosition);

	void update(sf::Time dt, sf::Vector2i& mousePosition);
	void draw();
};

