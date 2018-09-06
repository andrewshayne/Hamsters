#include "CollisionBox.h"



CollisionBox::CollisionBox()
{
}


CollisionBox::~CollisionBox()
{
}

bool CollisionBox::checkMouseHover(sf::Vector2i mousePos)
{
	if (mousePos.x > rect.getPosition().x
		&& mousePos.x < rect.getPosition().x + rect.getSize().x
		&& mousePos.y > rect.getPosition().y
		&& mousePos.y < rect.getPosition().y + rect.getSize().y)
		return true;
	return false;
}
