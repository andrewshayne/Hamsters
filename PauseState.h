#pragma once

#include "GameState.h"

class PauseState : public GameState
{
private:
	sf::Text stateText;
	sf::Font font;

	sf::Text resumeText;
	sf::Text exitText;

	sf::CircleShape selectIndicator;

	bool resumeGame;
	bool select;
public:
	PauseState(Game &game, sf::RenderWindow &window);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void handlePlayerInput(sf::Mouse::Button button, bool isPressed, const sf::Vector2i mousePosition);
	void handlePlayerInputScroll(float scrollDelta, const sf::Vector2i mousePosition);

	void update(sf::Time dt, const sf::Vector2i& mousePosition);
	void guiUpdate();
	void draw();
};

