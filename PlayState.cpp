#include "PlayState.h"
#include "PauseState.h"

#include "Game.h"

#include <iostream>

PlayState::PlayState(Game &game, sf::RenderWindow &window) : GameState(game, window), world(window)
{
	font.loadFromFile("Fonts/BodoniFLF-Bold.ttf");
	stateText.setString("Playing - Hit esc to pause");
	//stateText.setString("Playing - Hit esc to pause\n\tM - toggle map mode");
	stateText.setFont(font);
}


void PlayState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) //for keyboard input
{
	if(key == sf::Keyboard::Key::Escape)
	{
		unique_ptr<PauseState> pauseState(new PauseState(*pGame, *pWindow));
		pGame->pushState(move(pauseState));
	}

	if (isPressed && (key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::Right || key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::Down)) //move the camera
	{
		world.moveCamera(key);
	}
}

void PlayState::handlePlayerInput(sf::Mouse::Button button, bool isPressed, const sf::Vector2i mousePosition) //for mouse input
{
	if(button == sf::Mouse::Left)
	{
		world.handleLeftClick(isPressed, mousePosition);
	}
	if(button == sf::Mouse::Right)
	{
		world.handleRightClick(isPressed, mousePosition);
	}
}

void PlayState::handlePlayerInputScroll(float scrollDelta, const sf::Vector2i mousePosition)
{
	world.handleScroll(scrollDelta, mousePosition);
}

void PlayState::update(sf::Time dt, const sf::Vector2i& mousePosition)
{
	world.update(dt, mousePosition);
}

void PlayState::draw()
{
	sf::RenderWindow &window = *pWindow;
	world.draw();
	window.draw(stateText);
}
