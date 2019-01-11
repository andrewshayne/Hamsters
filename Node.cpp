#include "Node.h"

#include <iostream>


Node::Node(sf::Vector2f cellPosition, sf::Vector2f relPosition, std::string roomKey)
{
	circle.setFillColor(sf::Color::Green);
	circle.setRadius(6.f);
	circle.setPosition(cellPosition.x + relativeCellPosition.x, cellPosition.y + relativeCellPosition.y);
	circle.setOrigin(circle.getRadius(), circle.getRadius());

	highlightCircle.setFillColor(sf::Color::Transparent);
	highlightCircle.setOutlineColor(sf::Color::Black);
	highlightCircle.setOutlineThickness(20.f);
	highlightCircle.setRadius(120.f);
	highlightCircle.setPosition(cellPosition.x + relativeCellPosition.x, cellPosition.y + relativeCellPosition.y);
	highlightCircle.setOrigin(highlightCircle.getRadius(), highlightCircle.getRadius());

	this->roomKey = roomKey;
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

Stats Node::getStats()
{
	return stats;
}
