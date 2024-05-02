//
// Created on 5/1/2024.
//
// Authors: Kevin, Lucas, Merrick, Eric, Zeno
//


#ifndef CSI1430_THE_BYTE_BRIGADE__MAMOTHFUNC_H
#define CSI1430_THE_BYTE_BRIGADE__MAMOTHFUNC_H

#include "square.h"
#include "config.h"

/**
 * This function is used to find grass in a given square grid.
 *
 * The function takes a 2D array of Square objects as an argument, passed by reference.
 * The array represents a grid where each Square object can potentially contain grass.
 * The function is expected to implement the logic to locate the grass within the grid.
 *
 * param pSquare A 2D array of Square objects representing the grid.
 */
void findGrass(Square (&pSquare)[dim][dim]);

/**
 * This function is used to move a mammoth to grass in a given square grid.
 *
 * The function takes a 2D array of Square objects as an argument, passed by reference.
 * The array represents a grid where each Square object can potentially contain grass.
 * The function is expected to implement the logic to move a mammoth to grass within the grid.
 *
 * param pSquare A 2D array of Square objects representing the grid.
 */
void moveToGrass(Square (&pSquare)[dim][dim]);


#endif //CSI1430_THE_BYTE_BRIGADE__MAMOTHFUNC_H
