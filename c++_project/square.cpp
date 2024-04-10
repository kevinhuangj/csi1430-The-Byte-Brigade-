/*
 * square.cpp
 *
 *  Created on: Apr 3, 2024
 *      Author: dylan
 */

#include "square.h"

Square::Square()
{
	row = 0;
	col = 0;
	type = WATER;
	_color = color(25,25, 255);
}

void Square::draw(SDL_Plotter& g)
{
	for(int r = 0;r < SIDE;r++)
	{
		for(int c = 0;c < SIDE;c++)
		{
			g.plotPixel(c + SIDE*col, r + SIDE*row,_color);
		}
	}
}

void Square::setRow(int r)
{
	row = r;
}

void Square::setCol(int c)
{
	col = c;
}

void Square::click()
{
	type = static_cast<objType>(static_cast<int>(type + 1) % NUMTYPES);

	switch(type)
	{
	case DEAD: _color = color(255,255,255);
	break;
	case WATER: _color = color(25,25,255);
	break;
	case GRASS: _color = color(25,255,25);
	break;
	case RABBIT: _color = color(0,0,0);
	break;
	case FOX: _color = color(255,25,25);
	break;
	}
}



