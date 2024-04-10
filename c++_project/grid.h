/*
 * grid.h
 *
 *  Created on: Apr 3, 2024
 *      Author: dylan
 */

#ifndef GRID_H_
#define GRID_H_

#include "SDL_Plotter.h"
#include "config.h"

void drawLine(int x1, int y1, int x2, int y2, int R, int G, int B, SDL_Plotter& g);
double slope(int x1, int y1, int x2, int y2);
double y_intercept(int x1, int y1, int x2, int y2);
void drawGrid(SDL_Plotter& g);
bool hasSlope(int x1, int y1, int x2, int y2);
void drawSquare(int x, int y, int R, int G, int B, SDL_Plotter& g);



#endif /* GRID_H_ */
