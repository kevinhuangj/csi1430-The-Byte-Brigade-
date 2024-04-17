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

void Game::overpopulationRule()
{
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
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            vector<Square*> cellNeighbors = checkNeighbors(r, c, data, dim);

            if(cellNeighbors.size() < 2 && data[r][c].getType() == CELL)
            {
                data[r][c].setType(DEAD);
                cout << "underpopulationRule" << endl;
            }
        }
    }
}

void Game::nextGenerationRule()
{
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            vector<Square*> cellNeighbors = checkNeighbors(r, c,  data, dim);
            int numNeighbors = cellNeighbors.size();

            if((numNeighbors == 2 || numNeighbors == 3) && data[r][c].getType() == CELL)
            {
                // Set the cells around it to EMPTY
                for (Square* neighbor : cellNeighbors)
                {
                    neighbor->setType(DEAD);
                }
            }
        }
    }
}

void Game::reproductionRule()
{
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            vector<Square*> cellNeighbors = checkNeighbors(r, c, data, dim);
            int numNeighbors = cellNeighbors.size();

            if(numNeighbors == 3 && data[r][c].getType() == DEAD)
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
            overpopulationRule();
            this_thread::sleep_for(std::chrono::seconds(1)); // Delay for 1 second

            underpopulationRule();
            this_thread::sleep_for(std::chrono::seconds(2)); // Delay for 1 second

            nextGenerationRule();
            this_thread::sleep_for(std::chrono::seconds(1)); // Delay for 1 second

            reproductionRule();
            this_thread::sleep_for(std::chrono::seconds(1)); // Delay for 1 second
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