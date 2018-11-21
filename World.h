//#include "imgui.h"
//#include "imgui-SFML.h"

#include "Room.h"
#include "Hamster.h"

#include "InputManager.h"
#include "Overlay.h"

#include <stdlib.h>
#include <math.h>

#include "imgui.h"
#include "imgui-sfml.h"

#pragma once
class World
{
private:
	bool isAdminMode;
	bool rightMouseButtonHeld;
	sf::Vector2i initialMousePosition;
	InputManager inputManager;
	int money;
	sf::Text moneyText;

	sf::RenderTarget& target;
	sf::View worldView;
	sf::View minimapView; //show where the camera is positioned/zoomed relative to the entire map
	sf::View overlayView;

	sf::Sprite* backgroundSprite;
	sf::Texture backgroundImage;

	sf::Font font;
	sf::Text hoverHamsterText;
	sf::Text hoverCellText;

	Overlay* overlay;
	sf::RectangleShape viewRect;

	int rowCount = 10;
	int colCount = 10;


	Cell*** grid; //matrix of cell pointers (pointer to array of pointers to arrays of cell pointers)
	std::vector<sf::RectangleShape*> cellContainers;

	Room* room1;
	Room* room2;
	Room* room3;
	std::unordered_map<std::string,Room*> rooms; //change this to map, use "XY" coords as key?
	std::unordered_map<std::string,Hamster*> hamsters;
	std::unordered_map<std::string,std::vector<Hamster*>> factions; //<factionName,hamsters> : maps faction name to a hamster* vector

	bool isHoldingHamster;
	Hamster* currentlyHoveredHamster;
	Cell* currentlyHoveredCell;
	const Purchasable* currentlyHoveredPurchasable;

	bool isHoveringStoreWindow;
	bool isHoveringHamsterWindow;
public:
	explicit World(sf::RenderTarget& outputTarget);
	~World();

	std::unordered_map<sf::Vector2f,Node*> nodes;
	std::vector<Node*> reconstructPath(std::unordered_map<Node*, Node*> cameFrom, Node* current);
	std::vector<Node*> A_Star(Node* start, Node* finish);

	void update(sf::Time dt, const sf::Vector2i& mousePos);
	void guiUpdate();
	void draw();
	void drawHamster(Hamster* hamster, bool isPurchased);

	//h(n)
	float getEuclideanDistance(Node* n1, Node* n2);
	float getManhattanDistance(Node* n1, Node* n2);

	void addMoney(int amount);
	void subtractMoney(int amount);
	void updateMoneyText();

	void moveCamera(sf::Keyboard::Key key);
	void moveCamera(const sf::Vector2i& mousePosition);
	void correctCamera();
	void zoomCamera(float zoom, const sf::Vector2i& mousePosition);

	int getRoomCount();
	void addRoom(Room* room);
	void connectCells();

	void checkHamsterCollision(Hamster* hamster);
	void handleHamsterCollision(Hamster* hamster);

	bool isCursorHoveringWindow();
	bool checkOverlap(sf::RectangleShape& r1, sf::RectangleShape& r2);
	bool checkCollision(sf::RectangleShape& r1, sf::RectangleShape& r2);

	bool checkMouseHover(const sf::Vector2i& mousePosition, sf::RectangleShape& rect);
	bool checkMouseHover(const sf::Vector2i& mousePosition, sf::CircleShape& circle);
	void handleLeftClick(bool isPressed, const sf::Vector2i& mousePosition);
	void handleRightClick(bool isPressed, const sf::Vector2i& mousePosition);
	void handleScroll(float scrollDelta, const sf::Vector2i& mousePosition);
	void displayHamsterInfo();
	void purchaseHamster(std::string name);
};


