//
// Created by lulib on 4/23/2024.
//
#include "Entites/Headers/WorldGeneration.h"

bool wasCrop[dim][dim] = {false};

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
    int dirtCount = 0;

    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    // This is the random number generator that will be used to generate random numbers.
    // dis is "Distribution" which is used to generate random numbers within a range. dis(min, max).
    uniform_int_distribution<> dis(0, dim - 1);

    // Create a 2D Vector to store weights for each tile
    vector<vector<int>> weights(dim, vector<int>(dim, 1));

    // Count the number of dirt tiles or the game will crash when trying to place more water or
    // grass tiles than there is dirt.
    for(int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            // If the tile is of type DIRT, increment the dirtCount.
            if(pSquare[r][c].getType() == DIRT)
            {
                dirtCount++;
            }
        }
    }

    // If there are not enough dirt tiles to place the required number of grass and water tiles,
    // return without making any changes. If not, the game will crash.
    if(dirtCount < numGrass + numWater)
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
            // call back to dis to generate a random number for x and y
            x = dis(gen);
            y = dis(gen);
            // we count the number of attempts, if it exceeds the max attempts,
            // we break out of the loop. Because if we dont, the game will crash.
            attempts++;
        } while (pSquare[y][x].getType() != DIRT && attempts < MAX_ATTEMPTS);

        // Increase weights for neighboring tiles.
        // that way, we can increase the chances of placing grass tiles near each other.
        // so that the grass tiles are not as randomly scattered.
        // "dx" and "dy" are the x and y coordinates of the tiles around the current tile.
        // that way we can check the tiles around the current tile.
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)//We iterate through the 8 neighboring tiles of the created tile.
            {
                //we decided "nx" and "ny" to be "neighbor x" and "neighbor y".
                // FIXME: A possible refactor would be to rename them.
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

        // When all said and done, we set the tile type to GRASS
        pSquare[y][x].setType(GRASS);
    }

    // Place water tiles
    for (int i = 0; i < numWater; i++)
    {
        // we define a seperate x and y for the water tiles. That way there is no overlap
        // between the grass and water tiles.
        int x, y;
        // Find a dirt tile
        do
        {
            x = dis(gen);
            y = dis(gen);
            attempts++;
        } while (pSquare[y][x].getType() != DIRT && attempts < MAX_ATTEMPTS);

        // Increase weights for neighboring tiles
        // FIXME: we could refactor the names of dx and dy to be more descriptive.
        // FIXME: to something like "neighbor x" and "neighbor y"?
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
    // Couldn't find a way to get this interation into function form to reduce repetition.
    // But, we kind of need this repetition to check for different conditions throughout the grid.
    // Also, it's nice that we still only have a Big O Notation of O(n^2)...we think.
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            // If the current tile is a water tile
            if(pSquare[r][c].getType() == WATER)
            {
                bool hasCropAdjacent = false;
                // Check the neighboring tiles to see if there's already a crop tile
                // adjacent to the water tile
                //FIXME: Why "dr" and "dc"? We could refactor these to be more descriptive.
                // maybe to "delta row" and "delta column"?
                for(int dr = -1; dr <= 1; dr++)
                {
                    for(int dc = -1; dc <= 1; dc++)
                    {
                        // Calculate the coordinates of the neighboring tile
                        int nr = r + dr;
                        int nc = c + dc;
                        // If the neighboring tile is within the grid
                        // Added more spacing to make it easier to read.
                        if(nr >= 0  &&  nr < dim  &&  nc >= 0  &&  nc < dim)
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
                        break; //Breaks to the outer loop: for(int c = 0; c < dim; c++)
                               // Why? Because we don't need to check the other neighboring tiles.
                               // If we did, it would result in more unnecessary crop tiles.
                    }
                }
                // If there's already a crop tile adjacent to the water tile, skip to the next water tile
                if(hasCropAdjacent)
                {
                    continue; //Continues to the next iteration of the outer loop
                }

                // Check the neighboring tiles again to find a dirt or grass tile
                // We need to find a suitable tile to place a crop tile. Can't quite figure out
                // how to randomize this. But, for now we just don't want the CROPS tiles to be
                // placed over water or other CROPS tiles.
                for(int dr = -1; dr <= 1; dr++)
                {
                    for(int dc = -1; dc <= 1; dc++)
                    {
                        // Calculate the coordinates of the neighboring tile
                        // FIXME: refactor names. Maybe to "neighbor row" and "neighbor column"?
                        int nr = r + dr;
                        int nc = c + dc;
                        // If the neighboring tile is within the grid (that way there's no out of bounds errors)
                        // Added more spacing to make it easier to read.
                        if(nr >= 0  &&  nr < dim  &&  nc >= 0  &&  nc < dim)
                        {
                            // If the neighboring tile is either dirt or grass
                            if(pSquare[nr][nc].getType() == DIRT || pSquare[nr][nc].getType() == GRASS)
                            {
                                // Change the neighboring tile to a crop tile
                                pSquare[nr][nc].setType(CROPS);
                                pSquare[nr][nc].setWasCrop(true);
                                wasCrop[nr][nc] = true; // Store the coordinates
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}

void cropRegeneration(Square (&pSquare)[dim][dim])
{
    // Iterate over the entire grid to check for cells that need to be regenerated
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            // If the cell was once a crop and is currently grass
            if(wasCrop[r][c] && pSquare[r][c].getType() == GRASS)
            {
                // Change the cell type to crops
                pSquare[r][c].setType(CROPS);
                // Print a message indicating the coordinates of the regenerated crop
                std::cout << "Crop regenerated at coordinates: (" << r << ", " << c << ")" << std::endl;
            }
        }
    }
}