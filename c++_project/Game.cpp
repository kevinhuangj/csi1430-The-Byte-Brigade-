//
// Created by Lucas_Ulibarri2 on 4/17/2024.
//

#include "Game.h"



Game::Game() : g(SIZE, SIZE)
{
    initData();
}

void Game::generateGrassAndWater(const int numGrass, const int numWater)
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
        } while (pSquare[y][x].getType() != DIRT);

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
        } while (pSquare[y][x].getType() != DIRT);

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
                        weights[ny][nx] += 4;
                    }
                }
            }
        }

        // Set the tile type to WATER
        pSquare[y][x].setType(WATER);
    }
}

void Game::generateLoop()
{
    while(!g.getQuit())
    {
        generateGrassAndWater(10, 2);
        drawAndUpdate();    // Update the screen after each generation
        SDL_Delay(100);  // Delay for a while (e.g., 1 second) to see the changes
        if(g.kbhit())       // Break the loop if any key is pressed
        {
            g.getKey();     // Clear the key press event

            break;
        }
    }
}


void Game::initData()
{
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            pSquare[r][c].setRow(r);
            pSquare[r][c].setCol(c);
        }
    }
}

void Game::handleMouseClick()
{
    if(g.mouseClick())
    {
        point p = g.getMouseClick();
        cout << p.x/SIDE << " " << p.y/SIDE << endl;
        pSquare[p.y / SIDE][p.x / SIDE].click();

    }
}

void Game::handleKeyPress()
{
    if(g.kbhit())
    {
        char key = g.getKey();
        switch (key)
        {
        case 'r':
            music();
            generateLoop();
            break;
        case 'q':

            cout << "Q..." << endl;
                break;


            case 's':
                Mix_Chunk * munch = Mix_LoadWAV("c++_project/audio/Eat.wav");
                Mix_PlayChannel(-1, munch, 0);
                break;
        }
    }
}

void Game::drawAndUpdate()
{
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            pSquare[r][c].draw(g);
        }
    }
    drawGrid(g);
    g.update();
}

void Game::music() {

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);


    Mix_Music * music1 = Mix_LoadMUS("c++_project/audio/gamemus.wav");
    if(!music1){
        cout << "Error: No Music";
    }

    Mix_PlayMusic(music1,-1);
}

void Game::allstepsallcubes(){

    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            //pSquare[r][c].checkList();
        }
    }

}

void Game::run()
{
    while (!g.getQuit())
    {
        handleMouseClick();
        handleKeyPress();
        allstepsallcubes();
        drawAndUpdate();
    }
}