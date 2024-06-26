/*
 * square.h
 *
 *  Created on: Apr 3, 2024
 *      Author: Kevin Huang 
 *      Editted by Eric Escobar, Junshen Huang, Lucas Ulibarri, Merrick Beinhower, Zhicheng Zhao
 */


#ifndef SQUARE_H_
#define SQUARE_H_

#include "SDL_Plotter.h"
#include "config.h"
#include "grid.h"

class Square
{

private:
    int row{}, col{};
    objType type;
    color _color;
public:
    Square(); // <-- Constructor

    Square(int row, int col, int numNeighbors, objType type); // <-- Constructor

    void draw(SDL_Plotter& g);

    void setRow(int r);

    void setCol(int c);

    void click();

    int getRow();

    int getCol();

    objType getType();
    objType setType(objType t);


};

#endif

