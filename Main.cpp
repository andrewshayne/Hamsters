#include "Game.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception &e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return 0;
}

// void handleCollision(sf::RectangleShape& r1, sf::RectangleShape& r2, bool& isGrounded) {
// 	sf::Vector2f r1_HalfSize = { r1.getSize().x / 2.f, r1.getSize().y / 2.f };
// 	sf::Vector2f r1_Center = { r1.getPosition().x + r1_HalfSize.x, r1.getPosition().y + r1_HalfSize.y };

// 	sf::Vector2f r2_HalfSize = { r2.getSize().x / 2.f, r2.getSize().y / 2.f };
// 	sf::Vector2f r2_Center = { r2.getPosition().x + r2_HalfSize.x, r2.getPosition().y + r2_HalfSize.y };

// 	//get AABB
// 	float xDist = abs(r1_Center.x - r2_Center.x) - (r1_HalfSize.x + r2_HalfSize.x);
// 	float yDist = abs(r1_Center.y - r2_Center.y) - (r1_HalfSize.y + r2_HalfSize.y);

// 	if (xDist <= 0 && yDist <= 0)
// 	{

// 		float unit = 1.f;
// 		//smallest dist pushes out
// 		if (abs(xDist) < abs(yDist))
// 		{
// 			if (r1_Center.x < r2_Center.x)
// 				unit = -1.f;
// 			else
// 				unit = 1.f;

// 			//add projected position for y??
// 			r1.setPosition(r2_Center.x + (r1_HalfSize.x + r2_HalfSize.x)*unit, r1.getPosition().y);
// 			////entity.setVelocity(0.f, entity.getVelocity().y);
// 		}
// 		else
// 		{
// 			if (r1_Center.y < r2_Center.y)
// 			{
// 				unit = -1.f;
// 				isGrounded = true;
// 				////entity.setVelocity(entity.getVelocity().x, 0.f);
// 			}
// 			else
// 			{
// 				unit = 1.f;
// 				//entity.setVelocity(entity.getVelocity().x, entity.getGravity());
// 			}

// 			r1.setPosition(r1.getPosition().x, r2_Center.y + (r1_HalfSize.y + r2_HalfSize.y)*unit);
// 			//entity.setVelocity(entity.getVelocity().x, 0.f);
// 		}
// 		//cout << "OVERLAPPING WITH TILE #" << i << endl; //works!!
// 	}
// }

