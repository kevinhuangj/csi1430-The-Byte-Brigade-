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
    type = DIRT;
    numNeighbors = 0;
    //color brown = color(128, 64, 0);
    _color = color(128, 64, 0);
}

Square::Square(int numNeighbors, objType type)
{
    row = 0;
    col = 0;
    numNeighbors = 0;
    type = DIRT;
    _color = color(128, 64, 0);
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
    this->type = t;
    switch (type)
    {
        case DIRT:
            _color = color(128, 64, 0); // brown
            break;
        case CROPS:
            _color = color(255, 255, 0); // bright yellow
            break;
        case GRASS:
            _color = color(0, 128, 0); // Dark green
            break;
        case HUMAN:
            _color = color(255, 0, 0); // bright red
            break;
        case MAMMOTH:
            _color = color(0, 165, 255); // Baby blue
            break;
        case TIGER:
            _color = color(255, 165, 0); // orange
            break;
        case WATER:
            _color = color(0, 0, 255); // blue
    }
    return type;
}

void Square::click()
{
    type = static_cast<objType>(static_cast<int>(type + 1) % numTypes);
    switch (type)
    {
        case DIRT:
            _color = color(128, 64, 0); // brown
            break;
        case CROPS:
            _color = color(255, 255, 0); // bright yellow
            break;
        case GRASS:
            _color = color(0, 128, 0); // Dark green
            break;
        case HUMAN:
            _color = color(255, 0, 0); // bright red
            break;
        case MAMMOTH:
            _color = color(0, 165, 255); // Baby blue
            break;
        case TIGER:
            _color = color(255, 165, 0); // orange
            break;
        case WATER:
            _color = color(0, 0, 255); // blue
    }
}

int Square::getNumNeighbors() const
{
    return numNeighbors;
}

void Square::setNumNeighbors(int num)
{
    numNeighbors = num;
}


