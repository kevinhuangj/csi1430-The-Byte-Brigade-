//
// Created by lulib on 4/23/2024.
//

#ifndef WORLDGENERATION_H
#define WORLDGENERATION_H

#include "square.h"
#include "config.h"
#include <random>

void generateGrassAndWater(int numGrass, int numWater, Square (&pSquare)[dim][dim]);

void generateCropAroundWater(Square (&pSquare)[dim][dim]);

#endif //WORLDGENERATION_H
