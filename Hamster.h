#include "CollisionBox.h"
#include "Node.h"

#include <unordered_map>
#include <iostream>

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
	Node* currentNode;
	Node* currentDest;
	static const float scale;
	sf::Texture hamsterTexture;
	sf::Sprite sprite;
	bool isPathing;
	int pathCounter;
	std::vector<Node*> path;

	unsigned points; //this increments somehow, use to tell hamster's LVL
	Stats stats;
	std::string name;
	sf::Text nameText;
	sf::Font font;
	sf::Vector2i currentGridPosition;

	sf::RectangleShape hamsterRect;
	CollisionBox box;

	sf::Time timer;

public:
	sf::VertexArray vta;
	Hamster(sf::Vector2f position, std::string name);
	Hamster(Hamster* hamster, std::string name);
	~Hamster();
	void update(sf::Time dt, std::unordered_map<sf::Vector2f,Node*>);

	unsigned int getLVL();
	std::string getName();
	void setName(std::string name);
	sf::RectangleShape& getHamsterRect();
	sf::Text& getNameText();
	sf::Sprite& getSprite();

	Node* getCurrentNode();
	Node* getCurrentDest();
	bool getIsPathing();
	void setCurrentNode(Node* node);
	void setCurrentDest(Node* node);
	void traverse(Node* start, Node* finish);
	void setPath(std::vector<Node*> path);
	void clearPath();
	std::vector<Node*> getPath();
};

