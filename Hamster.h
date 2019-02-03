#include "CollisionBox.h"
#include "Node.h"

#include <unordered_map>
#include <math.h>
#include <iostream>


#include <fstream>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unordered_map.hpp>


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

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	  ar & hunger;
	  ar & thirst;
	  ar & happiness;
	  ar & obesity;
	  ar & intelligence;
	  ar & evil;
	}
};

class Hamster
{
private:
	friend class boost::serialization::access;
	// When the class Archive corresponds to an output archive, the
	// & operator is defined similar to <<.  Likewise, when the class Archive
	// is a type of input archive the & operator is defined similar to >>.
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		//posX = sprite.getPosition().x;
		//posY = sprite.getPosition().y;
		ar & posX; //need to get this from its texture coord... ALSO need to save it's texture, etc.
		ar & posY; //need to get this from its texture coord... ALSO need to save it's texture, etc.
		ar & stats;
	}

	Node* currentNode;
	Node* currentDest;
	static const float scale;
	sf::Texture hamsterTexture;
	sf::Sprite sprite;
	float posX; //only used to indicate save/load position?
	float posY; //only used to indicate save/load position?
	bool isPathing;
	int pathCounter;
	std::string roomKey;
	std::vector<Node*> path;
	Hamster* interactionPartner;

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
	Hamster(sf::Vector2f position, std::string name); //used in store components
	Hamster(Hamster* hamster, std::string name); //copy constructor (purchase)
	Hamster(); //default constructor for file read-in
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
	//std::vector<Node*> getPath();

	void setInteractionPartner(Hamster* partner);
};

