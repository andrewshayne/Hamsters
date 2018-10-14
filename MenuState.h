#pragma once

#include "GameState.h"

class MenuState : public GameState
{
private:
	sf::Text stateText;
	sf::Font font;
public:
	MenuState(Game &game, sf::RenderWindow &window);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void handlePlayerInput(sf::Mouse::Button button, bool isPressed, const sf::Vector2i mousePosition);
	void handlePlayerInputScroll(float scrollDelta, const sf::Vector2i mousePosition);

	void update(sf::Time dt, const sf::Vector2i& mousePosition);
	void draw();
};
