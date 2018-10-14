#include "World.h"


World::World(sf::RenderTarget& outputTarget) : target(outputTarget), worldView(outputTarget.getDefaultView()), isAdminMode(false), isHoldingHamster(false),
	currentlyHoveredHamster(nullptr), currentlyHoveredCell(nullptr), currentlyHoveredPurchasable(nullptr), isHoveringStoreWindow(false), isHoveringHamsterWindow(false),
	rightMouseButtonHeld(false), initialMousePosition({0,0})
{
	srand(time(NULL));
	if (!backgroundImage.loadFromFile("Images/trophies.png"))
	{
		exit(-1);
	}

	viewRect.setSize(worldView.getSize());
	viewRect.setOrigin(worldView.getSize().x / 2.f, viewRect.getSize().y / 2.f);
	viewRect.setPosition(worldView.getCenter());
	viewRect.setOutlineThickness(-8.f);
	viewRect.setOutlineColor(sf::Color::Red);
	viewRect.setFillColor(sf::Color::Transparent);

	overlay = new Overlay(Room::cellDimensions); //populate using the current world info?

	backgroundSprite = new sf::Sprite(backgroundImage);
	backgroundSprite->setOrigin(backgroundSprite->getLocalBounds().width / 2.f, backgroundSprite->getLocalBounds().height / 2.f);
	backgroundSprite->setScale(5.f, 3.75f); //because it is set to 2 in GAME

	//fix this up, very unsure about passing resolution down to every single class...
	backgroundSprite->setPosition(target.getSize().x / 2.f, target.getSize().y / 2.f);

	room1 = new Room({1,1});
	room2 = new Room({2,2});
	room3 = new Room({3,3});

	worldView.reset(sf::FloatRect(0.f, 0.f, target.getSize().x, target.getSize().y));
	worldView.setViewport(sf::FloatRect(0, 0, 1, 1));
	worldView.setCenter(target.getSize().x / 2.f, target.getSize().y / 2.f);

	minimapView.reset(sf::FloatRect(0.f, 0.f, target.getSize().x, target.getSize().y));
	minimapView.setViewport(sf::FloatRect(0.75f, 0.75f, 0.25f, 0.25f));

	overlayView.reset(sf::FloatRect(0.f, 0.f, target.getSize().x, target.getSize().y));
	worldView.setViewport(sf::FloatRect(0, 0, 1, 1));
	worldView.setCenter(target.getSize().x / 2.f, target.getSize().y / 2.f);

	grid = new Cell**[rowCount];
	for (int i = 0; i < rowCount; i++)
	{
		grid[i] = new Cell*[colCount];
		for (int j = 0; j < colCount; j++)
		{
			grid[i][j] = nullptr;
			sf::RectangleShape* cellContainer = new sf::RectangleShape(Room::cellDimensions);
			cellContainer->setPosition(i * Room::cellDimensions.x, j * Room::cellDimensions.y);
			cellContainer->setFillColor(sf::Color::Transparent);
			cellContainer->setOutlineColor(sf::Color::White);
			cellContainer->setOutlineThickness(-1.f);
			cellContainers.push_back(cellContainer);
		}
	}

	Hamster* hamster1 = new Hamster(sf::Vector2f(0.f, 0.f), "Hamuel");
	Hamster* hamster2 = new Hamster(sf::Vector2f(0.f, 0.f), "Hamson");
	Hamster* hamster3 = new Hamster(sf::Vector2f(0.f, 0.f), "Hamtaro");

	Hamster* hamster4 = new Hamster(sf::Vector2f(0.f, 0.f), "Hamtaro");

	room1->getCells().at("00")->addHamster(hamster1);
	room1->getCells().at("10")->addHamster(hamster2);
	room2->getCells().at("01")->addHamster(hamster3);

	addRoom(room1);
	addRoom(room2);
	addRoom(room3);
	connectCells();


	font.loadFromFile("Fonts/BodoniFLF-Bold.ttf");

	money = 5000;
	moneyText.setString("Money: " + std::to_string(money));
	moneyText.setPosition(1300, 0);
	moneyText.setCharacterSize(40.f);
	moneyText.setFont(font);

	hoverHamsterText.setFont(font);
	hoverHamsterText.setString("hamster: false");
	hoverHamsterText.setPosition(0.f, 80.f);
	hoverHamsterText.setCharacterSize(22.f);

	hoverCellText.setFont(font);
	hoverCellText.setString("cell: false");
	hoverCellText.setPosition(0.f, 110.f);
	hoverCellText.setCharacterSize(22.f);
}


