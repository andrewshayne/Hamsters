#pragma once

#include <boost/filesystem.hpp>

#include "GameState.h"

namespace fs = ::boost::filesystem;

class MenuState : public GameState
{
private:
	sf::Text stateText;
	sf::Font font;
	std::vector<std::string> saveFiles;
public:
	MenuState(Game &game, sf::RenderWindow &window);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void handlePlayerInput(sf::Mouse::Button button, bool isPressed, const sf::Vector2i mousePosition);
	void handlePlayerInputScroll(float scrollDelta, const sf::Vector2i mousePosition);
	void getSaveFiles();

	void update(sf::Time dt, const sf::Vector2i& mousePosition);
	void guiUpdate();
	void draw();
};
