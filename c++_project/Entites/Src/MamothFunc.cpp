//
// Created by merri on 5/1/2024.
//

#include "Entites/Headers/MamothFunc.h"

#include <vector>
#include <cmath>

int foundGrsRow;
int foundGrsCol;

void findGrass(Square (&pSquare)[dim][dim])
{
    int mammothRow = -1, mammothCol = -1;
    vector<int> grassRowLocations;
    vector<int> grassColLocations;

    // Find the Mammoth and all crops
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            if(pSquare[r][c].getType() == MAMMOTH)
            {
                mammothRow = r;
                mammothCol = c;
            }
            else if(pSquare[r][c].getType() == GRASS)
            {
                grassRowLocations.push_back(r);
                grassColLocations.push_back(c);
            }
        }
    }

    // Find the nearest crop within a radius of 4 squares
    double minDistance = 10000; // Initialize to a large value
    for(size_t i = 0; i < grassRowLocations.size(); i++)
    {
        double distance = std::sqrt(std::pow(grassRowLocations[i] - mammothRow, 2) + std::pow(grassColLocations[i] - mammothCol, 2));
        if(distance < minDistance && distance <= 8)
        {
            minDistance = distance;
            foundGrsRow = grassRowLocations[i];
            foundGrsCol = grassColLocations[i];
        }
    }

    // If no crops were found within the radius, set the Mammoth's square to GRASS
    if(minDistance == 10000)
    {
        pSquare[mammothRow][mammothCol].setType(DIRT);
    }
}

void moveToGrass(Square (&pSquare)[dim][dim])
{
    int currentmammothRow = -1;
    int currentmammothCol = -1;

    // First, find the Mammoth square and store its position
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            if(pSquare[r][c].getType() == MAMMOTH)
            {
                currentmammothRow = r;
                currentmammothCol = c;
                break;
            }
        }
        if(currentmammothRow != -1)
        {
            break;
        }
    }

    // Then, check the surrounding squares and move the Mammoth to a non-water square closer to the crop
    if(currentmammothRow != -1)
    {
        pSquare[currentmammothRow][currentmammothCol].setType(DIRT);
        if(currentmammothRow > 0 && pSquare[currentmammothRow - 1][currentmammothCol].getType() != (WATER) && pSquare[currentmammothRow - 1][currentmammothCol].getType() != MAMMOTH
           && abs(foundGrsRow - (currentmammothRow - 1)) < abs(foundGrsRow - currentmammothRow))
        {
            SDL_Delay(300);
            pSquare[currentmammothRow - 1][currentmammothCol].setType(MAMMOTH);
        }
        else if(currentmammothRow < dim - 1 && pSquare[currentmammothRow + 1][currentmammothCol].getType() != WATER && currentmammothRow < dim - 1 && pSquare[currentmammothRow + 1][currentmammothCol].getType() != MAMMOTH
                && abs(foundGrsRow - (currentmammothRow + 1)) < abs(foundGrsRow - currentmammothRow))
        {
            SDL_Delay(300);
            pSquare[currentmammothRow + 1][currentmammothCol].setType(MAMMOTH);
        }
        else if(currentmammothCol > 0 && pSquare[currentmammothRow][currentmammothCol - 1].getType() != WATER && currentmammothCol > 0 && pSquare[currentmammothRow][currentmammothCol - 1].getType() != MAMMOTH
                && abs(foundGrsCol - (currentmammothCol - 1)) < abs(foundGrsCol - currentmammothCol))
        {
            SDL_Delay(300);
            pSquare[currentmammothRow][currentmammothCol - 1].setType(MAMMOTH);
        }
        else if(currentmammothCol < dim - 1 && pSquare[currentmammothRow][currentmammothCol + 1].getType() != WATER && currentmammothCol < dim - 1 && pSquare[currentmammothRow][currentmammothCol + 1].getType() != MAMMOTH
                && abs(foundGrsCol - (currentmammothCol + 1)) < abs(foundGrsCol - currentmammothCol))
        {
            SDL_Delay(300);
            pSquare[currentmammothRow][currentmammothCol + 1].setType(MAMMOTH);
        }
        else
        {
            // If all surrounding squares are water, check the vicinity for a non-water square closer to the crop
            for(int r = max(0, currentmammothRow - 2); r <= min(dim - 1, currentmammothRow + 2); r++)
            {
                for(int c = max(0, currentmammothCol - 2); c <= min(dim - 1, currentmammothCol + 2); c++)
                {
                    if(pSquare[r][c].getType() != WATER && pSquare[r][c].getType() != MAMMOTH && abs(foundGrsRow - r) + abs(foundGrsCol - c) < abs(foundGrsRow - currentmammothRow) + abs(foundGrsCol - currentmammothCol))
                    {
                        SDL_Delay(300);
                        pSquare[r][c].setType(MAMMOTH);
                        return;
                    }
                }
            }

            // If all squares in the vicinity are water, the Mammoth stays in its current position
            pSquare[currentmammothRow][currentmammothCol].setType(MAMMOTH);
        }
    }
}
