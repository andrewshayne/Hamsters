#include "MenuState.h"
#include "PlayState.h"

#include "Game.h"

#include <iostream>

MenuState::MenuState(Game &game, sf::RenderWindow &window) : GameState(game, window)
{
	font.loadFromFile("Fonts/BodoniFLF-Bold.ttf");
	stateText.setCharacterSize(20);
	stateText.setString("Hamster Game\n- Press space or enter");
	stateText.setFont(font);
}


void MenuState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if(key == sf::Keyboard::Key::Space || key == sf::Keyboard::Key::Return)
	{
		unique_ptr<PlayState> playState(new PlayState(*pGame, *pWindow));
		pGame->pushState(move(playState));
	}
}

void MenuState::handlePlayerInput(sf::Mouse::Button button, bool isPressed, const sf::Vector2i mousePosition)
{

}

void MenuState::update(sf::Time dt, const sf::Vector2i& mousePosition)
{

}

void MenuState::draw()
{
	sf::RenderWindow &window = *pWindow;
	window.clear();
	window.draw(stateText);
}
