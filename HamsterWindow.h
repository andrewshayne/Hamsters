#include "UserWindow.h"

#include "Hamster.h"

#pragma once
class HamsterWindow: public UserWindow
{
private:
	Hamster* selectedHamster;

	sf::Text hamsterName;
public:
	HamsterWindow(sf::Vector2f position, sf::Vector2f size);
	~HamsterWindow();

	void setSelectedHamster(Hamster* hamster);
	Hamster* getSelectedHamster();
};