World::~World()
{
}

int randN(int n)
{
	return rand() % n;
}

void World::update(sf::Time dt, const sf::Vector2i& mousePos)
{
	sf::Vector2i mousePosition = (sf::Vector2i)target.mapPixelToCoords(mousePos);
	target.setView(overlayView);
	sf::Vector2i mousePosOverlay = (sf::Vector2i)target.mapPixelToCoords(mousePos);
	target.setView(worldView);

	bool foundHamster = false;
	bool foundCell = false;

	bool foundStoreHamster = false;
	isHoveringStoreWindow = checkMouseHover(mousePosOverlay, overlay->getStoreWindow()->getWindowRect());
	isHoveringHamsterWindow = checkMouseHover(mousePosition, overlay->getHamsterWindow()->getWindowRect());

	//update each hamster
	for (std::unordered_map<std::string, Hamster*>::iterator it_hamster = hamsters.begin(); it_hamster != hamsters.end(); ++it_hamster)
	{
		it_hamster->second->update(dt, nodes);
		if (!it_hamster->second->getIsPathing()) //hamster needs new destination
		{
			//determine destination (let's say first room cell for now)
			Node* start = it_hamster->second->getCurrentNode();

			//pick a random destination for now
			std::unordered_map<std::string, Room*>::iterator it_room = rooms.begin();
			std::advance(it_room, randN(rooms.size()));
			std::unordered_map<std::string,Cell*>::iterator it_cell = it_room->second->getCells().begin();
			std::advance(it_cell, randN(it_room->second->getCells().size()));
			Node* finish = it_cell->second->destination;

			//Node* finish = room1->getCells().begin()->second->destination;
			if (start != nullptr && finish != nullptr) //no nullptrs AND start != finish
			{
				if (start != finish) // don't path to the same place
				{
					it_hamster->second->setPath(A_Star(start, finish));
				}
				else //is there something we should do under this condition??
				{
					//std::cout << "you are already here!\n";
				}
			}
		}
	}

	//mouse is in the store window, not holding a hamster
	if (isHoveringStoreWindow)
	{
		if (!isHoldingHamster) //make sure no hamster is already being held, display this hamster's stats
		{
			for (std::vector<Purchasable>::const_iterator it = overlay->getStoreWindow()->getPurchasableHamsters().begin(); it != overlay->getStoreWindow()->getPurchasableHamsters().end(); ++it)
			{
				if (checkMouseHover(mousePosOverlay, (sf::RectangleShape&)it->rect))
				{
					currentlyHoveredPurchasable = &(*it);
					foundStoreHamster = true;
					break;
				}
			}
			if (!foundStoreHamster) currentlyHoveredPurchasable = nullptr;
		}
	}
	//mouse not in store window
	else
	{
		// find which room is being hovered (if not in hovering a window)
		for (std::unordered_map<std::string, Room*>::iterator it_room = rooms.begin(); it_room != rooms.end(); ++it_room)
		{
			for (std::unordered_map<std::string, Cell*>::iterator it_cell = it_room->second->getCells().begin(); it_cell != it_room->second->getCells().end(); ++it_cell)
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
		if (!foundCell) currentlyHoveredCell = nullptr;

		//if not holding a hamster, check every hamster in world
		if (!isHoldingHamster) //make sure no hamster is already being held, display this hamster's stats
		{
			for(std::unordered_map<std::string,Hamster*>::iterator it_hamster = hamsters.begin(); it_hamster != hamsters.end(); ++it_hamster)
			{
				if(checkMouseHover(mousePosition, it_hamster->second->getHamsterRect()))
				{
					currentlyHoveredHamster = it_hamster->second;
					foundHamster = true;
					break;
				}
			}
			if (!foundHamster) currentlyHoveredHamster = nullptr;
		}
	}

	if (isHoldingHamster)
	{
		if (currentlyHoveredHamster == nullptr) exit(0); //this should never be the case...
		currentlyHoveredHamster->getHamsterRect().setPosition((sf::Vector2f)mousePosition);
		currentlyHoveredHamster->getSprite().setPosition((sf::Vector2f)mousePosition);
	}

	if (rightMouseButtonHeld)
		moveCamera(mousePosition);
	else
	{
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
		target.draw(*cellContainers.at(i));

	//draw rooms and hamsters
	for (std::unordered_map<std::string,Room*>::iterator it_room = rooms.begin(); it_room != rooms.end(); ++it_room)
	{
		//put this in room draw class?
		for (std::unordered_map<std::string,Cell*>::iterator it_cell = it_room->second->getCells().begin(); it_cell != it_room->second->getCells().end(); ++it_cell)
		{
			//target.draw(it_cell->second->rect);
			target.draw(it_cell->second->getSprite());
			//draw 4 doors
			for (int k = 0; k < 4; ++k)
			{
				if (it_cell->second->neighborCell[k] != nullptr)
					it_cell->second->portalRects[k].setFillColor(sf::Color::Green);
				target.draw(it_cell->second->portalRects[k]);
			}
			target.draw(it_cell->second->getDestinationNode()->circle);

			it_cell->second->hamsterCountText.setString(std::to_string(it_cell->second->hamsters.size()));
			target.draw(it_cell->second->hamsterCountText);
		}
	}
	//draw hamsters
	for (std::unordered_map<std::string, Hamster*>::iterator it = hamsters.begin(); it != hamsters.end(); ++it)
		drawHamster(it->second, true);
	
	//draw portals



	//VIEW - overlay
	target.setView(overlayView);
	target.draw(overlay->getHamsterWindow()->getWindowRect());
	for (std::unordered_map<std::string, WindowComponent*>::iterator it = overlay->getHamsterWindow()->components.begin(); it != overlay->getHamsterWindow()->components.end(); ++it)
	{
		target.draw(it->second->title);
		if(overlay->getHamsterWindow()->getSelectedHamster() != nullptr) //if hamster is selected, draw stats
			target.draw(overlay->getHamsterWindow()->getSelectedHamster()->getNameText()); //iterate over hamster's stats (should they be ordered?)
	}
	target.draw(overlay->getStoreWindow()->getWindowRect());
	for (std::unordered_map<std::string, WindowComponent*>::iterator it = overlay->getStoreWindow()->components.begin(); it != overlay->getStoreWindow()->components.end(); ++it)
		target.draw(it->second->title);
	//purchasables on store window INSTEAD OF the component...
	for (std::vector<Purchasable>::const_iterator it = overlay->getStoreWindow()->getPurchasableHamsters().begin(); it != overlay->getStoreWindow()->getPurchasableHamsters().end(); ++it)
		drawHamster((Hamster*)it->purchasableObject, false);

	//target.draw(hoverHamsterText);
	//target.draw(hoverCellText);
	target.draw(moneyText);



	//VIEW - minimap
	target.setView(minimapView);
	target.draw(*backgroundSprite);
	target.draw(viewRect);

	target.setView(worldView);
	if(isHoldingHamster)
		drawHamster(currentlyHoveredHamster, true);

	if(isAdminMode) //draw admin-only info here
	{
	}

}

void World::drawHamster(Hamster* hamster, bool isPurchased)
{
	float scale = worldView.getSize().x / target.getSize().x;
	hamster->getNameText().setScale({scale,scale});
	target.draw(hamster->getSprite());
	target.draw(hamster->vta);
	if(isPurchased)
		target.draw(hamster->getNameText());
}


std::vector<Node*> World::reconstructPath(std::unordered_map<Node*, Node*> cameFrom, Node* current)
{
	std::vector<Node*> totalPath{ current };
	while (!(cameFrom.find(current) == cameFrom.end())) //check if current exists as key in cameFrom
	{
		current = cameFrom[current];
		totalPath.push_back(current);
	}
	//std::cout << "path:\n";
	for (int i = 0; i < totalPath.size(); i++)
	{
		//std::cout << "node - " << std::to_string(totalPath.at(i)->circle.getPosition().x) + ", " + std::to_string(totalPath.at(i)->circle.getPosition().y) << std::endl;
	}
	//std::cout << std::endl;
	return totalPath;
}

std::vector<Node*> World::A_Star(Node* start, Node* finish)
{
	std::unordered_map<sf::Vector2f,Node*> closedSet{ }; //set of nodes already evaluated
	std::unordered_map<sf::Vector2f,Node*> openSet{ { start->circle.getPosition(), start } }; //set of currently discovered nodes not evaluated

	//for each node, which node it can be most efficiently reached from, cameFrom will eventually contain the most efficient prev step
	std::unordered_map<Node*,Node*> cameFrom{ }; 
	std::unordered_map<Node*, float> gScore; //map all existing nodes on map to a gScore
	std::unordered_map<Node*, float> fScore; //map all existing nodes on map to a fScore

	for (std::unordered_map<sf::Vector2f, Node*>::iterator it_node = nodes.begin(); it_node != nodes.end(); ++it_node)
	{
		gScore[it_node->second] = FLT_MAX;
		fScore[it_node->second] = FLT_MAX;
	}
	gScore[start] = 0.f; //cost of going from start to start is 0
	fScore[start] = getManhattanDistance(start, finish); //first node is completely heuristic

	while (openSet.size() > 0)
	{
		//get the lowest fScore
		Node* lowestNode = openSet.begin()->second;
		float lowestScore = fScore[openSet.begin()->second];
		for (std::unordered_map<sf::Vector2f, Node*>::iterator it_node = openSet.begin(); it_node != openSet.end(); ++it_node) //for each node in openset, check fScore
		{
			if (fScore[it_node->second] < lowestScore)
			{
				lowestNode = it_node->second;
				lowestScore = fScore[it_node->second];
			}
		}
		Node* current = lowestNode;
		if (current == finish)
			return reconstructPath(cameFrom, current);

		openSet.erase(current->circle.getPosition());
		closedSet[current->circle.getPosition()] = current;

		for (std::vector<Node*>::iterator it_neighbor = current->neighbors.begin(); it_neighbor != current->neighbors.end(); ++it_neighbor) //iterate over each neighbor of current
		{
			//if neighbor in closedSet
			if (!(closedSet.find((*it_neighbor)->circle.getPosition()) == closedSet.end()))
				continue; //ignore the neighbor which is already evaluated

			float tentative_gScore = gScore[current] + getEuclideanDistance(current, *it_neighbor); //distance from start to a neighbor

			//if neighbor NOT in openSet
			if (openSet.find((*it_neighbor)->circle.getPosition()) == openSet.end()) //discover a new node
				openSet[(*it_neighbor)->circle.getPosition()] = *it_neighbor;
			else if (tentative_gScore >= gScore[*it_neighbor])
				continue; //this is NOT a better path

			//this path is the best until now, record it!
			cameFrom[*it_neighbor] = current;
			gScore[*it_neighbor] = tentative_gScore;
			fScore[*it_neighbor] = gScore[*it_neighbor] + getManhattanDistance(*it_neighbor, finish);
		}
	}
}

float World::getEuclideanDistance(Node* n1, Node* n2)
{
	sf::Vector2f vector = { n1->circle.getPosition().x - n2->circle.getPosition().x, n1->circle.getPosition().y - n2->circle.getPosition().y };
	return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

float World::getManhattanDistance(Node* n1, Node* n2)
{
	return fabs(n1->circle.getPosition().x - n2->circle.getPosition().x) + fabs(n1->circle.getPosition().y - n2->circle.getPosition().y);
}

void World::addMoney(int amount)
{
	money += amount;
	updateMoneyText();
}

void World::subtractMoney(int amount)
{
	money -= amount;
	updateMoneyText();
}

void World::updateMoneyText()
{
	moneyText.setString("Money: " + std::to_string(money));
}


void World::moveCamera(sf::Keyboard::Key key)
{
	sf::Vector2f moveVector{0,0};
	if (key == sf::Keyboard::Key::Left)
		moveVector.x = -8.f;
	if (key == sf::Keyboard::Key::Right)
		moveVector.x = 8.f;
	if (key == sf::Keyboard::Key::Up)
		moveVector.y = -8.f;
	if (key == sf::Keyboard::Key::Down)
		moveVector.y = 8.f;
	worldView.move(moveVector);

	correctCamera();
}

void World::moveCamera(const sf::Vector2i& mousePosition)
{
	sf::Vector2i myMousePosition = sf::Mouse::getPosition();
	sf::Vector2i delta = initialMousePosition - (sf::Vector2i)target.mapPixelToCoords(myMousePosition);
	worldView.setCenter(worldView.getCenter() + (sf::Vector2f)delta);
	target.setView(worldView);
	initialMousePosition = (sf::Vector2i)target.mapPixelToCoords(myMousePosition);

	correctCamera();
}

void World::correctCamera()
{
	//correct view position if it goes outside of bounds
	sf::Vector2f newCenter = worldView.getCenter();
	if (newCenter.x - worldView.getSize().x / 2.f < 0.f)
		newCenter.x = worldView.getSize().x / 2.f;
	else if (newCenter.x + worldView.getSize().x / 2.f > target.getSize().x)
		newCenter.x = target.getSize().x - worldView.getSize().x / 2.f;
	if (newCenter.y - worldView.getSize().y / 2.f < 0.f)
		newCenter.y = worldView.getSize().y / 2.f;
	else if (newCenter.y + worldView.getSize().y / 2.f > target.getSize().y)
		newCenter.y = target.getSize().y - worldView.getSize().y / 2.f;
	worldView.setCenter(newCenter);

	viewRect.setPosition(worldView.getCenter());
	viewRect.setSize(worldView.getSize());
	viewRect.setOrigin(worldView.getSize().x / 2.f, viewRect.getSize().y / 2.f);
}

void World::zoomCamera(float zoom, const sf::Vector2i& mousePosition)
{
	sf::Mouse::getPosition();
	worldView.zoom(zoom);


	correctCamera();
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
		nodes[it_cell->second->destination->circle.getPosition()] = it_cell->second->destination;

		//add hamsters in the room to World's hamsters
		for(std::unordered_map<std::string,Hamster*>::iterator it_hamster = it_cell->second->hamsters.begin(); it_hamster != it_cell->second->hamsters.end(); ++it_hamster)
			hamsters[it_hamster->first] = it_hamster->second;
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

				for (int i = 0; i < 4; i++)
				{
					//add all existing neighbors at cell portholes (currently just destinations)
					if (grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y]->neighborCell[i] != nullptr)
					{
						grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y]->destination->neighbors
							.push_back(grid[it_cell->second->gridCoordinate.x][it_cell->second->gridCoordinate.y]->neighborCell[i]->destination);
						std::cout << "added neighbor node\n";
					}
				}
			}
		}
	}
}

