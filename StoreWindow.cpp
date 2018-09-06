#include "StoreWindow.h"



StoreWindow::StoreWindow(sf::Vector2f position, sf::Vector2f size): UserWindow(position, size)
{
	std::string comp = "store component #1";
	componentMap[comp] = new WindowComponent(position, comp);
}


StoreWindow::~StoreWindow()
{
}
