#include "UserWindow.h"

#pragma once
class HamsterWindow: public UserWindow
{
private:
	Hamster* selectedHamster;

	sf::Text hamsterName;


	std::vector<sf::Text> hamsterStatsText;
public:
	HamsterWindow(sf::Vector2f position, sf::Vector2f size);
	~HamsterWindow();

	void update();
	void setSelectedHamster(Hamster* hamster);
	void setHamsterInfo();
	Hamster* getSelectedHamster();
};

