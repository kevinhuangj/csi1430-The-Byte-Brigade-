//
// Created by Lucas_Ulibarri2 on 4/22/2024.
//

#ifndef CSI1430_THE_BYTE_BRIGADE__HUMAN_H
#define CSI1430_THE_BYTE_BRIGADE__HUMAN_H

#include "PLOTTER/SDL_Plotter.h"
#include "config.h"
#include <iostream>
#include <string>
using namespace std;

class Human
{
private:
    int health;
    int hunger;
    int thirst;
    int row, col;
    string tool;
    objType type;
    color _color = color(210, 180, 140);

public:
    Human();

    int getHealth();
    void setHealth(int h);

    int getHunger();
    void setHunger(int h);

    int getThirst();
    void setThirst(int t);

    string getTool();
    void setTool(string t);

    int getRow();
    void setRow(int r);

    int getCol();
    void setCol(int c);

    void setPos(int row, int col);

    void draw(SDL_Plotter& g);


    void hunt();
};


#endif //CSI1430_THE_BYTE_BRIGADE__HUMAN_H
