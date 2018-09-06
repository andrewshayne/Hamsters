#include "UserWindow.h"



UserWindow::UserWindow(sf::Vector2f position, sf::Vector2f size)
{
	windowRect.setPosition(position);
	windowRect.setSize(size);
	windowRect.setFillColor(sf::Color::Blue);
}

sf::RectangleShape& UserWindow::getWindowRect()
{
	return windowRect;
}