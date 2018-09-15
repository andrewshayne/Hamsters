#include <SFML/Graphics.hpp>

#include <unordered_map>

#include "Hamster.h"

#pragma once

// later allow rooms to be contstructed using a list of cell info!!

//portal or porthole?
enum PortalDirection { N, E, S, W };

struct Cell
{
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

	//initialize with relative position, 0,0 indicating master
	Cell(sf::Vector2i cellSize, sf::Vector2i relativePosition, sf::Vector2i masterCellPosition, bool isOutGoingPortal[4], bool isCollidableWall[4]) : defaultSize(cellSize),
		relativeCoordinate(relativePosition),
		gridCoordinate(masterCellPosition.x + relativePosition.x, masterCellPosition.y + relativePosition.y),
		isOutgoingPortal(isOutGoingPortal),
		isCollidableWall(isCollidableWall)
	{
		neighborCell[N] = neighborCell[E] = neighborCell[S] = neighborCell[W] = nullptr;
		portalCoordinates[N] = sf::Vector2f(gridCoordinate.x, gridCoordinate.y - 0.4f);
		portalCoordinates[E] = sf::Vector2f(gridCoordinate.x + 0.4f, gridCoordinate.y);
		portalCoordinates[S] = sf::Vector2f(gridCoordinate.x, gridCoordinate.y + 0.4f);
		portalCoordinates[W] = sf::Vector2f(gridCoordinate.x - 0.4f, gridCoordinate.y);
		// isOutgoingPortal[N] = isOutgoingPortal[E] = isOutgoingPortal[S] = isOutgoingPortal[W] = false;
		// isCollidableWall[N] = isCollidableWall[E] = isCollidableWall[S] = isCollidableWall[W] = true;

		rect.setFillColor(sf::Color(255,0,0,180));
		rect.setSize((sf::Vector2f)defaultSize);
		rect.setOrigin(sf::Vector2f(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y / 2));
		rect.setPosition(gridCoordinate.x * defaultSize.x * 2 + defaultSize.x, gridCoordinate.y * defaultSize.y * 2 + defaultSize.y);

		portalRects[N].setSize(sf::Vector2f(4.f, 8.f));
		portalRects[E].setSize(sf::Vector2f(8.f, 4.f));
		portalRects[S].setSize(sf::Vector2f(4.f, 8.f));
		portalRects[W].setSize(sf::Vector2f(8.f, 4.f));
		for (int i = 0; i < 4; ++i)
		{
			portalRects[i].setFillColor(sf::Color::Transparent);
			portalRects[i].setOrigin(portalRects[i].getSize().x / 2, portalRects[i].getSize().y / 2);
			portalRects[i].setPosition(portalCoordinates[i].x * defaultSize.x * 2 + defaultSize.x/2, portalCoordinates[i].y * defaultSize.y * 2 + defaultSize.x/2);
		}
		portalRects[N].setPosition(rect.getPosition().x, rect.getPosition().y - rect.getSize().y/2);
		portalRects[E].setPosition(rect.getPosition().x + rect.getSize().x/2, rect.getPosition().y);
		portalRects[S].setPosition(rect.getPosition().x, rect.getPosition().y + rect.getSize().y/2);
		portalRects[W].setPosition(rect.getPosition().x - rect.getSize().x/2, rect.getPosition().y);

	}

	void addHamster(Hamster* hamster)
	{
		hamsters[hamster->getName()] = hamster;
		hamsters[hamster->getName()]->getHamsterRect().setPosition(this->rect.getPosition());
	}

	std::string getKey()
	{
		return std::to_string(relativeCoordinate.x) + std::to_string(relativeCoordinate.y);
	}
};

class Room
{
	//when dragging and dropping onto grid, display a line to the current nearest spot it will lock onto!
private:
	sf::Vector2i masterCellPosition;
	sf::Vector2f dimensions;
	const sf::Vector2i cellSize = sf::Vector2i(40,30);
	std::unordered_map<std::string,Cell*> cells; //first cell is always the master cell

public:
	Room(sf::Vector2i masterCellPosition); //may need a default constructor too for drag and drop
	~Room();

	std::string getKey();
	std::unordered_map<std::string,Cell*>& getCells();
	void connectCells();
};

