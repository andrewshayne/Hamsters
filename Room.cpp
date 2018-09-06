#include "Room.h"


#include <iostream>

Room::Room(sf::Vector2i masterCellPosition) : masterCellPosition(masterCellPosition)
{
	// this room's shape:
	//
	// [1][2]
	// [3]
	//

	bool out1[4], out2[4], out3[4] = { false,false,false,false };
	bool col1[4], col2[4], col3[4] = { true, true, true, true  };

	out1[S] = true;  out1[E] = true;
	col1[S] = false; col1[E] = false;

	out2[W] = true;
	col2[W] = false;

	out3[N] = true;
	col3[N] = false;


	Cell* cell1 = new Cell(cellSize, sf::Vector2i(0, 0), masterCellPosition, out1, out1); //1
	Cell* cell2 = new Cell(cellSize, sf::Vector2i(1, 0), masterCellPosition, out2, col2); //2
	Cell* cell3 = new Cell(cellSize, sf::Vector2i(0, 1), masterCellPosition, out3, col3); //3

	cells[cell1->getKey()] = cell1;
	cells[cell2->getKey()] = cell2;
	cells[cell3->getKey()] = cell3;
	
	Hamster* hamster1 = new Hamster(sf::Vector2f(0.f,40.f));
	Hamster* hamster2 = new Hamster(sf::Vector2f(0.f,60.f));
	Hamster* hamster3 = new Hamster(sf::Vector2f(0.f,80.f));

	hamster1->setName(std::to_string(masterCellPosition.x) + "_1");
	hamster2->setName(std::to_string(masterCellPosition.x) + "_2");
	hamster3->setName(std::to_string(masterCellPosition.x) + "_3");

	std::cout << hamster1->getName() << " " << hamster2->getName() << " " << hamster3->getName() << std::endl;

	cells[cell1->getKey()]->addHamster(hamster1);
	cells[cell2->getKey()]->addHamster(hamster2);
	//cells.at(3)->addHamster(hamster3);

}

Room::~Room()
{
}

std::string Room::getKey()
{
	return std::to_string(masterCellPosition.x) + std::to_string(masterCellPosition.y);
}

std::unordered_map<std::string,Cell*>& const Room::getCells()
{
	return cells;
}

void Room::connectCells()
{
	for (std::unordered_map<std::string,Cell*>::iterator it_cell = cells.begin(); it_cell != cells.end(); ++it_cell)
	{
		//check each direction for each cell
		// if()
		for (int dir = 0; dir < 4; dir++)
		{
			if (it_cell->second->isOutgoingPortal[dir])
			{
				//cells.at(i)->neighborCell[dir] = //how to connect to cell at cords??
			}
		}
	}
}

