#pragma once
/*
* percolation.h
*
*  Created on: Oct 31, 2016
*      Author: Ashrit
*/

#ifndef PERCOLATION_H_
#define PERCOLATION_H_
#endif /* PERCOLATION_H_ */

#include <iostream>
#include"NDisjointSets.h"
#include "PercVisualizer.h"

using namespace std;

class percolation
{
public:
	percolation();
	percolation(int);
	~percolation();

	void open(int, int);
	bool isOpen(int, int);
	bool pathToTop(int, int);
	bool percolates();
	void dumpGrid(int);
	void dumpSets();
	void resetGrid();
	int getOpenCellCount();
	void showFinalVisualization();


private:
	int row, col; //private variable for grid dimension
	int **grid; // pointer to a 2d grid(pointer to an array of arrays)
	NDisjointSets Sets;//this will hold an array of row coordinates
	int openCellCount;
};
//this is a default constructor, when called instantiates an object grid
// with row = col = 6
percolation::percolation()
{
	row = 6;
	col = 6;
	openCellCount = 0;

	//these two array will be acting as our
	//sets(one for row and one for column) where we can merge them later on
	grid = new int *[row];

	for (int i = 0; i < row; i++)
	{
		grid[i] = new int[col];

		for (int j = 0; j <col; j++)
		{
			grid[i][j] = 1;
		}
	}
}

//parameter constructor for the percolation class. Creates an nxn grid
// where n is provided when instantiating, the disjoint set object is
//also initialized
percolation::percolation(int n) :Sets(n * n)
{
	row = n;
	col = n;
	openCellCount = 0;

	grid = new int *[row];

	for (int i = 0; i < row; i++)
	{
		grid[i] = new int[col];

		for (int j = 0; j <col; j++)
		{
			grid[i][j] = 1;
		}
	}
}

//destructor for the percolation class
percolation::~percolation()
{
	for (int i = 0; i < row; i++)
		delete[] grid[i];

	delete[] grid;
}

//takes the element in the grid and spits it out in a matrix form in to
// the print console
void percolation::dumpGrid(int n)
{
	row = n;
	col = n;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << grid[i][j] << " ";

		cout << endl;
	}

}

// This function checks to see if a specific cell is unblocked, if not we unblock it
//and connect it with its neighbors if they are unblocked as well. NDisjointSets class is used
//for connecting(or Union).
void percolation::open(int x, int y)
{
	int index = (x * row) + y;
	if (grid[x][y] == 1)
	{
		grid[x][y] = 0;
		openCellCount++;


		//connect the current cell to the cell above
		//if it is also unblocked
		if (isOpen((x - 1), y) && (x - 1) >= 0)
		{
			Sets.Union(index, (index - row));
		}

		//connect the cell to the right to the current
		//cell if it also unblock
		if (isOpen(x, (y + 1)) && (y + 1) <= col)
		{
			Sets.Union(index, (index + 1));
		}

		//connect the cell below to the current cell
		//if it is also unblocked
		if (isOpen(x + 1, y) && (x + 1) <= row)
		{
			Sets.Union(index, (index + row));
		}

		//connect the left cell to the current cell
		//if it is also unblocked
		if (isOpen(x, (y - 1)) && (y - 1) >= 0)
		{
			Sets.Union(index, (index - 1));
		}
	}
}

// This function yields true whenever the cell that is in check is unblocked
bool percolation::isOpen(int x, int y)
{
	int temp_row = x;
	int temp_col = y;


	//additional check is there for the boundary condition
	if (x + 1 <= row && y + 1 <= col && x >= 0
		&& y >= 0 && grid[temp_row][temp_col] != 1)
		return true;

	else
		return false;

}

// this function finds a path from a current cell to a cell to a top row
bool percolation::pathToTop(int x, int y)
{
	int index = (x * row) + y;
	int curr_element = Sets.Find(index);

	for (int i = 0; i < col; i++)
	{
		if (curr_element == Sets.Find(i))
			return true;
	}

	return false;
}
//this function checks to see if the system as a whole percolates from bottom
//row to the top row.
bool percolation::percolates()
{
	for (int i = 0; i < col; i++)
	{
		if (pathToTop(row - 1, i))
			return true;
	}
	return false;
}

//this function is used for debugging purposes
//to see the condition of the sets being used
void percolation::dumpSets()
{
	Sets.showAllPaths("Here is the set of coordinates:");
	cout << endl;
}

//this function resets the grid to all
//blocked cells and resets the set and the
//open cell count
void percolation::resetGrid()
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			grid[i][j] = 1;

	Sets.reset();

	openCellCount = 0;
}

//this function returns count for all the open cell
int percolation::getOpenCellCount()
{
	return openCellCount;
}

//this function utilizes the Percvisualizer class to
//visualize the percolation
void percolation::showFinalVisualization()
{
	//create a pointer to an object type PercVisualizer
	PercVisualizer *pv;
	pv = new PercVisualizer(col, row, "Here is the visualization");

	// color_choice will hold 1 of 2 values. If the cell needs to be open
	//then the value will be 1, else any other integer value will paint
	//the cell gold, indicating the percolation path
	int
		tpX = 0, botX = 0, tpY = 0, botY = 0, color_choice = 0,
		index = 0, parent = 0, x = 0, y = 0;

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			//we check to see if the cell is open if it is
			//then we paint that cell white to show its open
			if (isOpen(i, j))
			{
				tpX = pv->getTopX(j);
				botX = pv->getBottomX(j);
				tpY = pv->getTopY(i);
				botY = pv->getBottomY(i);
				color_choice = 1;

				pv->paintCell(tpX, tpY, botX, botY, color_choice);
			}
			if (pathToTop(row - 1, j))
			{
				index = ((row - 1) * row) + j;
				parent = Sets.Find(index);
			}

		}

	//we adjust the parent of all the indices
	//so the parent match up. Could be a little bit
	//expensive to be done for every trial, hence this is done
	//only for the final visualization
	for (int i = 0; i < row* col; i++)
		Sets.Find(i);

	// now we see if cell from bottom row that percolates
	//to top row and get its parent and paint all cell that
	//have that same parent
	for (int i = 0; i < row * col; i++)
	{
		int item = 0;
		item = Sets.getItem(i);
		//a
		if (item == parent)
		{
			x = i % col;
			y = i / col;
			tpX = pv->getTopX(x);
			botX = pv->getBottomX(x);
			tpY = pv->getTopY(y);
			botY = pv->getBottomY(y);
			color_choice = 2;

			pv->paintCell(tpX, tpY, botX, botY, color_choice);
		}
	}

	pv->displayVisualizer();
}