void World::checkHamsterCollision(Hamster* hamster)
{
}

void World::handleHamsterCollision(Hamster* hamster)
{
}

bool World::isCursorHoveringWindow()
{
	return isHoveringStoreWindow || isHoveringHamsterWindow;
}

bool World::checkOverlap(sf::RectangleShape & r1, sf::RectangleShape & r2)
{
	// If a majority of the hamster's area is in the room, then it may be dropped... ?
	// (write a function to calculate the area of 2 overlapping rectangles?)
	if (r1.getPosition().x > r2.getPosition().x + r2.getSize().x || r2.getPosition().x > r1.getPosition().x + r1.getSize().x) return false; // If one rectangle is on left side of other
	if (r1.getPosition().y > r2.getPosition().y + r2.getSize().y || r2.getPosition().y > r1.getPosition().y + r1.getSize().y) return false; // If one rectangle is above other
	return true;
}

bool World::checkCollision(sf::RectangleShape& r1, sf::RectangleShape& r2)
{
	return false;
}

bool World::checkMouseHover(const sf::Vector2i& mousePosition, sf::RectangleShape& rect)
{
	if (mousePosition.x > rect.getPosition().x - rect.getSize().x / 2
		&& mousePosition.x < rect.getPosition().x + rect.getSize().x / 2
		&& mousePosition.y > rect.getPosition().y - rect.getSize().y / 2
		&& mousePosition.y < rect.getPosition().y + rect.getSize().y / 2)
		return true;
	return false;

	// if (mousePosition.x > rect.getPosition().x
	// 	&& mousePosition.x < rect.getPosition().x + rect.getSize().x
	// 	&& mousePosition.y > rect.getPosition().y
	// 	&& mousePosition.y < rect.getPosition().y + rect.getSize().y)
	// 	return true;
	// return false;
}

