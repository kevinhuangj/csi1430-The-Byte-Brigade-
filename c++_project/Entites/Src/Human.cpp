//
// Created by Lucas_Ulibarri2 on 4/22/2024.
//

#include "Entites/Headers/Human.h"

Human::Human()
{
    hunger = 0;
    thirst = 0;
    objType type = HUMAN;
}



int Human::getHunger()
{
    return hunger;
}
void Human::setHunger(int h)
{
    hunger = h;
}

int Human::getThirst()
{
    return thirst;
}
void Human::setThirst(int t)
{
    thirst = t;
}

int Human::getRow()
{
    return row;
}
void Human::setRow(int r)
{
    row = r;
}

int Human::getCol()
{
    return col;
}
void Human::setCol(int c)
{
    col = c;
}

void Human::setPos(int row, int col)
{
    this->row = row;
    this->col = col;
}

void Human::draw(SDL_Plotter& g)
{
    int x = col * SIDE;
    int y = row * SIDE;
    //More drawing logic here?
    g.plotPixel(x, y, _color);
}

void Human::hunt()
{

    cout << "Hunting" << endl;      //FIXME: Need an algorithm for hunting
}
