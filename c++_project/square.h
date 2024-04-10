/*
 * square.h
 *
 *  Created on: Apr 3, 2024
 *      Author: dylan
 */


#ifndef SQUARE_H_
#define SQUARE_H_

#include "SDL_Plotter.h"
#include "config.h"

class Square
{

private:
	int row, col;
	objType type;
	color _color;

public:
	Square();
	void draw(SDL_Plotter& g);
	void setRow(int);
	void setCol(int);
	void click();
};

#endif

