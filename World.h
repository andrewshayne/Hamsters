#include <SFML/Graphics.hpp>

#include "Room.h"
#include "Hamster.h"

#include "InputManager.h"
#include "Overlay.h"

#pragma once
class World
{
private:
	bool isAdminMode;
	InputManager inputManager;

	sf::RenderTarget& target;
	sf::View worldView;
	sf::View minimapView; //show where the camera is positioned/zoomed relative to the entire map

	sf::Sprite* backgroundSprite;
	sf::Texture backgroundImage;

	Overlay* overlay;

	int rows = 8;
	int cols = 8;
	Cell*** grid; //matrix of cell pointers (pointer to array of pointers to arrays of cell pointers)
	std::vector<sf::RectangleShape*> cellContainers;

	Room* room1;
	Room* room2;
	std::unordered_map<std::string,Room*> rooms; //change this to map, use "XY" coords as key?
	std::unordered_map<std::string,Hamster*> hamsters;

	bool isHoldingHamster;
	Hamster* currentlyHoveredHamster;
	Cell* currentlyHoveredCell;
	//std::map ??
public:
	explicit World(sf::RenderTarget& outputTarget);
	~World();

	void update(sf::Time dt, const sf::Vector2i& mousePosition);
	void draw();

	int getRoomCount();
	void addRoom(Room* room);
	void connectCells();

	void checkHamsterCollision(Hamster* hamster);
	void handleHamsterCollision(Hamster* hamster);

	bool checkOverlap(sf::RectangleShape& r1, sf::RectangleShape& r2);
	bool checkCollision(sf::RectangleShape& r1, sf::RectangleShape& r2);

	bool checkMouseHover(const sf::Vector2i& mousePosition,  sf::RectangleShape& rect);
	void handleLeftClick();
	void displayHamsterInfo();
};

