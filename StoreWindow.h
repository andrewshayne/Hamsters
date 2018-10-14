#include "UserWindow.h"

#pragma once

struct Purchasable
{
	std::string name;
	int price;
	void* purchasableObject; //may be a hamster, room, etc.
	sf::RectangleShape rect;

	Purchasable(int price, sf::RectangleShape& rect, Hamster* purchasableHamster)
	{
		name = "Hamster";
		this->price = price;
		this->rect = rect;
		purchasableObject = purchasableHamster;
	}
	Purchasable(int price, sf::RectangleShape& rect, Room* purchasableRoom)
	{
		name = "Room";
		this->price = price;
		this->rect = rect;
		purchasableObject = purchasableRoom;
	}
};

class StoreWindow: public UserWindow
{
private:
	std::vector<Purchasable> purchasableHamsters;
	std::vector<Purchasable> purchasableRooms;
public:
	StoreWindow(sf::Vector2f position, sf::Vector2f size);
	~StoreWindow();

	void update();
	const std::vector<Purchasable>& getPurchasableHamsters();
	const std::vector<Purchasable>& getPurchasableRooms();
};

