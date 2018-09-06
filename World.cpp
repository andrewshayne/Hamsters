#include "World.h"


World::World(sf::RenderTarget& outputTarget) : target(outputTarget), worldView(outputTarget.getDefaultView()), isHoldingHamster(false), currentlyHoveredHamster(nullptr), currentlyHoveredCell(nullptr)
{
	if (!backgroundImage.loadFromFile("Images/trophies.png"))
	{
		exit(-1);
	}

	overlay = new Overlay(); //populate using the current world info?

	backgroundSprite = new sf::Sprite(backgroundImage);
	backgroundSprite->setOrigin(backgroundSprite->getLocalBounds().width / 2.f, backgroundSprite->getLocalBounds().height / 2.f);
	backgroundSprite->setScale(2, 2); //because it is set to 2 in GAME

	//fix this up, very unsure about passing resolution down to every single class...
	backgroundSprite->setPosition(target.getSize().x / 2.f, target.getSize().y / 2.f);

	sf::Vector2i myRoomCoord1 = sf::Vector2i(2, 2);
	room1 = new Room(myRoomCoord1); //why isn't it showing up here??


	sf::Vector2i myRoomCoord2 = sf::Vector2i(3, 4);
	room2 = new Room(myRoomCoord2); //why isn't it showing up here??

	worldView.reset(sf::FloatRect(0.f, 0.f, target.getSize().x, target.getSize().y));
	worldView.setViewport(sf::FloatRect(0, 0, 1, 1));

	minimapView.reset(sf::FloatRect(0.f, 0.f, target.getSize().x, target.getSize().y));
	minimapView.setViewport(sf::FloatRect(0.75f, 0.75f, 0.25f, 0.25f));

	grid = new Cell**[rows];
	for (int i = 0; i < rows; i++)
	{
		grid[i] = new Cell*[cols];
		for (int j = 0; j < cols; j++)
		{
			grid[i][j] = nullptr;
			sf::RectangleShape* cellContainer = new sf::RectangleShape(sf::Vector2f(80.f, 60.f));
			cellContainer->setPosition(i * 80.f, j * 60.f);
			cellContainer->setFillColor(sf::Color::Transparent);
			cellContainer->setOutlineColor(sf::Color::White);
			cellContainer->setOutlineThickness(-1.f);
			cellContainers.push_back(cellContainer);
		}
	}

	addRoom(room1);
	addRoom(room2);

	connectCells();
}


World::~World()
{
}

void World::update(sf::Time dt, sf::Vector2i& mousePosition)
{
	bool foundHamster = false;
	bool foundCell = false;
	//check every hamster in every room for mouse hover, IF not holding one
	if (!isHoldingHamster) //make sure no hamster is already being held, display this hamster's stats
	{
		for (std::unordered_map<std::string,Room*>::iterator it_room = rooms.begin(); it_room != rooms.end(); ++it_room) //iterate over all rooms
		{
			for (std::unordered_map<std::string,Cell*>::iterator it_cell = it_room->second->getCells().begin(); it_cell != it_room->second->getCells().end(); ++it_cell) //iterate over cells in room
			{
				for (std::unordered_map<std::string,Hamster*>::iterator it = it_cell->second->hamsters.begin(); it != it_cell->second->hamsters.end(); ++it) //iterate over hamsters in cell
				{
					//if no hamster is hit once, set current to nullptr

					//check if mouse lands inside a hamster's box
					if (checkMouseHover(mousePosition, it->second->getHamsterRect()))
					{
						currentlyHoveredHamster = it->second;
						foundHamster = true;
						break;
					}
				}
				if (foundHamster) break;
			}
			if (foundHamster) break;
		}
		if (!foundHamster)
		{
			currentlyHoveredHamster = nullptr;
		}
	}
	//if (isHoldingHamster /* && currentlyHoveredHamster != nullptr */)
	else
	{
		if (currentlyHoveredHamster == nullptr)
		{
			exit(0); //this should never be the case...
		}
		currentlyHoveredHamster->getHamsterRect().setPosition((sf::Vector2f)mousePosition);

		//check if hamster is being held over a room! (mouse position)
		//we don't care (I think) if the empty-handed mouse is hovering over a room
		for (std::unordered_map<std::string,Room*>::iterator it_room = rooms.begin(); it_room != rooms.end(); ++it_room)
		{
			for (std::unordered_map<std::string,Cell*>::iterator it_cell = it_room->second->getCells().begin(); it_cell != it_room->second->getCells().end(); ++it_cell)
			{
				//check if mouse is over a cell
				if (checkMouseHover(mousePosition, it_cell->second->rect))
				{
					currentlyHoveredCell = it_cell->second;
					foundCell = true;
					break;
				}
			}
			if (foundCell) break;
			currentlyHoveredCell = nullptr;
		}
		if (!foundCell)
		{
			currentlyHoveredCell = nullptr;
		}
	}

}

