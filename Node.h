#include <SFML/Graphics.hpp>

#pragma once

namespace std {
	template<> struct hash<sf::Vector2f>
	{
		std::size_t operator()(const sf::Vector2f& v) const
		{
			return std::hash<std::string>()(std::to_string(v.x) + std::to_string(v.y));
		}
	};
}

class Node
{
public:

	//hold a bunch of stats at a Node that cells and the room can average/calculate?
	sf::Vector2f relativeCellPosition; //position relative to the centroid of the cell (0,0)
	sf::CircleShape circle;
	std::vector<Node*> neighbors;

	//vector of pairs(?) of <Node*, OutgoingAnimationState&, ...>

	Node(sf::Vector2f cellPosition, sf::Vector2f relPosition);
	~Node();

	std::string getKey();
};

