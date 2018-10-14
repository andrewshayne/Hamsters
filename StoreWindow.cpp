#include "StoreWindow.h"



StoreWindow::StoreWindow(sf::Vector2f position, sf::Vector2f size): UserWindow(position, size)
{
	std::string comp = "store component #1";
	components[comp] = new WindowComponent(position, comp);

	Hamster* h1 = new Hamster(sf::Vector2f(position.x, position.y - getWindowRect().getSize().y / 2.f + 20.f), "h1");
	Hamster* h2 = new Hamster(sf::Vector2f(position.x, position.y - getWindowRect().getSize().y / 2.f + 50.f), "h2");
	Hamster* h3 = new Hamster(sf::Vector2f(position.x, position.y - getWindowRect().getSize().y / 2.f + 80.f), "h3");


	int defaultPrice = 500;
	Purchasable p1(defaultPrice, h1->getHamsterRect(), h1);
	Purchasable p2(defaultPrice, h2->getHamsterRect(), h2);
	Purchasable p3(defaultPrice, h3->getHamsterRect(), h3);

	purchasableHamsters.push_back(p1);
	purchasableHamsters.push_back(p2);
	purchasableHamsters.push_back(p3);
}


StoreWindow::~StoreWindow()
{
}

void StoreWindow::update()
{
}

const std::vector<Purchasable>& StoreWindow::getPurchasableHamsters()
{
	return purchasableHamsters;
}

const std::vector<Purchasable>& StoreWindow::getPurchasableRooms()
{
	return purchasableRooms;
}
