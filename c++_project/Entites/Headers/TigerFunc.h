//
// Created on 5/1/2024.
//
// Authors: Kevin, Lucas, Merrick, Eric, Zeno
//


#ifndef TIGERFUNC_H
#define TIGERFUNC_H

#include "square.h"
#include "config.h"

/**
 * This function is used to find humans in a given square grid.
 *
 * The function takes a 2D array of Square objects as an argument, passed by reference.
 * The array represents a grid where each Square object can potentially contain a human.
 * The function is expected to implement the logic to locate the humans within the grid.
 *
 * param pSquare A 2D array of Square objects representing the grid.
 */
void findPeeps(Square (&pSquare)[dim][dim]);

/**
 * This function is used to move a tiger to a human in a given square grid.
 *
 * The function takes a 2D array of Square objects as an argument, passed by reference.
 * The array represents a grid where each Square object can potentially contain a human.
 * The function is expected to implement the logic to move a tiger to a human within the grid.
 *
 * param pSquare A 2D array of Square objects representing the grid.
 */
void moveToPeep(Square (&pSquare)[dim][dim]);

#endif //TIGERFUNC_H
