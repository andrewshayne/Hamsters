#include "Node.h"

#include <iostream>


Node::Node(sf::Vector2f cellPosition, sf::Vector2f relPosition)
{
	circle.setFillColor(sf::Color::Green);
	circle.setRadius(8.f);
	circle.setPosition(cellPosition.x + relativeCellPosition.x, cellPosition.y + relativeCellPosition.y);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	getKey();
}

Node::~Node()
{
}

std::string Node::getKey()
{
	std::cout << std::to_string(circle.getPosition().x) + std::to_string(circle.getPosition().y) << std::endl;
	return std::to_string(circle.getPosition().x) + std::to_string(circle.getPosition().y);
}
