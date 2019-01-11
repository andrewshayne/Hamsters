#include <SFML/Graphics.hpp>

#include <unordered_map>

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

struct Stats
{
	int food;	//describes the food level at this node
	int water;	//"				water "
	int fun;	//"				fun   "
	std::unordered_map<std::string,int> factionTurfScore; //<factionName,turfScore> : shows how much turf every faction owns on this node

	Stats()
	{
		food = 0;
		water = 0;
		fun = 0;
		//...
	}
};

class Node
{
public:

	//hold a bunch of stats at a Node that cells and the room can average/calculate?
	sf::Vector2f relativeCellPosition; //position relative to the centroid of the cell (0,0)
	sf::CircleShape circle;
	sf::CircleShape highlightCircle;
	std::string roomKey;
	std::vector<Node*> neighbors;
	Stats stats;

	//vector of pairs(?) of <Node*, OutgoingAnimationState&, ...>

	Node(sf::Vector2f cellPosition, sf::Vector2f relPosition, std::string roomKey);
	~Node();

	std::string getKey();
	Stats getStats();
};