void World::handleLeftClick(bool isPressed, const sf::Vector2i& mousePosition)
{
	if (isPressed)
	{
		if (isHoldingHamster && isCursorHoveringWindow()) return;
		//if click inside hamster's box, pick it up
		if (currentlyHoveredHamster != nullptr && !isHoveringStoreWindow) //on a hamster, not in store
		{
			if (currentlyHoveredCell != nullptr) //on a cell
			{
				if (isHoldingHamster)	currentlyHoveredCell->addHamster(currentlyHoveredHamster);		//dropping hamster into cell
				else					currentlyHoveredCell->removeHamster(currentlyHoveredHamster);	//taking hamster from cell
			}
			isHoldingHamster = !isHoldingHamster;
			if (isHoldingHamster)
			{
				currentlyHoveredHamster->setCurrentNode(nullptr);
				currentlyHoveredHamster->setCurrentDest(nullptr);
				currentlyHoveredHamster->clearPath();
			}
		}
		else if (currentlyHoveredPurchasable != nullptr && isHoveringStoreWindow)
		{
			if (!isHoldingHamster) //purchase hamster
			{
				std::string name = "buddy" + std::to_string(rand() % 1000 + 1);
				purchaseHamster(name); //pass default store hamster and new name
			}
		}
	}
}

