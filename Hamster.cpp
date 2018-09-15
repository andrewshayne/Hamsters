#include "Hamster.h"



Hamster::Hamster(sf::Vector2f position, std::string name) : points(1000), position(position), name(name)
{
	hamsterRect.setSize(sf::Vector2f(16.f, 16.f));
	hamsterRect.setOrigin(hamsterRect.getPosition().x + hamsterRect.getSize().x / 2, hamsterRect.getPosition().y + hamsterRect.getSize().x / 2);
	hamsterRect.setPosition(position);
	hamsterRect.setFillColor(sf::Color::Yellow);

	nameText.setString(name);
	//nameText.setFont();
	nameText.setPosition(sf::Vector2f(position.x, position.y - 20.f));
}


Hamster::~Hamster()
{
}

unsigned Hamster::getLVL() //figure out points later, probably adjust the numbers in this function
{
	if		(points < 2000)	return 1;
	else if	(points < 3000)	return 2;
	else if	(points < 4000)	return 3;
	else if	(points < 5000)	return 4;
	else 					return 5;
}

void Hamster::update(sf::Time dt)
{
	nameText.setPosition(hamsterRect.getPosition()); //update text pos to rect pos
}

std::string Hamster::getName()
{
	return name;
}

void Hamster::setName(std::string name)
{
	this->name = name;
}

sf::RectangleShape& Hamster::getHamsterRect()
{
	return hamsterRect;
}

sf::Text& Hamster::getNameText()
{
	return nameText;
}
