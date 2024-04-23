//
// Created by lulib on 4/23/2024.
//
#include "Entites/Headers/WorldGeneration.h"

void generateGrassAndWater(int numGrass, int numWater, Square (&pSquare)[dim][dim])
{
    /*
     * References:
     * - Voronoi Diagram: https://mathworld.wolfram.com/VoronoiDiagram.html
     * - Elementary Cellular Automaton: https://mathworld.wolfram.com/ElementaryCellularAutomaton.html
     * - Weighted Random Sampling: https://mathworld.wolfram.com/Sampling.html
     * - Procedural Generation Tutorial (YouTube): https://www.youtube.com/watch?v=slTEz6555Ts&pp=ygUrQ2VsbHVsYXIgQXV0b21hdGEgZm9yIFByb2NlZHVyYWwgR2VuZXJhdGlvbg%3D%3D
     * - Voronoi Diagrams for Procedural Generation (YouTube): https://www.youtube.com/watch?v=I6Fen2Ac-1U&pp=ygU0Vm9yb25vaSBEaWFncmFtcyBmb3IgUHJvY2VkdXJhbCBHZW5lcmF0aW9uIENHQWNhZGVteQ%3D%3D
     * - Diamond Square | Procedural Generation | Game Development Tutorial (YouTube): https://www.youtube.com/watch?v=1HV8GbFnCik&pp=ygU0Vm9yb25vaSBEaWFncmFtcyBmb3IgUHJvY2VkdXJhbCBHZW5lcmF0aW9uIENHQWNhZGVteQ%3D%3D
     * - Why use <random> instead of rand()?: https://stackoverflow.com/questions/52869166/why-is-the-use-of-rand-considered-bad
     * - C++ random number generation: https://en.cppreference.com/w/cpp/numeric/random
     */

    const int MAX_ATTEMPTS = 1000;
    // Maximum number of attempts to find a suitable tile
    int attempts = 0;
    // Initialize the number of attempts

    // Initialize the count of dirt tiles
    int dirtcount = 0;

    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, dim - 1);

    // Create a 2D array to store weights for each tile
    vector<vector<int>> weights(dim, vector<int>(dim, 1));

    // Count the number of dirt tiles
    for(int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            // If the tile is of type DIRT, increment the dirtcount
            if(pSquare[r][c].getType() == DIRT)
            {
                dirtcount++;
            }
        }
    }

    // If there are not enough dirt tiles to place the required number of grass and water tiles, return without making any changes
    if(dirtcount < numGrass + numWater)
    {
        return;
    }

    // Place grass tiles
    for (int i = 0; i < numGrass; i++)
    {
        int x, y;
        // Find a dirt tile
        do
        {
            x = dis(gen);
            y = dis(gen);
            attempts++;
        } while (pSquare[y][x].getType() != DIRT && attempts < MAX_ATTEMPTS);

        // Increase weights for neighboring tiles
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                int nx = x + dx;
                int ny = y + dy;
                // If the neighboring tile is within the map and is of type GRASS, increase its weight
                if (nx >= 0 && nx < dim && ny >= 0 && ny < dim)
                {
                    if (pSquare[ny][nx].getType() == GRASS)
                    {
                        weights[ny][nx] += 1;
                    }
                }
            }
        }

        // Set the tile type to GRASS
        pSquare[y][x].setType(GRASS);
    }

    // Place water tiles
    for (int i = 0; i < numWater; i++)
    {
        int x, y;
        // Find a dirt tile
        do
        {
            x = dis(gen);
            y = dis(gen);
            attempts++;
        } while (pSquare[y][x].getType() != DIRT && attempts < MAX_ATTEMPTS);

        // Increase weights for neighboring tiles
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                int nx = x + dx;
                int ny = y + dy;
                // If the neighboring tile is within the map and is of type WATER, increase its weight
                if (nx >= 0 && nx < dim && ny >= 0 && ny < dim)
                {
                    if (pSquare[ny][nx].getType() == WATER)
                    {
                        weights[ny][nx] += 16; // Increase weight by a larger amount
                    }
                }
            }
        }

        // Set the tile type to WATER
        pSquare[y][x].setType(WATER);

        // Use weighted random sampling to select the next water tile
        int wx, wy;
        do
        {
            wx = dis(gen);
            wy = dis(gen);
        } while (weights[wy][wx] == 0); // Select a tile with non-zero weight

        x = wx;
        y = wy;
    }
}

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