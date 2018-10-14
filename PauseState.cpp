#include "PauseState.h"

#include "Game.h"

#include <iostream>

PauseState::PauseState(Game &game, sf::RenderWindow &window) : GameState(game, window),
	resumeGame(true),
	select(false)
{
	font.loadFromFile("Fonts/BodoniFLF-Bold.ttf");
	stateText.setString("Paused");
	stateText.setFont(font);

	resumeText.setString("Resume");
	resumeText.setPosition((float)(window.getSize().x / 2), (float)(window.getSize().y / 2));
	resumeText.setFont(font);

	exitText.setString("Exit");
	exitText.setPosition((float)(window.getSize().x / 2) + 20.f, (float)(window.getSize().y / 2) + 26.f);
	exitText.setFont(font);

	selectIndicator.setFillColor(sf::Color::Red);
	selectIndicator.setPosition(resumeText.getPosition().x - 10, resumeText.getPosition().y + 14);
	selectIndicator.setRadius(4);
}


void PauseState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	//if esc, go back to playState
	if((key == sf::Keyboard::Key::Space || key == sf::Keyboard::Key::Return) && isPressed)
	{
		select = true;
	}
	if((key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::Down) && isPressed)
	{
		resumeGame = !resumeGame;
	}
}

void PauseState::handlePlayerInput(sf::Mouse::Button button, bool isPressed, const sf::Vector2i mousePosition)
{

}

void PauseState::handlePlayerInputScroll(float scrollDelta, const sf::Vector2i mousePosition)
{
}

void PauseState::update(sf::Time dt, const sf::Vector2i& mousePosition)
{
	if(resumeGame)
	{
		selectIndicator.setPosition(resumeText.getPosition().x - 10, resumeText.getPosition().y + 14);
		resumeText.setFillColor(sf::Color::Red);
		exitText.setFillColor(sf::Color::White);
		if(select)
			pGame->popState();
	}
	else
	{
		selectIndicator.setPosition(exitText.getPosition().x - 10, exitText.getPosition().y + 14);
		resumeText.setFillColor(sf::Color::White);
		exitText.setFillColor(sf::Color::Red);
		if(select)
			exit(1);
	}
}

void PauseState::draw()
{
	//transparent overlay and "pause"
	sf::RenderWindow &window = *pWindow;
	window.clear();
	window.draw(resumeText);
	window.draw(exitText);
	window.draw(selectIndicator);
	window.draw(stateText);
}