void World::draw()
{
	//Background
	target.clear();
	target.setView(worldView);
	target.draw(*backgroundSprite);

	//draw the grid
	for (int i = 0; i < cellContainers.size(); i++)
	{
		target.draw(*cellContainers.at(i));
	}

	//draw rooms and hamsters
	for (std::unordered_map<std::string,Room*>::iterator it_room = rooms.begin(); it_room != rooms.end(); ++it_room)
	{
		//put this in room draw class?
		for (std::unordered_map<std::string,Cell*>::iterator it_cell = it_room->second->getCells().begin(); it_cell != it_room->second->getCells().end(); ++it_cell)
		{
			target.draw(it_cell->second->rect);
			//draw 4 doors
			for (int k = 0; k < 4; ++k)
			{
				if (it_cell->second->neighborCell[k] != nullptr)
				{
					it_cell->second->portalRects[k].setFillColor(sf::Color::Green);
				}
				target.draw(it_cell->second->portalRects[k]);
			}

			//draw hamsters
			for (std::unordered_map<std::string,Hamster*>::iterator it = it_cell->second->hamsters.begin(); it != it_cell->second->hamsters.end(); ++it)
			{
				target.draw(it->second->getHamsterRect());
			}
		}
	}

	//draw portals

	//draw overlay
	target.draw(overlay->getHamsterWindow()->getWindowRect());
	for (std::unordered_map<std::string, WindowComponent*>::iterator it = overlay->getHamsterWindow()->componentMap.begin(); it != overlay->getHamsterWindow()->componentMap.end(); ++it)
	{
		target.draw(it->second->title);
	}

	target.draw(overlay->getStoreWindow()->getWindowRect());
	for (std::unordered_map<std::string, WindowComponent*>::iterator it = overlay->getStoreWindow()->componentMap.begin(); it != overlay->getStoreWindow()->componentMap.end(); ++it)
	{
		target.draw(it->second->title);
	}



	//VIEW - miniunordered_map
	target.setView(minimapView);
	target.draw(*backgroundSprite);

	target.setView(worldView);
}

int World::getRoomCount()
{
	return 0;
}

void World::addRoom(Room* room)
{
	//takes the master cell and places it in the matrix at pos
	//actually places all cells in their position on the grid
	rooms[room->getKey()] = room;
	for (std::unordered_map<std::string,Cell*>::iterator it_cell = room->getCells().begin(); it_cell != room->getCells().end(); ++it_cell)
	{
		grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y] = it_cell->second;
	}
}

