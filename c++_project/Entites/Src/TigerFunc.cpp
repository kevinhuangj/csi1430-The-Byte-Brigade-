//
// Created by merri on 5/1/2024.
//


#include "Entites/Headers/TigerFunc.h"

#include <vector>
#include <cmath>

int foundHmnRow;
int foundHmnCol;

void findPeeps(Square (&pSquare)[dim][dim])
{
    int tigerRow = -1, tigerCol = -1;
    vector<int> HmnsRowLocations;
    vector<int> HmnsColLocations;

    // Find the human and all crops
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            if(pSquare[r][c].getType() == TIGER)
            {
                tigerRow = r;
                tigerCol = c;
            }
            else if(pSquare[r][c].getType() == HUMAN)
            {
                HmnsRowLocations.push_back(r);
                HmnsColLocations.push_back(c);
            }
        }
    }

    // Find the nearest crop within a radius of 4 squares
    double minDistance = 10000; // Initialize to a large value
    for(size_t i = 0; i < HmnsRowLocations.size(); i++)
    {
        double distance = std::sqrt(std::pow(HmnsRowLocations[i] - tigerRow, 2) + std::pow(HmnsColLocations[i] - tigerCol, 2));
        if(distance < minDistance && distance <= 80)
        {
            minDistance = distance;
            foundHmnRow = HmnsRowLocations[i];
            foundHmnCol = HmnsColLocations[i];
        }
    }

    // If no crops were found within the radius, set the human's square to GRASS
    if(minDistance == 10000)
    {
        pSquare[tigerRow][tigerCol].setType(GRASS);
    }
}

void moveToPeep(Square (&pSquare)[dim][dim])
{
    int currentHumanRow = -1;
    int currenttigerCol = -1;

    // First, find the HUMAN square and store its position
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            if(pSquare[r][c].getType() == TIGER)
            {
                currentHumanRow = r;
                currenttigerCol = c;
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
        pSquare[currentHumanRow][currenttigerCol].setType(GRASS);
        if(currentHumanRow > 0 && pSquare[currentHumanRow - 1][currenttigerCol].getType() != (WATER) && pSquare[currentHumanRow - 1][currenttigerCol].getType() != TIGER
           && abs(foundHmnRow - (currentHumanRow - 1)) < abs(foundHmnRow - currentHumanRow))
        {
            SDL_Delay(300);
            pSquare[currentHumanRow - 1][currenttigerCol].setType(TIGER);
        }
        else if(currentHumanRow < dim - 1 && pSquare[currentHumanRow + 1][currenttigerCol].getType() != WATER && currentHumanRow < dim - 1 && pSquare[currentHumanRow + 1][currenttigerCol].getType() != TIGER
                && abs(foundHmnRow - (currentHumanRow + 1)) < abs(foundHmnRow - currentHumanRow))
        {
            SDL_Delay(300);
            pSquare[currentHumanRow + 1][currenttigerCol].setType(TIGER);
        }
        else if(currenttigerCol > 0 && pSquare[currentHumanRow][currenttigerCol - 1].getType() != WATER && currenttigerCol > 0 && pSquare[currentHumanRow][currenttigerCol - 1].getType() != TIGER
                && abs(foundHmnCol - (currenttigerCol - 1)) < abs(foundHmnCol - currenttigerCol))
        {
            SDL_Delay(300);
            pSquare[currentHumanRow][currenttigerCol - 1].setType(TIGER);
        }
        else if(currenttigerCol < dim - 1 && pSquare[currentHumanRow][currenttigerCol + 1].getType() != WATER && currenttigerCol < dim - 1 && pSquare[currentHumanRow][currenttigerCol + 1].getType() != TIGER
                && abs(foundHmnCol - (currenttigerCol + 1)) < abs(foundHmnCol - currenttigerCol))
        {
            SDL_Delay(300);
            pSquare[currentHumanRow][currenttigerCol + 1].setType(TIGER);
        }
        else
        {
            // If all surrounding squares are water, check the vicinity for a non-water square closer to the crop
            for(int r = max(0, currentHumanRow - 2); r <= min(dim - 1, currentHumanRow + 2); r++)
            {
                for(int c = max(0, currenttigerCol - 2); c <= min(dim - 1, currenttigerCol + 2); c++)
                {
                    if(pSquare[r][c].getType() != WATER && pSquare[r][c].getType() != TIGER && abs(foundHmnRow - r) + abs(foundHmnCol - c) < abs(foundHmnRow - currentHumanRow) + abs(foundHmnCol - currenttigerCol))
                    {
                        SDL_Delay(300);
                        pSquare[r][c].setType(TIGER);
                        return;
                    }
                }
            }

            // If all squares in the vicinity are water, the human stays in its current position
            pSquare[currentHumanRow][currenttigerCol].setType(TIGER);
        }
    }
}
