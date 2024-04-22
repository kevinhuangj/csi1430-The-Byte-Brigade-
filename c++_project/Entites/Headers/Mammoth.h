#ifndef CSI1430_THE_BYTE_BRIGADE_MAMMOTH_H
#define CSI1430_THE_BYTE_BRIGADE_MAMMOTH_H
#include "PLOTTER/SDL_Plotter.h"
#include "config.h"
#include <iostream>
#include <string>
using namespace std;

class Mammoth {
private:
    int health;
    int endurance;
    int strength;
    int row, col;
    objType type;
    color _color = color(139, 69, 19);

public:
    Mammoth();

    int getHealth() const;
    void setHealth(int h);

    int getEndurance() const;
    void setEndurance(int e);

    int getStrength() const;
    void setStrength(int s);

    int getRow();
    void setRow(int r);

    int getCol();
    void setCol(int c);

    void setPos(int row, int col);

    void draw(SDL_Plotter& g);

    void graze();
    void migrate();
    void reproduce();
};

#endif //CSI1430_THE_BYTE_BRIGADE_MAMMOTH_H
