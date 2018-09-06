#include "Overlay.h"



StoreWindow* Overlay::getStoreWindow()
{
	return storeWindow;
}

HamsterWindow* Overlay::getHamsterWindow()
{
	return hamsterWindow;
}

Overlay::Overlay() : position(sf::Vector2f(0.f,300.f)), storeWindowPosition(sf::Vector2f(20.f,20.f)), hamsterWindowPosition(sf::Vector2f(20.f,101.f))
{
	storeWindow = new StoreWindow(sf::Vector2f(position.x + storeWindowPosition.x, position.y + storeWindowPosition.y), sf::Vector2f(60.f, 80.f));
	hamsterWindow = new HamsterWindow(sf::Vector2f(position.x + hamsterWindowPosition.x, position.y + hamsterWindowPosition.y), sf::Vector2f(240.f, 60.f));
}


Overlay::~Overlay()
{
}
