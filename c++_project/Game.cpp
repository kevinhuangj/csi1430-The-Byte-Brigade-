//
// Created by Lucas_Ulibarri2 on 4/17/2024.
//

#include "Game.h"

Game::Game() : g(SIZE, SIZE)
{
    initData();
}

void Game::generateGrassAndWater(int numGrass, int numWater)
{
    int dirtcount = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, dim - 1);

    // Create a 2D array to store weights for each tile
    std::vector<std::vector<int>> weights(dim, std::vector<int>(dim, 1));

    // Count the number of dirt tiles
    for(int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            if(data[r][c].getType() == DIRT)
            {
                dirtcount++;
            }
        }
    }
    if(dirtcount < numGrass + numWater)
    {
        // Not enough dirt tiles to place grass and water
        return;
    }

    // Place grass and water
    for (int i = 0; i < numGrass; i++)
        {
        int x, y;
        do
        {
            x = dis(gen);
            y = dis(gen);
        } while (data[y][x].getType() != DIRT);

        // Increase weights for neighboring tiles
        for (int dx = -1; dx <= 1; dx++)
            {
            for (int dy = -1; dy <= 1; dy++)
            {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < dim && ny >= 0 && ny < dim)
                {
                    if (data[ny][nx].getType() == GRASS)
                    {
                        weights[ny][nx] += 1; // Increase weight for grass tiles
                    }
                }
            }
        }

        data[y][x].setType(GRASS);
    }

    for (int i = 0; i < numWater; i++)
    {
        int x, y;
        do
        {
            x = dis(gen);
            y = dis(gen);
        } while (data[y][x].getType() != DIRT);

        // Increase weights for neighboring tiles
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < dim && ny >= 0 && ny < dim)
                {
                    if (data[ny][nx].getType() == WATER)
                    {
                        weights[ny][nx] += 4; // Increase weight for water tiles
                    }
                }
            }
        }

        data[y][x].setType(WATER);
    }
}


void Game::initData()
{
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            data[r][c].setRow(r);
            data[r][c].setCol(c);
        }
    }
}

void Game::handleMouseClick()
{
    if(g.mouseClick())
    {
        point p = g.getMouseClick();
        cout << p.x/SIDE << " " << p.y/SIDE << endl;
        data[p.y/SIDE][p.x/SIDE].click();
    }
}

void Game::handleKeyPress()
{
    if(g.kbhit())
    {
        char key = g.getKey();
        if(key == 'r')
        {
            initData();

            for(int i = 0; i < 10; i++)
            {
                generateGrassAndWater(10, 1);
            }
        }
    }
}

void Game::drawAndUpdate()
{
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            data[r][c].draw(g);
        }
    }
    drawGrid(g);
    g.update();
}

void Game::run()
{
    while (!g.getQuit())
    {
        handleMouseClick();
        handleKeyPress();
        drawAndUpdate();
    }
}