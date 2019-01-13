#include "HamsterWindow.h"



HamsterWindow::HamsterWindow(sf::Vector2f position, sf::Vector2f size) : UserWindow(position, size), selectedHamster(nullptr)
{
	std::string comp = "hamster component #1";
	components[comp] = new WindowComponent(position, comp);

	hamsterName.setFont(getFont());
	hamsterName.setPosition(position); //set relative to the window's position
	hamsterName.setCharacterSize(40.f);
	hamsterName.setFillColor(sf::Color::White);
}


HamsterWindow::~HamsterWindow()
{
}

void HamsterWindow::update()
{
	//just assign int IDs to each drawable element to distinguish
	// 0 = hamsterName
}

void HamsterWindow::setSelectedHamster(Hamster* hamster)
{
	selectedHamster = hamster;
	if (hamster != nullptr)
	{
		hamsterName.setString(hamster->getName());
		drawElements.insert({ 0, hamsterName });
	}
	else
	{
		//drawElements.erase(0);
		//hamsterName.setString("N/A");
	}
}

void HamsterWindow::setHamsterInfo()
{
	//dangerrrrr
	//hamsterName.setString(selectedHamster->getName());
}

Hamster* HamsterWindow::getSelectedHamster()
{
	return selectedHamster;
}
