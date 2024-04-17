//
// Created by Lucas_Ulibarri2 on 4/17/2024.
//

#include "Game.h"

#include "Game.h"

Game::Game() : g(SIZE, SIZE)
{
    initData();
}

vector<Square*> Game::checkNeighbors(int row, int col, Square data[][dim], int dim)
{
    vector<Square*> cellNeighbors;

    if (data[row][col].getType() != CELL)
    {
        return cellNeighbors;
    }

    int directions[8][2] = {{-1, 0},
                            {-1, 1},
                            {0, 1},
                            {1, 1},
                            {1, 0},
                            {1, -1},
                            {0, -1},
                            {-1, -1}};

    for (int i = 0; i < 8; i++)
    {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        if (newRow >= 0 && newRow < dim && newCol >= 0 && newCol < dim && data[newRow][newCol].getType() == CELL)
        {
            cellNeighbors.push_back(&data[newRow][newCol]);
        }
    }

    return cellNeighbors;
}

void getNeighbors()
{

}

void Game::overpopulationRule()
{
    lock_guard<mutex> lock(data_mutex);
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            vector<Square*> cellNeighbors = checkNeighbors(r, c, data, dim);

            if (cellNeighbors.size() > 3)
            {
                data[r][c].setType(DEAD);
                cout << "Overpopulation" << endl;
            }
        }
    }
}

void Game::underpopulationRule()
{
    lock_guard<mutex> lock(data_mutex);
    // First loop to update numNeighbors for each Square
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            vector<Square*> cellNeighbors = checkNeighbors(r, c, data, dim);
            data[r][c].setNumNeighbors(cellNeighbors.size());
        }
    }

    // Second loop to apply the underpopulation rule
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            if(data[r][c].getNumNeighbors() < 2)
            {
                data[r][c].setType(DEAD);
                cout << "underpopulationRule" << endl;
            }
        }
    }
}

void Game::nextGenerationRule()
{
    lock_guard<mutex> lock(data_mutex);
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            vector<Square*> cellNeighbors = checkNeighbors(r, c,  data, dim);
            int numNeighbors = cellNeighbors.size();

            if((numNeighbors == 2 || numNeighbors == 3) && data[r][c].getType() == CELL)
            {
                data[r][c].setType(CELL);
            }
        }
    }
}

void Game::reproductionRule()
{
    lock_guard<mutex> lock(data_mutex);
    // First loop to update numNeighbors for each Square
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            vector<Square*> cellNeighbors = checkNeighbors(r, c, data, dim);
            data[r][c].setNumNeighbors(cellNeighbors.size());
        }
    }

    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            vector<Square*> cellNeighbors = checkNeighbors(r, c, data, dim);
            int numNeighbors = cellNeighbors.size();

            if(numNeighbors == 3)
            {
                data[r][c].setType(CELL);
                cout << "Reproduction" << endl;
            }
        }
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
            thread t1(&Game::underpopulationRule, this);
            thread t2(&Game::nextGenerationRule, this);
            thread t3(&Game::overpopulationRule, this);
            thread t4(&Game::reproductionRule, this);

            t1.join();
            t2.join();
            t3.join();
            t4.join();
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