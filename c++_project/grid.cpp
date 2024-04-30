/*
 * grid.cpp
 *
 *  Created on: Apr 3, 2024
 *      Author: Kevin Huang
 *      editted by Eric Escobar,Junshen Huang, Lucas Ulibarri, Merrick_Beinhower, Zhicheng_Zhao
 */

#include "grid.h"

void drawLine(int x1, int y1, int x2, int y2, int R, int G, int B, SDL_Plotter& g)
{
    double m = slope(x1,y1,x2,y2);
    double b = y_intercept(x1,y1,x2,y2);
    int y;
    if(hasSlope(x1,y1,x2,y2)){
        for(int x = min(x1,x2); x <= max(x1,x2); x++)
        {
            y = m * x + b;
            g.plotPixel(x, y, R,G,B);
        }
        g.update();
    }

    else
    {
        for(int y = min(y1,y2); y <= max(y1,y2); y++)
        {
            g.plotPixel(x1, y, R,G,B);
        }
        g.update();
    }
}

double slope(int x1, int y1, int x2, int y2)
{
    // delta y / delta x
    return static_cast<double>(y1-y2)/(x1-x2);
}

double y_intercept(int x1, int y1, int x2, int y2)
{
    double m = slope(x1,y1,x2,y2);
    return y1 - m * x1;
}

void drawGrid(SDL_Plotter& g)
{
    int x1, y1, x2, y2, R=0, G=0, B=0;

    //draw vertical lines
    y1 = 0;
    y2 = SIZE-1;
    int numVLines = SIZE/SIDE + 1;

    for(int i = 0; i < numVLines; i++)
    {
        x1 = x2 = i * SIDE;
        drawLine(x1, y1, x2, y2, R, G, B, g);
    }

    //draw horizontal line
    int numHLines = SIZE/SIDE + 1;
    x1 = 0;
    x2 = SIZE-1;

    for(int i = 0; i < numHLines; i++)
    {
        y1 = y2 = i*SIDE;
        drawLine(x1, y1, x2, y2, R, G, B, g);

    }
}

bool hasSlope(int x1, int y1, int x2, int y2)
{
    return x1 != x2;
}

void drawSquare(int x_offset, int y_offset, int R, int G, int B, SDL_Plotter& g)
{
    for(int x = 0; x < SIDE; x++)
    {
        for(int y = 0; y < SIDE; y++)
        {
            g.plotPixel(x + x_offset, y + y_offset, R, G, B);
        }
    }
}
