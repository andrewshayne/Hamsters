#include <SFML/Graphics.hpp>

#include "CollisionBox.h"

#pragma once
class Hamster
{
private:
	std::string name;
	sf::Vector2i currentGridPosition;
	sf::Vector2f position;

	sf::RectangleShape hamsterRect;
	CollisionBox box;

	sf::Time timer;

public:
	Hamster(sf::Vector2f position);
	~Hamster();
	void update(sf::Time dt);

	std::string getName();
	void setName(std::string name);
	sf::RectangleShape& getHamsterRect();
};

