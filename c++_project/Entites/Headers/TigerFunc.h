//
// Created by merri on 5/1/2024.
//

#ifndef TIGERFUNC_H
#define TIGERFUNC_H

#include "square.h"
#include "config.h"

//Big O Notation O(n^2)
void findPeeps(Square (&pSquare)[dim][dim]);

void moveToPeep(Square (&pSquare)[dim][dim]);

#endif //TIGERFUNC_H
