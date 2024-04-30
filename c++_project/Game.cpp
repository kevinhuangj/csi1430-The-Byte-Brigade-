//
// Created by Lucas_Ulibarri on 4/17/2024.
//

#include "Game.h"

bool generateRan = false;

Game::Game() : g(SIZE, SIZE)
{
    initData();
}

void Game::generateLoop()
{
    while(!g.getQuit())
    {
        generateGrassAndWater(20, 1, pSquare);
        drawAndUpdate();    // Update the screen after each generation
        generateCropAroundWater(pSquare);
        drawAndUpdate();    // Update the screen after generating crops
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
        pSquare[p.y/SIDE][p.x/SIDE].click();
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
            if(generateRan == false)
            {
                generateLoop();
                generateRan = true;
            }
            break;
        case 'q':

            cout << "Q..." << endl;

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

void Game::run()
{
    while (!g.getQuit())
    {
        findCrops(pSquare);
        moveToCrop(pSquare);
        handleMouseClick();
        handleKeyPress();
        drawAndUpdate();
    }
}