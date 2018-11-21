#include "CollisionBox.h"
#include "Node.h"

#include <unordered_map>
#include <math.h>
#include <iostream>

#pragma once

struct HamsterStats
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
	int hunger;
	int thirst;
	int happiness;
	int obesity;
	int intelligence;
	int evil;
	
	std::vector<std::string> factionNames; //list of factions this hamster is part of
	std::unordered_map<std::string, int> affection; //<hamsterName,affectionScore> : shows how fond of each hamster this hamster is

	//calculated stats


	HamsterStats()
	{
		hunger = 0;
		thirst = 0;
		happiness = 0;
		obesity = 0;
		intelligence = 0;
		evil = 0;
	}

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
	std::string roomKey;
	std::vector<Node*> path;

	unsigned points; //this increments somehow, use to tell hamster's LVL
	HamsterStats stats;
	std::string name;
	sf::Text nameText;
	sf::Font font;
	sf::Vector2i currentGridPosition;

	sf::RectangleShape hamsterRect;
	CollisionBox box;

	sf::Time timer;

public:
	bool updateRoomKey;
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
	HamsterStats& getStats();

	Node* getCurrentNode();
	Node* getCurrentDest();
	bool getIsPathing();
	void setCurrentNode(Node* node);
	void setCurrentDest(Node* node);
	void setRoomKey(std::string roomKey);
	void traverse(Node* start, Node* finish);
	void setPath(std::vector<Node*> path);
	void clearPath();
	std::vector<Node*> getPath();
};

