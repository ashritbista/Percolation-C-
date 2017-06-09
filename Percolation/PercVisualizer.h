#pragma once
/*
* PercVisualizer.h
*
*  Created on: Nov 15, 2016
*      Author: Ashrit
*/

#ifndef PERCVISUALIZER_H_
#define PERCVISUALIZER_H_
#endif /* PERCVISUALIZER_H_ */

#include <iostream>
#include <string>
#include"CImg/CImg.h"

using namespace std;
using namespace cimg_library;

class PercVisualizer
{
public:
	PercVisualizer(int, int, string);
	void paintCell(int, int, int, int, int);
	void displayVisualizer();
	void getCellDimension();
	int getTopX(int);
	int getTopY(int);
	int getBottomX(int);
	int getBottomY(int);

private:
	int row, col, x_offset, y_offset, cell_width, cell_height;
	CImg <unsigned char> *canvas;
};

//Constructor, creates an instance of the object
PercVisualizer::PercVisualizer(int x, int y, string t)
{
	row = x;
	col = y;
	x_offset = 10;
	y_offset = 10;
	unsigned char boundary[] = { 0, 0, 255 };

	getCellDimension();

	int
		window_height = 2 * (y_offset)+col * (cell_height),
		window_width = 2 * (x_offset)+row * (cell_width);

	canvas = new CImg <unsigned char>(window_width, window_height, 1, 3, 0);

	for (int i = 0; i <= row; i++)
	{
		canvas->draw_line(x_offset, (y_offset + i * cell_height), (x_offset + row * cell_width),
			(y_offset + i * cell_height), boundary);
	}

	for (int i = 0; i <= col; i++)
	{
		canvas->draw_line((x_offset + i * cell_width), y_offset, (x_offset + i * cell_width),
			(y_offset + col * cell_height), boundary);
	}
}

//This gets the dimension for cell's height and width
void PercVisualizer::getCellDimension()
{
	if (row <= 70)
	{
		cell_width = 10;
		cell_height = 10;
	}

	if (row > 70 && row <= 120)
	{
		cell_width = 5;
		cell_height = 5;
	}

	if (row >= 121 && row <= 200)
	{
		cell_width = 3;
		cell_height = 3;
	}
}

//In order to paint the cell, this function gets
//the x-coord from the upper boundary left cell.
int PercVisualizer::getTopX(int c)
{
	int topX = 0;

	topX = x_offset + c * cell_width;

	return topX;
}

//gets the y-coord from the upper left boundary of the cell
int PercVisualizer::getTopY(int r)
{
	int topY = 0;

	topY = y_offset + r * cell_height;
	return topY;
}

//get the x-coord from the bottom right boundary of the cell
int PercVisualizer::getBottomX(int c)
{
	int bottomX = 0;

	bottomX = x_offset + c * cell_width + cell_width;

	return bottomX;
}

//get the y-coord from the bottom right boundary of the cell
int PercVisualizer::getBottomY(int r)
{
	int bottomY = 0;

	bottomY = y_offset + r * cell_height + cell_height;
	return bottomY;
}

//This function paints the cell with appropriate colors
//initially the canvas is black, so are the blocked cells
//when the cells are unblocked it turns white and the percolation
//path is gold
void PercVisualizer::paintCell(int tp_x, int tp_y, int bot_x, int bot_y, int color_choice)
{
	unsigned char color[] = { 0, 0, 0 };

	if (color_choice == 1)
	{
		color[0] = 255;
		color[1] = 255;
		color[2] = 255;
	}

	else
	{
		color[0] = 255;
		color[1] = 165;
		color[2] = 0;
	}

	canvas->draw_rectangle(tp_x + 1, tp_y + 1, bot_x - 1, bot_y - 1, color, 1);
}

//This function will display the window that will visualize the percolation path
void PercVisualizer::displayVisualizer()
{
	CImgDisplay disp(*canvas, "System grid");

	while (!disp.is_closed())
	{
		disp.wait();
	}
}

