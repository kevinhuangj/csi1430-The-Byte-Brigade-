//
// Created by merri on 5/1/2024.
//


#include "Entites/Headers/TigerFunc.h"

#include <vector>
#include <cmath>
#include <random>


int foundHmnRow;
int foundHmnCol;
int TGRrandRow;
int TGRrandCol;


void findPeeps(Square (&pSquare)[dim][dim])
{
    int tigerRow = -1, tigerCol = -1;
    vector<int> HmnsRowLocations;
    vector<int> HmnsColLocations;

    // Find the Tiger and all crops
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

    // If no crops were found within the radius, set the Tiger's square to GRASS
    if(minDistance == 10000)
    {
        pSquare[tigerRow][tigerCol].setType(GRASS);
    }
}

void moveToPeep(Square (&pSquare)[dim][dim])
{
    int currentTigerRow = -1;
    int currentTigerCol = -1;

    // First, find the Tiger square and store its position
    TGRrandRow = rand()%2;
    TGRrandCol = rand()%2;

    if(TGRrandRow == 0) {
        for (int r = 0; r < dim; r++) {
            if(TGRrandCol == 0) {
                for (int c = 0; c < dim; c++) {
                    if (pSquare[r][c].getType() == TIGER) {
                        currentTigerRow = r;
                        currentTigerCol = c;
                        break;
                    }
                }
            }else{
                for (int c = dim; c >= 0; c--) {
                    if (pSquare[r][c].getType() == TIGER) {
                        currentTigerRow = r;
                        currentTigerCol = c;
                        break;
                    }
                }

            }
            if (currentTigerRow != -1) {
                break;
            }
        }
    }else{
        for (int r = dim; r >= 0; r--) {
            if(TGRrandCol == 0) {
                for (int c = 0; c < dim; c++) {
                    if (pSquare[r][c].getType() == TIGER) {
                        currentTigerRow = r;
                        currentTigerCol = c;
                        break;
                    }
                }
            }else{
                for (int c = dim; c >= 0; c--) {
                    if (pSquare[r][c].getType() == TIGER) {
                        currentTigerRow = r;
                        currentTigerCol = c;
                        break;
                    }
                }

            }
            if (currentTigerRow != -1) {
                break;
            }
        }
    }


    // Then, check the surrounding squares and move the Tiger to a non-water square closer to the crop
    if(currentTigerRow != -1)
    {
        pSquare[currentTigerRow][currentTigerCol].setType(GRASS);
        if(currentTigerRow > 0 && pSquare[currentTigerRow - 1][currentTigerCol].getType() != (WATER) && pSquare[currentTigerRow - 1][currentTigerCol].getType() != TIGER
           && abs(foundHmnRow - (currentTigerRow - 1)) < abs(foundHmnRow - currentTigerRow))
        {
            SDL_Delay(300);
            pSquare[currentTigerRow - 1][currentTigerCol].setType(TIGER);
        }
        else if(currentTigerRow < dim - 1 && pSquare[currentTigerRow + 1][currentTigerCol].getType() != WATER && currentTigerRow < dim - 1 && pSquare[currentTigerRow + 1][currentTigerCol].getType() != TIGER
                && abs(foundHmnRow - (currentTigerRow + 1)) < abs(foundHmnRow - currentTigerRow))
        {
            SDL_Delay(300);
            pSquare[currentTigerRow + 1][currentTigerCol].setType(TIGER);
        }
        else if(currentTigerCol > 0 && pSquare[currentTigerRow][currentTigerCol - 1].getType() != WATER && currentTigerCol > 0 && pSquare[currentTigerRow][currentTigerCol - 1].getType() != TIGER
                && abs(foundHmnCol - (currentTigerCol - 1)) < abs(foundHmnCol - currentTigerCol))
        {
            SDL_Delay(300);
            pSquare[currentTigerRow][currentTigerCol - 1].setType(TIGER);
        }
        else if(currentTigerCol < dim - 1 && pSquare[currentTigerRow][currentTigerCol + 1].getType() != WATER && currentTigerCol < dim - 1 && pSquare[currentTigerRow][currentTigerCol + 1].getType() != TIGER
                && abs(foundHmnCol - (currentTigerCol + 1)) < abs(foundHmnCol - currentTigerCol))
        {
            SDL_Delay(300);
            pSquare[currentTigerRow][currentTigerCol + 1].setType(TIGER);
        }
        else
        {
            // If all surrounding squares are water, check the vicinity for a non-water square closer to the crop
            for(int r = max(0, currentTigerRow - 2); r <= min(dim - 1, currentTigerRow + 2); r++)
            {
                for(int c = max(0, currentTigerCol - 2); c <= min(dim - 1, currentTigerCol + 2); c++)
                {
                    if(pSquare[r][c].getType() != WATER && pSquare[r][c].getType() != TIGER && abs(foundHmnRow - r) + abs(foundHmnCol - c) < abs(foundHmnRow - currentTigerRow) + abs(foundHmnCol - currentTigerCol))
                    {
                        SDL_Delay(100);
                        pSquare[r][c].setType(TIGER);
                        return;
                    }
                }
            }

            // If all squares in the vicinity are water, the Tiger stays in its current position
            pSquare[currentTigerRow][currentTigerCol].setType(TIGER);
        }
    }
}
