//
// Created on 4/23/2024.
//
// Authors: Kevin, Lucas, Merrick, Eric, Zeno
//


#ifndef WORLDGENERATION_H
#define WORLDGENERATION_H

#include "square.h"
#include "config.h"
#include <random>

/**
 * This function is used to generate grass and water in a given square grid.
 *
 * The function takes three arguments: the number of grass and water squares to be generated,
 * and a 2D array of Square objects, passed by reference.
 * The array represents a grid where each Square object can potentially contain grass or water.
 * The function is expected to implement the logic to randomly distribute the specified number of grass and water squares within the grid.
 *
 * param numGrass The number of grass squares to be generated.
 * param numWater The number of water squares to be generated.
 * param pSquare A 2D array of Square objects representing the grid.
 */
void generateGrassAndWater(int numGrass, int numWater, Square (&pSquare)[dim][dim]);

/**
 * This function is used to generate crops around water in a given square grid.
 *
 * The function takes a 2D array of Square objects as an argument, passed by reference.
 * The array represents a grid where each Square object can potentially contain grass or water.
 * The function is expected to implement the logic to generate crops around water within the grid.
 *
 * param pSquare A 2D array of Square objects representing the grid.
 */
void generateCropAroundWater(Square (&pSquare)[dim][dim]);

/**
 * This function is used to regenerate crops in a given square grid.
 *
 * The function takes a 2D array of Square objects as an argument, passed by reference.
 * The array represents a grid where each Square object can potentially contain crops.
 * The function is expected to implement the logic to regenerate crops within the grid.
 *
 * param pSquare A 2D array of Square objects representing the grid.
 */
void cropRegeneration(Square (&pSquare)[dim][dim]);

#endif //WORLDGENERATION_H