void World::handleRightClick(bool isPressed, const sf::Vector2i& mousePosition)
{
	if (isPressed) //press and hold, drag screen
	{
		rightMouseButtonHeld = true;
		initialMousePosition = (sf::Vector2i)target.mapPixelToCoords(sf::Mouse::getPosition()); //(sf::Vector2i)target.mapPixelToCoords(mousePosition);
	}
	else //release
	{
		rightMouseButtonHeld = false;
		std::cout << "release\n";
	}
}

void World::handleScroll(float scrollDelta, const sf::Vector2i& mousePosition)
{
	//BUG: ZOOMING APPLIES TO THE MENU SCREEN!!!

	// handle scroll through hovered hamster pile??
	//if (currentlyHoveredHamster != nullptr)
	//{
	//	for (std::unordered_map<std::string, Hamster*>::iterator it_hamster = hamsters.begin(); it_hamster != hamsters.end(); ++it_hamster)
	//	{
	//		if(it_hamster->second != currentlyHoveredHamster && checkMouseHover(mousePosition, it_hamster->second->getHamsterRect()))
	//		{
	//			currentlyHoveredHamster = it_hamster->second;
	//			break;
	//		}
	//	}
	//	return;
	//}

	if		(scrollDelta > 0 && worldView.getSize().x > 200.f)				zoomCamera(0.8f, mousePosition);
	else if (scrollDelta < 0 && worldView.getSize().x < target.getSize().x) zoomCamera(1.25f, mousePosition);
}

void World::displayHamsterInfo()
{
	//when hamster is hovered or held, display its info in a panel!
	overlay->getHamsterWindow()->setSelectedHamster(currentlyHoveredHamster);
	overlay->getHamsterWindow()->setHamsterInfo();
}

void World::purchaseHamster(std::string name)
{
	if (currentlyHoveredPurchasable == nullptr) exit(0);
	if (money - currentlyHoveredPurchasable->price < 0)
	{
		std::cout << "Not enough funds to purchase this hamster.\n";
		return;
	}
	subtractMoney(currentlyHoveredPurchasable->price);
	hamsters[name] = new Hamster((Hamster*)currentlyHoveredPurchasable->purchasableObject, name);
	currentlyHoveredHamster = hamsters[name];
	isHoldingHamster = true;
}