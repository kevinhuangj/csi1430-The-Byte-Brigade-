//
// Created by lulib on 4/23/2024.
//

#ifndef HUMANFUNC_H
#define HUMANFUNC_H

#include "square.h"
#include "config.h"

//Big O Notation O(n^2)
void findCrops(Square (&pSquare)[dim][dim]);


void moveToCrop(Square (&pSquare)[dim][dim]);

#endif //HUMANFUNC_H
