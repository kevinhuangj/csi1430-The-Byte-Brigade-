/*
 * square.cpp
 *
 *  Created on: Apr 3, 2024
 *      Author: Kevin Huang
 *      Editted by Eric_Escobar, Junshen_Huang, Lucas_Ulibarri, Merrick_Beinhower, Zhicheng_Zhao
 */

#include "square.h"

Square::Square() // <-- Constructor
{
    row = 0;
    col = 0;
    type = DEAD;
    _color = color(128, 128, 128);
}

Square::Square(int row, int col, int numNeighbors, objType type)
{
    this-> row = row;
    this-> col = col;
    type = DEAD;
    _color = color(128, 128, 128);
}

void Square::draw(SDL_Plotter& g)
{
    for(int r = 0; r < SIDE; r++)
    {
        for(int c = 0; c < SIDE; c++)
        {
            g.plotPixel(c + SIDE * col, r + SIDE * row, _color);
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

int Square::getRow()
{
    return row;
}

int Square::getCol()
{
    return col;
}

//getter of type
objType Square::getType()
{
    return type;
}

//setter of type
objType Square::setType(objType t)
{
    type = t;
    switch (type)
    {
        case DEAD:
            _color = color(128,128,128);
            break;
        case CELL:
            _color = color(0,0,255);
            break;
        case GRASS:
            _color = color(0,0,0);
            break;
        case RABBIT:
            _color = color(128,128,128);
            break;
        case FOX:
            _color = color(255,128,128);
            break;
    }
    return type;
}

void Square::click()
{
    type = static_cast<objType>(static_cast<int>(type + 1) % numTypes);
    switch (type)
    {
        case DEAD:
            _color = color(128,128,128);
            break;
        case CELL:
            _color = color(0,0,255);
            break;
        case GRASS:
            _color = color(0,0,0);
            break;
        case RABBIT:
            _color = color(128,128,128);
            break;
        case FOX:
            _color = color(255,128,128);
            break;
    }
}


