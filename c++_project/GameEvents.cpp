//
// Created by Lucas_Ulibarri2 on 4/10/2024.
//

#include "GameEvents.h"
#include "square.h"
#include "grid.h"

//Game events for the game of life

GameEvents::GameEvents()
{
    // Constructor
}

void GameEvents::underpopulationRule() {
    // Rule for underpopulation
    int dim = SIZE/SIDE;
    Square data[dim][dim];

    for(int r = 0;r < dim;r++)
    {
        for(int c = 0;c < dim;c++)
        {
            data[r][c].setRow(r);
            data[r][c].setCol(c);
        }
    }

    /*
    data.getNeighbors();                       //fixme
    if(data.getNeighbors() < 2)
    {
        data.setType(DEAD);
    }
    */

}


void GameEvents::overpopulationRule()
{
    // Rule for overpopulation
    cout << "Overpopulation Rule\n";
}

void GameEvents::reproductionRule()
{
    // Rule for reproduction
    cout << "Reproduction Rule\n";
}

void GameEvents::nextGenerationRule()
{
    // Rule for next generation
    cout << "Next Generation Rule\n";
}