void World::connectCells()
{
	for (std::unordered_map<std::string,Room*>::iterator it_room = rooms.begin(); it_room != rooms.end(); ++it_room)
	{
		for (std::unordered_map<std::string,Cell*>::iterator it_cell = it_room->second->getCells().begin(); it_cell != it_room->second->getCells().end(); ++it_cell)
		{
			//check each direction for each cell
			//ADD BOUNDS CHECKING LATER!!!!!!!!!!
			if (grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y] != nullptr)
			{
				grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y]->neighborCell[N]
					= grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y - 1];
				grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y]->neighborCell[E]
					= grid[it_cell->second->gridCoordinate.x + 1][it_cell->second->gridCoordinate.y];
				grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y]->neighborCell[S]
					= grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y + 1];
				grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y]->neighborCell[W]
					= grid[it_cell->second->gridCoordinate.x - 1][it_cell->second->gridCoordinate.y];
			}


			// if (it_cell->second->isOutgoingPortal[N])
			// {
			// 	it_cell->second->neighborCell[N] = grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y + 1];
			// 	it_cell->second->portalRects[N].setFillColor(sf::Color::Green);
			// }
			// if (it_cell->second->isOutgoingPortal[S])
			// {
			// 	it_cell->second->neighborCell[S] = grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y - 1];
			// 	it_cell->second->portalRects[S].setFillColor(sf::Color::Green);
			// }
			// if (it_cell->second->isOutgoingPortal[E])
			// {
			// 	it_cell->second->neighborCell[E] = grid[it_cell->second->gridCoordinate.x + 1][it_cell->second->gridCoordinate.y];
			// 	it_cell->second->portalRects[E].setFillColor(sf::Color::Green);
			// }
			// if (it_cell->second->isOutgoingPortal[W])
			// {
			// 	it_cell->second->neighborCell[W] = grid[it_cell->second->gridCoordinate.x - 1][it_cell->second->gridCoordinate.y];
			// 	it_cell->second->portalRects[W].setFillColor(sf::Color::Green);
			// }
		}
	}
}

void World::checkHamsterCollision(Hamster* hamster)
{
}

void World::handleHamsterCollision(Hamster* hamster)
{
}

bool World::checkOverlap(sf::RectangleShape & r1, sf::RectangleShape & r2)
{
	// If a majority of the hamster's area is in the room, then it may be dropped... ?
	// (write a function to calculate the area of 2 overlapping rectangles?)

	// If one rectangle is on left side of other
	if (r1.getPosition().x > r2.getPosition().x + r2.getSize().x || r2.getPosition().x > r1.getPosition().x + r1.getSize().x)
	{
		return false;
	}
	// If one rectangle is above other
	if (r1.getPosition().y > r2.getPosition().y + r2.getSize().y || r2.getPosition().y > r1.getPosition().y + r1.getSize().y)
	{
		return false;
	}
	return true;
}

bool World::checkCollision(sf::RectangleShape& r1, sf::RectangleShape& r2)
{
	return false;
}

bool World::checkMouseHover(sf::Vector2i& mousePosition, sf::RectangleShape& rect)
{
	if (mousePosition.x > rect.getPosition().x - rect.getSize().x/2
		&& mousePosition.x < rect.getPosition().x + rect.getSize().x/2
		&& mousePosition.y > rect.getPosition().y - rect.getSize().y/2
		&& mousePosition.y < rect.getPosition().y + rect.getSize().y/2)
		return true;
	return false;

	// if (mousePosition.x > rect.getPosition().x
	// 	&& mousePosition.x < rect.getPosition().x + rect.getSize().x
	// 	&& mousePosition.y > rect.getPosition().y
	// 	&& mousePosition.y < rect.getPosition().y + rect.getSize().y)
	// 	return true;
	// return false;
}

void World::handleLeftClick()
{
	//if click inside hamster's box, pick it up
	if (currentlyHoveredHamster != nullptr) //on a hamster
	{
		if (currentlyHoveredCell != nullptr) //on a cell
		{
			if (isHoldingHamster)	//dropping hamster into cell
			{
				//currentlyHoveredCell->hamsters[currentlyHoveredHamster->getName()] = currentlyHoveredHamster;
				//currentlyHoveredHamster->getHamsterRect().setPosition(currentlyHoveredCell->rect.getPosition().x, currentlyHoveredCell->rect.getPosition().y);
				currentlyHoveredCell->addHamster(currentlyHoveredHamster);
				printf("count: %i\n", currentlyHoveredCell->hamsters.size());
			}
			else					//taking hamster from cell
			{
				//remove this hamster from the room!!! , need a unordered_map instead of vector...
				//currentlyHoveredCell->hamsters.

				currentlyHoveredCell->hamsters.erase(currentlyHoveredHamster->getName());
				printf("count: %i\n", currentlyHoveredCell->hamsters.size());
			}

		}
		isHoldingHamster = !isHoldingHamster;
	}
}

void World::displayHamsterInfo()
{
	//when hamster is hovered or held, display its info in a panel!
	overlay->getHamsterWindow()->setSelectedHamster(currentlyHoveredHamster);
}

