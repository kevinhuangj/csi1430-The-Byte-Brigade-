//
// Created by lulib on 4/23/2024.
//

#include "Entites/Headers/HumanFunc.h"

//Big O Notation O(n^2)
void findCrops(Square (&pSquare)[dim][dim])
{
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            if(pSquare[r][c].getType() == HUMAN)
            {
                bool foundCrop = false;
                for(int dr = -1; dr <= 1; dr++)
                {
                    for(int dc = -1; dc <= 1; dc++)
                    {
                        if(r+dr >= 0 && r+dr < dim && c+dc >= 0 && c+dc < dim && pSquare[r+dr][c+dc].getType() == CROPS)
                        {
                            foundCrop = true;
                            pSquare[r+dr][c+dc].setType(DIRT); // Change CROPS to DIRT
                            break;
                        }
                    }
                    if(foundCrop) break;
                }
                if(!foundCrop) {
                    for(int dr = -2; dr <= 2; dr++)
                    {
                        for(int dc = -2; dc <= 2; dc++)
                        {
                            if(r+dr >= 0 && r+dr < dim && c+dc >= 0 && c+dc < dim && pSquare[r+dr][c+dc].getType() == CROPS)
                            {
                                foundCrop = true;
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