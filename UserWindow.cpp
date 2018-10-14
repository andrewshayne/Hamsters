#include "UserWindow.h"



UserWindow::UserWindow(sf::Vector2f position, sf::Vector2f size)
{
	windowRect.setPosition(position);
	windowRect.setSize(size);
	windowRect.setOrigin(size.x / 2.f, size.y / 2.f);
	windowRect.setFillColor(sf::Color::Blue);
	windowRect.setOutlineThickness(-2);
	windowRect.setOutlineColor(sf::Color::Black);
}

sf::RectangleShape& UserWindow::getWindowRect()
{
	return windowRect;
}

sf::Vector2f UserWindow::getRelativePosition()
{
	return relativePosition;
}
