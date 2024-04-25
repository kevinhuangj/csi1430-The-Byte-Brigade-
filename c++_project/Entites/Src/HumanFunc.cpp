//
// Created by lulib on 4/23/2024.
//

#include "Entites/Headers/HumanFunc.h"

int foundCrpCol;
int foundCrpRow;
bool foundCrop;


void findCrops(Square (&pSquare)[dim][dim])
{
    //Goes through entire grid
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            //if the iterator comes a cross a tile that is type HUMAN
            if(pSquare[r][c].getType() == HUMAN)
            {
                //Check to see of THIS human tile sees a crop within the immediate 8 tiles around
                // itself. if there is a crop, we set that crop type to dirt(consuming it).
                foundCrop = false;
                for(int dr = -1; dr <= 1; dr++)
                {
                    for(int dc = -1; dc <= 1; dc++)
                    {
                        if(r+dr >= 0  &&  r+dr < dim  &&  c+dc >= 0  &&  c+dc < dim  &&  pSquare[r+dr][c+dc].getType() == CROPS)
                        {
                            foundCrop = true;
                            pSquare[r+dr][c+dc].setType(DIRT); // Change CROPS to DIRT
                            pSquare[r][c].attributesHUMAN.setHunger(8); // Reset the hunger of the human
                            break;
                        }
                    }
                    if(foundCrop)
                    {
                        pSquare[r][c].attributesHUMAN.setHunger(8); // Reset the hunger of the human
                        break;
                    }
                }

                if(!foundCrop)
                {
                    //This is to check the additional area around the already checked
                    // immediate area around the current Human.
                    for(int dr = -2; dr <= 2; dr++)
                    {
                        for(int dc = -2; dc <= 2; dc++)
                        {
                            if(r+dr >= 0  &&  r+dr < dim  &&  c+dc >= 0  &&  c+dc < dim  &&  pSquare[r+dr][c+dc].getType() == CROPS)
                            {
                                foundCrop = true;
                                foundCrpRow = r + dr;
                                foundCrpCol = c + dc;
                                cout << "CROPS found at: " << r+dr << ", " << c+dc << endl; // Output the location of CROPS
                                break;
                            }
                        }
                        if(foundCrop)
                        {
                            break;
                        }
                    }
                }
                if(!foundCrop)
                {
                    pSquare[r][c].setType(GRASS);
                }
            }
        }
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

    // Then, update the position of the HUMAN square
    if(currentHumanRow != -1 && foundCrop)
    {
        pSquare[currentHumanRow][currentHumanCol].setType(GRASS);
        if(foundCrpRow < pSquare[currentHumanRow][currentHumanCol].getRow() && currentHumanRow > 0)
        {
            pSquare[currentHumanRow - 1][currentHumanCol].setType(HUMAN);
        }
        else if(foundCrpRow > pSquare[currentHumanRow][currentHumanCol].getRow() && currentHumanRow < dim - 1)
        {
            pSquare[currentHumanRow + 1][currentHumanCol].setType(HUMAN);
        }
        else if(foundCrpRow == pSquare[currentHumanRow][currentHumanCol].getRow())
        {
            if(foundCrpCol < pSquare[currentHumanRow][currentHumanCol].getCol() && currentHumanCol > 0)
            {
                pSquare[currentHumanRow][currentHumanCol - 1].setType(HUMAN);
            }
            else if(foundCrpCol > pSquare[currentHumanRow][currentHumanCol].getCol() && currentHumanCol < dim - 1)
            {
                pSquare[currentHumanRow][currentHumanCol + 1].setType(HUMAN);
            }
        }
    }
}