#include "Overlay.h"



StoreWindow* Overlay::getStoreWindow()
{
	return storeWindow;
}

HamsterWindow* Overlay::getHamsterWindow()
{
	return hamsterWindow;
}

void Overlay::update()
{
	//setWindowPosition(hamsterWindow, hamsterWindow->getRelativePosition());
	//setWindowPosition(hamsterWindow, hamsterWindow->getRelativePosition());
}

void Overlay::setWindowPosition(UserWindow* userWindow, sf::Vector2f position)
{
	userWindow->getWindowRect().setPosition(position);
}

Overlay::Overlay(sf::Vector2f cellDimensions) : storeWindowPosition(sf::Vector2f((cellDimensions.x / 2) + 12.f, (cellDimensions.y * 3 / 2) + 100.f)), hamsterWindowPosition(sf::Vector2f((cellDimensions.x * 3 / 2) + 12.f, (cellDimensions.y / 2) + (cellDimensions.y * 3) + 100.f))
{
	storeWindow = new StoreWindow(storeWindowPosition, sf::Vector2f(cellDimensions.x, cellDimensions.y * 3));
	hamsterWindow = new HamsterWindow(hamsterWindowPosition, sf::Vector2f(cellDimensions.x * 3, cellDimensions.y));
}


Overlay::~Overlay()
{
}
