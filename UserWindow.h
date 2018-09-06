#include <SFML/Graphics.hpp>

#include <unordered_map>

#pragma once

struct WindowComponent
{
	sf::Font font;
	sf::Text title;
	sf::RectangleShape rect;
	std::unordered_map< std::string, std::pair<sf::Text, sf::Text> > attributes;

	WindowComponent(sf::Vector2f position, std::string title)
	{
		font.loadFromFile("Fonts/BodoniFLF-Bold.ttf");
		this->title.setString(title);
		this->title.setFont(font);
		this->title.setPosition(position);
		this->title.setCharacterSize(20);

		this->rect.setPosition(position);
	}
};

class UserWindow
{
private:
	sf::RectangleShape windowRect;
public:
	UserWindow(sf::Vector2f position, sf::Vector2f size);

	sf::RectangleShape& getWindowRect();
	std::unordered_map<std::string, WindowComponent*> componentMap;
};

