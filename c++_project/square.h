/*
 * square.h
 *
 *  Created on: Apr 3, 2024
 *      Author: Kevin Huang 
 *      Editted by Eric Escobar, Junshen Huang, Lucas Ulibarri, Merrick Beinhower, Zhicheng Zhao
 */


#ifndef SQUARE_H_
#define SQUARE_H_

#include "PLOTTER/SDL_Plotter.h"
#include "config.h"
#include "grid.h"

class Square
{

private:
    int row{}, col{};
    objType type;
    color _color;
    int numNeighbors;
public:
    Square(); // <-- Constructor

    Square(int numNeighbors, objType type); // <-- Constructor

    struct humanAttribute
    {
        int hunger = 4, thirst = 100;
        void setHunger(int h)
        {
            hunger = h;
        }
    };

    humanAttribute attributesHUMAN;

    void draw(SDL_Plotter& g);

    void setRow(int r);

    void setCol(int c);

    void click();

    int getRow();

    int getCol();

    int getNumNeighbors() const;

    void setNumNeighbors(int num);

    objType getType();
    objType setType(objType t);


};

#endif

