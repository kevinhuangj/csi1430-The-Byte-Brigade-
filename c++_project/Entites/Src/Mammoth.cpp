//
// Created by Lucas_Ulibarri2 on 4/22/2024.
//

#include "Entites/Headers/Mammoth.h"

Mammoth::Mammoth()
{
    health = 100;
    endurance = 100;
    strength = 100;
    objType type = MAMMOTH;
}

int Mammoth::getHealth() const
{
    return health;
}
void Mammoth::setHealth(int h)
{
    health = h;
}

int Mammoth::getEndurance() const
{
    return endurance;
}
void Mammoth::setEndurance(int e)
{
    endurance = e;
}

int Mammoth::getStrength() const
{
    return strength;
}
void Mammoth::setStrength(int s)
{
    strength = s;

}

int Mammoth::getRow()
{
    return row;
}
void Mammoth::setRow(int r)
{
    row = r;
}

int Mammoth::getCol()
{
    return col;
}
void Mammoth::setCol(int c)
{
    col = c;
}

void Mammoth::setPos(int row, int col)
{
    this->row = row;
    this->col = col;
}

void Mammoth::draw(SDL_Plotter& g)
{
    int x = col * SIDE;
    int y = row * SIDE;
    //More logic for drawing
    g.plotPixel(x, y, _color);
}

void Mammoth::graze()
{
    cout << "Mammoth is grazing" << endl;       //FIXME: Implement grazing
}
void Mammoth::migrate()
{
    cout << "Mammoth is migrating" << endl;     //FIXME: Implement migrating
}
void Mammoth::reproduce()
{
    cout << "Mammoth is reproducing" << endl;   //FIXME: Implement reproducing
}