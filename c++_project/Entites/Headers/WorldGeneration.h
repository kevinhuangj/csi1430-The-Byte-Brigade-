//
// Created by lulib on 4/23/2024.
//

#ifndef WORLDGENERATION_H
#define WORLDGENERATION_H

#include "square.h"
#include "config.h"
#include <random>

// Big O Notation O(n^2)
void generateGrassAndWater(int numGrass, int numWater, Square (&pSquare)[dim][dim]);

// Big O Notation O(n^2)
void generateCropAroundWater(Square (&pSquare)[dim][dim]);

#endif //WORLDGENERATION_H
