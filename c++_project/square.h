/*
 * square.h
 *
 *  Created on: Apr 3, 2024
 *      Author: Kevin Huang, Eric Escobar, Junshen Huang, 
 *              Lucas Ulibarri, Merrick Beinhower, Zhicheng Zhao
 */


#ifndef SQUARE_H_
#define SQUARE_H_

#include "PLOTTER/SDL_Plotter.h"
#include "config.h"
#include "grid.h"
#include <random>
class Square
{

private:
    int row{}, col{};
    objType type;
    color _color;
    int numNeighbors;
    bool wasCrop = false;
public:

    Square(); // <-- Constructor

    Square(int numNeighbors, objType type); // <-- Constructor

    void draw(SDL_Plotter& g);

    void setRow(int r);

    void setCol(int c);

    void click();

    bool getWasCrop() const;

    bool setWasCrop(bool crop);

    int getRow() const;

    int getCol() const;

    int getNumNeighbors() const;

    void setNumNeighbors(int num);

    objType getType();
    objType setType(objType t);


};

#endif

