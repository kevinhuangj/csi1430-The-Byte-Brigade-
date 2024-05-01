//
// Created by lulib on 4/23/2024.
//

#include "Entites/Headers/HumanFunc.h"

#include <vector>
#include <cmath>

int foundCrpRow;
int foundCrpCol;

void findCrops(Square (&pSquare)[dim][dim])
{
    int humanRow = -1, humanCol = -1;
    vector<int> cropsRowLocations;
    vector<int> cropsColLocations;

    // Find the human and all crops
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            if(pSquare[r][c].getType() == HUMAN)
            {
                humanRow = r;
                humanCol = c;
            }
            else if(pSquare[r][c].getType() == CROPS)
            {
                cropsRowLocations.push_back(r);
                cropsColLocations.push_back(c);
            }
        }
    }

    // Find the nearest crop within a radius of 4 squares
    double minDistance = 10000; // Initialize to a large value
    for(size_t i = 0; i < cropsRowLocations.size(); i++)
    {
        double distance = std::sqrt(std::pow(cropsRowLocations[i] - humanRow, 2) + std::pow(cropsColLocations[i] - humanCol, 2));
        if(distance < minDistance && distance <= 8)
        {
            minDistance = distance;
            foundCrpRow = cropsRowLocations[i];
            foundCrpCol = cropsColLocations[i];
        }
    }

    // If no crops were found within the radius, set the human's square to GRASS
    if(minDistance == 10000)
    {
        pSquare[humanRow][humanCol].setType(GRASS);
    }
}

void moveToCrop(Square (&pSquare)[dim][dim])
{
    int currentHumanRow = -1;
    int currentHumanCol = -1;

    // First, find the HUMAN square and store its position
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            if(pSquare[r][c].getType() == HUMAN)
            {
                currentHumanRow = r;
                currentHumanCol = c;
                break;
            }
        }
        if(currentHumanRow != -1)
        {
            break;
        }
    }

    // Then, check the surrounding squares and move the human to a non-water square closer to the crop
    if(currentHumanRow != -1)
    {
        pSquare[currentHumanRow][currentHumanCol].setType(GRASS);
        if(currentHumanRow > 0 && pSquare[currentHumanRow - 1][currentHumanCol].getType() != WATER && abs(foundCrpRow - (currentHumanRow - 1)) < abs(foundCrpRow - currentHumanRow))
        {
            SDL_Delay(300);
            pSquare[currentHumanRow - 1][currentHumanCol].setType(HUMAN);
        }
        else if(currentHumanRow < dim - 1 && pSquare[currentHumanRow + 1][currentHumanCol].getType() != WATER && abs(foundCrpRow - (currentHumanRow + 1)) < abs(foundCrpRow - currentHumanRow))
        {
            SDL_Delay(300);
            pSquare[currentHumanRow + 1][currentHumanCol].setType(HUMAN);
        }
        else if(currentHumanCol > 0 && pSquare[currentHumanRow][currentHumanCol - 1].getType() != WATER && abs(foundCrpCol - (currentHumanCol - 1)) < abs(foundCrpCol - currentHumanCol))
        {
            SDL_Delay(300);
            pSquare[currentHumanRow][currentHumanCol - 1].setType(HUMAN);
        }
        else if(currentHumanCol < dim - 1 && pSquare[currentHumanRow][currentHumanCol + 1].getType() != WATER && abs(foundCrpCol - (currentHumanCol + 1)) < abs(foundCrpCol - currentHumanCol))
        {
            SDL_Delay(300);
            pSquare[currentHumanRow][currentHumanCol + 1].setType(HUMAN);
        }
        else
        {
            // If all surrounding squares are water, check the vicinity for a non-water square closer to the crop
            for(int r = max(0, currentHumanRow - 2); r <= min(dim - 1, currentHumanRow + 2); r++)
            {
                for(int c = max(0, currentHumanCol - 2); c <= min(dim - 1, currentHumanCol + 2); c++)
                {
                    if(pSquare[r][c].getType() != WATER && abs(foundCrpRow - r) + abs(foundCrpCol - c) < abs(foundCrpRow - currentHumanRow) + abs(foundCrpCol - currentHumanCol))
                    {
                        SDL_Delay(300);
                        pSquare[r][c].setType(HUMAN);
                        return;
                    }
                }
            }

            // If all squares in the vicinity are water, the human stays in its current position
            pSquare[currentHumanRow][currentHumanCol].setType(HUMAN);
        }
    }
}
