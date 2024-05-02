//
// Created by lulib on 4/23/2024.
//

#include "Entites/Headers/MamothFunc.h"

#include <vector>
#include <cmath>
#include <random>


int foundGraRow;
int foundGraCol;
int MMTrandCol;
int MMTrandRow;

void findGrass(Square (&pSquare)[dim][dim])
{
    int mammothRow = -1, mammothCol = -1;
    vector<int> grassRowLocations;
    vector<int> grassColLocations;

    // Find the MAMMOTH and all Grass

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
            foundGraRow = grassRowLocations[i];
            foundGraCol = grassColLocations[i];
        }
    }

    // If no Grass were found within the radius, set the MAMMOTH's square to GRASS
    if(minDistance == 10000)
    {
        pSquare[mammothRow][mammothCol].setType(GRASS);
    }
}

void moveToGrass(Square (&pSquare)[dim][dim])
{
    int currentmammothRow = -1;
    int currentmammothCol = -1;

    // First, find the MAMMOTH square and store its position and its random
    int MMTrandRow = rand()%2;
    int MMTrandCol = rand()%2;

    if(MMTrandRow == 0) {
        for (int r = 0; r < dim; r++) {
            if(MMTrandCol == 0) {
                for (int c = 0; c < dim; c++) {
                    if (pSquare[r][c].getType() == MAMMOTH) {
                        currentmammothRow = r;
                        currentmammothCol = c;
                        break;
                    }
                }
            }else{
                for (int c = dim; c >= 0; c--) {
                    if (pSquare[r][c].getType() == MAMMOTH) {
                        currentmammothRow = r;
                        currentmammothCol = c;
                        break;
                    }
                }

            }
            if (currentmammothRow != -1) {
                break;
            }
        }
    }else{
        for (int r = dim; r >= 0; r--) {
            if(MMTrandCol == 0) {
                for (int c = 0; c < dim; c++) {
                    if (pSquare[r][c].getType() == MAMMOTH) {
                        currentmammothRow = r;
                        currentmammothCol = c;
                        break;
                    }
                }
            }else{
                for (int c = dim; c >= 0; c--) {
                    if (pSquare[r][c].getType() == MAMMOTH) {
                        currentmammothRow = r;
                        currentmammothCol = c;
                        break;
                    }
                }

            }
            if (currentmammothRow != -1) {
                break;
            }
        }
    }

    // Then, check the surrounding squares and move the MAMMOTH to a non-water square closer to the crop
    if(currentmammothRow != -1)
    {
        pSquare[currentmammothRow][currentmammothCol].setType(DIRT);
        if(currentmammothRow > 0 && pSquare[currentmammothRow - 1][currentmammothCol].getType() != (WATER) && pSquare[currentmammothRow - 1][currentmammothCol].getType() != MAMMOTH
           && abs(foundGraRow - (currentmammothRow - 1)) < abs(foundGraRow - currentmammothRow))
        {
            SDL_Delay(300);
            pSquare[currentmammothRow - 1][currentmammothCol].setType(MAMMOTH);
        }
        else if(currentmammothRow < dim - 1 && pSquare[currentmammothRow + 1][currentmammothCol].getType() != WATER && currentmammothRow < dim - 1 && pSquare[currentmammothRow + 1][currentmammothCol].getType() != MAMMOTH
                && abs(foundGraRow - (currentmammothRow + 1)) < abs(foundGraRow - currentmammothRow))
        {
            SDL_Delay(300);
            pSquare[currentmammothRow + 1][currentmammothCol].setType(MAMMOTH);
        }
        else if(currentmammothCol > 0 && pSquare[currentmammothRow][currentmammothCol - 1].getType() != WATER && currentmammothCol > 0 && pSquare[currentmammothRow][currentmammothCol - 1].getType() != MAMMOTH
                && abs(foundGraCol - (currentmammothCol - 1)) < abs(foundGraCol - currentmammothCol))
        {
            SDL_Delay(300);
            pSquare[currentmammothRow][currentmammothCol - 1].setType(MAMMOTH);
        }
        else if(currentmammothCol < dim - 1 && pSquare[currentmammothRow][currentmammothCol + 1].getType() != WATER && currentmammothCol < dim - 1 && pSquare[currentmammothRow][currentmammothCol + 1].getType() != MAMMOTH
                && abs(foundGraCol - (currentmammothCol + 1)) < abs(foundGraCol - currentmammothCol))
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
                    if(pSquare[r][c].getType() != WATER && pSquare[r][c].getType() != MAMMOTH && abs(foundGraRow - r) + abs(foundGraCol - c) < abs(foundGraRow - currentmammothRow) + abs(foundGraCol - currentmammothCol))
                    {
                        SDL_Delay(150);
                        pSquare[r][c].setType(MAMMOTH);
                        return;
                    }
                }
            }

            // If all squares in the vicinity are water, the MAMMOTH stays in its current position
            pSquare[currentmammothRow][currentmammothCol].setType(MAMMOTH);
        }
    }
}
