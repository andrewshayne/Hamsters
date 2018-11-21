#include "Room.h"


#include <iostream>

const sf::Vector2f Room::cellDimensions = { 320.f, 180.f };

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


	Cell* cell1 = new Cell(cellDimensions, sf::Vector2i(0, 0), masterCellPosition, out1, out1, "Images/tubeL2.png"); //1
	Cell* cell2 = new Cell(cellDimensions, sf::Vector2i(1, 0), masterCellPosition, out2, col2, "Images/room1.png"); //2
	Cell* cell3 = new Cell(cellDimensions, sf::Vector2i(0, 1), masterCellPosition, out3, col3, "Images/room1.png"); //3

	cells[cell1->getRelativeKey()] = cell1;
	cells[cell2->getRelativeKey()] = cell2;
	cells[cell3->getRelativeKey()] = cell3;
}

Room::~Room()
{
}

std::string Room::getKey()
{
	return std::to_string(masterCellPosition.x) + std::to_string(masterCellPosition.y);
}

std::unordered_map<std::string,Cell*>& Room::getCells()
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