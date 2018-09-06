#include "Hamster.h"



Hamster::Hamster(sf::Vector2f position)
{
	this->position = position;
	hamsterRect.setSize(sf::Vector2f(16.f, 16.f));
	hamsterRect.setOrigin(hamsterRect.getPosition().x + hamsterRect.getSize().x / 2, hamsterRect.getPosition().y + hamsterRect.getSize().x / 2);
	hamsterRect.setPosition(position);
	hamsterRect.setFillColor(sf::Color::Yellow);
}


Hamster::~Hamster()
{
}

void Hamster::update(sf::Time dt)
{
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
