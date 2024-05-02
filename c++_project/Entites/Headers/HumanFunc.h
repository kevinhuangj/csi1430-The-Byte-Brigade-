//
// Created on 4/23/2024.
//
// Authors: Kevin, Lucas, Merrick, Eric, Zeno
//


#ifndef HUMANFUNC_H
#define HUMANFUNC_H

#include "square.h"
#include "config.h"


/**
 * This function is used to find crops in a given square grid.
 *
 * The function takes a 2D array of Square objects as an argument, passed by reference.
 * The array represents a grid where each Square object can potentially contain a crop.
 * The function is expected to implement the logic to locate the crops within the grid.
 *
 * param pSquare A 2D array of Square objects representing the grid.
 */
void findCrops(Square (&pSquare)[dim][dim]);

/**
 * This function is used to move a human to a crop in a given square grid.
 *
 * The function takes a 2D array of Square objects as an argument, passed by reference.
 * The array represents a grid where each Square object can potentially contain a crop.
 * The function is expected to implement the logic to move a human to a crop within the grid.
 *
 * param pSquare A 2D array of Square objects representing the grid.
 */
void moveToCrop(Square (&pSquare)[dim][dim]);

#endif //HUMANFUNC_H
