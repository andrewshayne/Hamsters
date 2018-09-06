#include <SFML/Graphics.hpp>

#pragma once
class CollisionBox
{
public:
	sf::RectangleShape rect;
	CollisionBox();
	~CollisionBox();

	bool checkMouseHover(sf::Vector2i mousePos);
};

