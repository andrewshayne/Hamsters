//#include "imgui.h"
//#include "imgui-SFML.h"

#include "Room.h"
#include "Hamster.h"

#include "InputManager.h"
#include "Overlay.h"

#include <stdlib.h>
#include <math.h>

#include "imgui.h"
#include "imgui-SFML.h"

#pragma once

struct Button
{
	sf::Font font;
	sf::Text text;
	sf::RectangleShape rect;

	Button(std::string str, sf::Vector2f position)
	{

		font.loadFromFile("Fonts/BodoniFLF-Bold.ttf");
		text.setFont(font);
		text.setString(str);
		text.setPosition(position);

		rect.setFillColor(sf::Color::Red);
		rect.setSize({ 120.f, 50.f });
		rect.setOrigin(rect.getSize().x / 2.f, rect.getSize().y / 2.f);
		rect.setPosition(position);
	}

	void draw(sf::RenderTarget& target)
	{
		target.draw(rect);
		target.draw(text);
	}
};
class World
{
private:
	friend class boost::serialization::access;
	// When the class Archive corresponds to an output archive, the
	// & operator is defined similar to <<.  Likewise, when the class Archive
	// is a type of input archive the & operator is defined similar to >>.
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & money;
		//ar & hamsters;
	}

	Button nextDayButton;
	bool isAdminMode;
	bool rightMouseButtonHeld;
	sf::Vector2i initialMousePosition;
	InputManager inputManager;
	int money;
	sf::Text moneyText;

	sf::Vector2i currentMousePos;
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

	void readSaveFile(std::string fileName); //and pass params to obj constructors
	void writeSaveFile(std::string fileName);

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
	void hideHamsterInfo();
	void purchaseHamster(std::string name);

	//hamster interactions?
	void invokeHamsterInteraction(Hamster* h1, Hamster* h2, int interactionId);
};


