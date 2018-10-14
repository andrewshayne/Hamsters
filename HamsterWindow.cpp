#include "HamsterWindow.h"



HamsterWindow::HamsterWindow(sf::Vector2f position, sf::Vector2f size) : UserWindow(position, size), selectedHamster(nullptr)
{
	std::string comp = "hamster component #1";
	components[comp] = new WindowComponent(position, comp);
}


HamsterWindow::~HamsterWindow()
{
}

void HamsterWindow::update()
{
}

void HamsterWindow::setSelectedHamster(Hamster* hamster)
{
	selectedHamster = hamster;
}

void HamsterWindow::setHamsterInfo()
{
	hamsterName.setString(selectedHamster->getName());

}

Hamster* HamsterWindow::getSelectedHamster()
{
	return selectedHamster;
}
