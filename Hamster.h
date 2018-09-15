#include <SFML/Graphics.hpp>

#include "CollisionBox.h"

#pragma once

struct Stats
{

	//intention is to have: (all from various LVLs)
	//	basic stats (start with random presets, effected by the environment)
	//	- some hidden
	//	- some piped into meters
	//
	//	calculated stats
	//	- derived from basic stats
	//	- some hidden, some meter

	//meter - just list all viable options now, some values will be dependent

	//basic stats
	unsigned int hunger;
	unsigned int thirst;
	unsigned int happiness;
	unsigned int obesity;
	unsigned int intelligence;
	unsigned int evil;

	//calculated stats

};

class Hamster
{
private:
	unsigned points; //this increments somehow, use to tell hamster's LVL
	Stats stats;
	std::string name;
	sf::Text nameText;
	sf::Vector2i currentGridPosition;
	sf::Vector2f position;

	sf::RectangleShape hamsterRect;
	CollisionBox box;

	sf::Time timer;

public:
	Hamster(sf::Vector2f position, std::string name);
	~Hamster();
	void update(sf::Time dt);

	unsigned int getLVL();
	std::string getName();
	void setName(std::string name);
	sf::RectangleShape& getHamsterRect();
	sf::Text& getNameText();
};

