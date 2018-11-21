#include <unordered_map>

#include "Hamster.h"
#include <iostream>

#pragma once

// later allow rooms to be contstructed using a list of cell info!!

//portal or porthole?
enum PortalDirection { N, E, S, W };



struct Cell
{
	Node* destination;
	std::vector<Node*> waypoints;

	sf::Vector2i parentCoordinate;
	std::string parentKey;
	std::string gridKey;
	sf::Vector2i relativeCoordinate; //0,0 for master cell
	sf::Vector2i gridCoordinate;
	//need to know if cells are linked to eachother in a room or connected to another room!!
	Cell* neighborCell[4]; //if nullptr, no portal OR unusable portal, else has neighbor cell
	sf::Vector2f portalCoordinates[4]; //the (abs?) coords of this portal? ... necessary? probably...
	sf::RectangleShape portalRects[4];
	bool* isOutgoingPortal; //determines if a portal is here (CANNOT EXIST WITHOUT COLLIDABLE WALL)
	bool* isCollidableWall; //determines if open wall or connected interior

	std::unordered_map<std::string,Hamster*> hamsters;

	sf::Vector2i defaultSize;
	sf::RectangleShape rect;
	sf::Sprite bgSprite;
	sf::Texture bgTexture;

	sf::Font font;
	sf::Text hamsterCountText;
	//initialize with relative position, 0,0 indicating master
	Cell(sf::Vector2f cellSize, sf::Vector2i relativePosition, sf::Vector2i masterCellPosition, bool isOutGoingPortal[4], bool isCollidableWall[4], std::string filename) : defaultSize(cellSize),
		relativeCoordinate(relativePosition), parentCoordinate(masterCellPosition), gridCoordinate(masterCellPosition.x + relativePosition.x, masterCellPosition.y + relativePosition.y),
		isOutgoingPortal(isOutGoingPortal), isCollidableWall(isCollidableWall)
	{
		parentKey = std::to_string(parentCoordinate.x) + std::to_string(parentCoordinate.y);
		gridKey = std::to_string(gridCoordinate.x) + std::to_string(gridCoordinate.y);
		neighborCell[N] = neighborCell[E] = neighborCell[S] = neighborCell[W] = nullptr;
		portalCoordinates[N] = sf::Vector2f(gridCoordinate.x, gridCoordinate.y - 0.4f);
		portalCoordinates[E] = sf::Vector2f(gridCoordinate.x + 0.4f, gridCoordinate.y);
		portalCoordinates[S] = sf::Vector2f(gridCoordinate.x, gridCoordinate.y + 0.4f);
		portalCoordinates[W] = sf::Vector2f(gridCoordinate.x - 0.4f, gridCoordinate.y);
		// isOutgoingPortal[N] = isOutgoingPortal[E] = isOutgoingPortal[S] = isOutgoingPortal[W] = false;
		// isCollidableWall[N] = isCollidableWall[E] = isCollidableWall[S] = isCollidableWall[W] = true;

		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Magenta);
		rect.setOutlineThickness(-4.f);
		rect.setSize((sf::Vector2f)defaultSize);
		rect.setPosition(gridCoordinate.x * defaultSize.x + defaultSize.x / 2.f, gridCoordinate.y * defaultSize.y + defaultSize.y / 2.f);
		rect.setOrigin(rect.getSize().x / 2.f, rect.getSize().y / 2.f);

		portalRects[N].setSize(sf::Vector2f(8.f, 16.f));
		portalRects[E].setSize(sf::Vector2f(16.f, 8.f));
		portalRects[S].setSize(sf::Vector2f(8.f, 16.f));
		portalRects[W].setSize(sf::Vector2f(16.f, 8.f));
		for (int i = 0; i < 4; ++i)
		{
			portalRects[i].setFillColor(sf::Color::Transparent);
			portalRects[i].setOrigin(portalRects[i].getSize().x / 2, portalRects[i].getSize().y / 2);
			portalRects[i].setPosition(portalCoordinates[i].x * defaultSize.x * 2 + defaultSize.x/2, portalCoordinates[i].y * defaultSize.y * 2 + defaultSize.x/2);
		}
		portalRects[N].setPosition(-8 + rect.getPosition().x, rect.getPosition().y - rect.getSize().y/2);
		portalRects[E].setPosition(rect.getPosition().x + rect.getSize().x/2, 8 + rect.getPosition().y);
		portalRects[S].setPosition(8 + rect.getPosition().x, rect.getPosition().y + rect.getSize().y/2);
		portalRects[W].setPosition(rect.getPosition().x - rect.getSize().x/2, -8 + rect.getPosition().y);

		font.loadFromFile("Fonts/BodoniFLF-Bold.ttf");
		this->hamsterCountText.setString("0");
		this->hamsterCountText.setFont(font);
		this->hamsterCountText.setPosition(rect.getPosition().x - cellSize.x / 2.f, rect.getPosition().y - cellSize.y / 2.f);
		this->hamsterCountText.setCharacterSize(24);
		this->hamsterCountText.setFillColor(sf::Color::White);
		this->hamsterCountText.setOutlineColor(sf::Color::Black);
		this->hamsterCountText.setOutlineThickness(2.f);

		bgTexture.loadFromFile(filename);
		bgSprite.setTexture(bgTexture);
		bgSprite.setPosition(rect.getPosition().x - rect.getSize().x / 2.f, rect.getPosition().y - rect.getSize().y / 2.f);
		bgSprite.setScale(.2f, .2f);


		//default destination Node position = center
		destination = new Node(rect.getPosition(), { 0,0 }, getRelativeKey());
	}

	void addHamster(Hamster* hamster)
	{
		//std::cout << "added hamster to cell " << this->relativeCoordinate.x << ", " << this->relativeCoordinate.y << std::endl;
		hamsters[hamster->getName()] = hamster;
		hamsters[hamster->getName()]->setCurrentNode(destination); //change this to currentNode...
		hamsters[hamster->getName()]->setCurrentDest(nullptr); //change this to currentNode...

		//change if want to remove snap-to-center
		hamsters[hamster->getName()]->getHamsterRect().setPosition(this->rect.getPosition());
	}

	void removeHamster(Hamster* hamster)
	{
		//std::cout << "removed hamster from cell " << this->relativeCoordinate.x << ", " << this->relativeCoordinate.y << std::endl;
		hamsters.erase(hamster->getName());
	}

	std::string getRelativeKey()
	{
		//std::cout << "cells: " << std::to_string(relativeCoordinate.x) + std::to_string(relativeCoordinate.y) << std::endl;
		return std::to_string(relativeCoordinate.x) + std::to_string(relativeCoordinate.y);
	}

	sf::Sprite getSprite()
	{
		return bgSprite;
	}

	Node* getDestinationNode()
	{
		return destination;
	}
};

class Room
{
	//when dragging and dropping onto grid, display a line to the current nearest spot it will lock onto!
private:
	sf::Vector2i masterCellPosition;
	sf::Vector2f dimensions;
	std::unordered_map<std::string,Cell*> cells; //first cell is always the master cell

public:
	static const sf::Vector2f cellDimensions;

	Room(sf::Vector2i masterCellPosition); //may need a default constructor too for drag and drop
	~Room();

	std::string getKey();
	std::unordered_map<std::string,Cell*>& getCells();
	void connectCells();
};

