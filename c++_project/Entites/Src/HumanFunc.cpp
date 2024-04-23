//
// Created by lulib on 4/23/2024.
//

#include "Entites/Headers/HumanFunc.h"

void generateCropAroundWater(Square (&pSquare)[dim][dim])
{
    // Loop through each tile in the grid
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            // If the current tile is a water tile
            if(pSquare[r][c].getType() == WATER)
            {
                bool hasCropAdjacent = false;
                // Check the neighboring tiles
                for(int dr = -1; dr <= 1; dr++)
                {
                    for(int dc = -1; dc <= 1; dc++)
                    {
                        // Calculate the coordinates of the neighboring tile
                        int nr = r + dr;
                        int nc = c + dc;
                        // If the neighboring tile is within the grid
                        if(nr >= 0 && nr < dim && nc >= 0 && nc < dim)
                        {
                            // If the neighboring tile is a crop tile
                            if(pSquare[nr][nc].getType() == CROPS)
                            {
                                hasCropAdjacent = true;
                                break;
                            }
                        }
                    }
                    if(hasCropAdjacent)
                    {
                        break; //Breaks to the outer loop
                    }
                }
                // If there's already a crop tile adjacent to the water tile, skip to the next water tile
                if(hasCropAdjacent)
                {
                    continue; //Continues to the next iteration of the outer loop
                }

                // Check the neighboring tiles again to find a dirt or grass tile
                for(int dr = -1; dr <= 1; dr++)
                {
                    for(int dc = -1; dc <= 1; dc++)
                    {
                        // Calculate the coordinates of the neighboring tile
                        int nr = r + dr;
                        int nc = c + dc;
                        // If the neighboring tile is within the grid
                        if(nr >= 0 && nr < dim && nc >= 0 && nc < dim)
                        {
                            // If the neighboring tile is either dirt or grass
                            if(pSquare[nr][nc].getType() == DIRT || pSquare[nr][nc].getType() == GRASS)
                            {
                                // Change the neighboring tile to a crop tile
                                pSquare[nr][nc].setType(CROPS);
                                // Return after changing the first suitable tile
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}
