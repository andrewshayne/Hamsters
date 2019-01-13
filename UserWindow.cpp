#include "UserWindow.h"



UserWindow::UserWindow(sf::Vector2f position, sf::Vector2f size)
{
	windowRect.setPosition(position);
	windowRect.setSize(size);
	windowRect.setOrigin(size.x / 2.f, size.y / 2.f);
	windowRect.setFillColor({ 0,0,200, 200 });
	windowRect.setOutlineThickness(-2);
	windowRect.setOutlineColor(sf::Color::Black);

	font.loadFromFile("Fonts/BodoniFLF-Bold.ttf");
}

sf::Font & UserWindow::getFont()
{
	return font;
}

sf::RectangleShape& UserWindow::getWindowRect()
{
	return windowRect;
}

sf::Vector2f UserWindow::getRelativePosition()
{
	return relativePosition;
}
