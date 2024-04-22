//
// Created by Lucas_Ulibarri2 on 4/17/2024.
//

#include "Game.h"

Game::Game() : g(SIZE, SIZE)
{
    initData();
    human.setPos(0, 0);
    mammoth.setPos(0, 1);
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