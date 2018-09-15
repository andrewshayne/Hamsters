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
	//////////////////////////////////////////////////////////////////////////////////////////////world.otherKeyInput(key, isPressed);
	//world.movePlayer(key, isPressed);
}

void PlayState::handlePlayerInput(sf::Mouse::Button button, bool isPressed, const sf::Vector2i mousePosition) //for mouse input
{
	if(button == sf::Mouse::Left)
	{
		//add sectors later to increase performance? (collision detection)

		//world.addCircle(mousePosition.x, mousePosition.y);
		//world.playClickSound();


		world.handleLeftClick();
	}
	if(button == sf::Mouse::Right)
	{
		//world.addPart(mousePosition);
	}
	if(button == sf::Mouse::Middle)
	{
		cout << mousePosition.x << ", " << mousePosition.y << endl;
		//world.clearCircles();
	}
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
