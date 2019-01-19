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


	//search for save files
	//push to list
	//...
	getSaveFiles();
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

void MenuState::handlePlayerInputScroll(float scrollDelta, const sf::Vector2i mousePosition)
{
}

void MenuState::getSaveFiles()
{
	fs::path root("./Savefiles");
	fs::directory_iterator end_itr;

	//cycle through directory
	for (fs::directory_iterator itr(root); itr != end_itr; ++itr)
	{
		//if not a directory, list it
		if (fs::is_regular_file(itr->path()))
		{
			std::string current_file = itr->path().string();
			saveFiles.push_back(current_file);
			//std::cout << current_file << std::endl;
		}
	}
}

void MenuState::update(sf::Time dt, const sf::Vector2i& mousePosition)
{

}

void MenuState::guiUpdate()
{
}

void MenuState::draw()
{
	sf::RenderWindow &window = *pWindow;
	window.clear();
	window.draw(stateText);

	for (int i = 0; i < saveFiles.size(); i++)
	{
		sf::Text* text = new sf::Text();
		text->setFont(font);
		text->setString(std::to_string(i + 1) + ")\t" + saveFiles.at(i));
		text->setCharacterSize(20);
		text->setPosition({ 100.f, 100.f + (i * 40.f) });
		text->setFillColor(sf::Color::White);
		window.draw(*text);
	}
}
