//
// Created by Lucas_Ulibarri2 on 4/17/2024.
//

#ifndef CSI1430_THE_BYTE_BRIGADE_GAME_H
#define CSI1430_THE_BYTE_BRIGADE_GAME_H

#include "square.h"
#include "SDL_Plotter.h"
#include "config.h"
#include "grid.h"
#include <thread>
#include <mutex>
using namespace std;


class Game
{
private:
    SDL_Plotter g;
    Square data[dim][dim] ;
    int numNeighbors;
    mutex data_mutex;

public:
    Game();

    vector<Square*> checkNeighbors(int row, int col, Square data[][dim], int dim);

    void overpopulationRule();

    void underpopulationRule();

    void nextGenerationRule();

    void reproductionRule();

    void initData();

    void handleMouseClick();

    void handleKeyPress();

    void drawAndUpdate();

    void run();

};


#endif //CSI1430_THE_BYTE_BRIGADE_GAME_H
