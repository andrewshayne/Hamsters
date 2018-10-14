#include "StoreWindow.h"
#include "HamsterWindow.h"

#pragma once
class Overlay
{
private:
	// needs to have:
	// funds
	// drag and drop purchase
	sf::Vector2f cellDimensions;
	sf::Vector2f storeWindowPosition;
	sf::Vector2f hamsterWindowPosition;

	StoreWindow* storeWindow;
	HamsterWindow* hamsterWindow;
public:
	StoreWindow* getStoreWindow();
	HamsterWindow* getHamsterWindow();

	void update();
	void setWindowPosition(UserWindow* userWindow, sf::Vector2f position);
	Overlay(sf::Vector2f cellDimensions);
	~Overlay();
};

