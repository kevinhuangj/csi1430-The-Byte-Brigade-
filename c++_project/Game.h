//
// Created by Lucas_Ulibarri2 on 4/17/2024.
//

#ifndef CSI1430_THE_BYTE_BRIGADE_GAME_H
#define CSI1430_THE_BYTE_BRIGADE_GAME_H

#include "square.h"
#include "PLOTTER/SDL_Plotter.h"
#include "config.h"
#include <mutex>
#include "Entites/Headers/HumanFunc.h"
#include "C:\Users\merri\Documents\GitHub\csi1430-The-Byte-Brigade-\c++_project\Entites\Headers\TigerFunc.h"
#include "Entites/Headers/WorldGeneration.h"
#include "Entites/Headers/cropFunc.h"
#include <random>
using namespace std;

class Game
{
private:
    SDL_Plotter g;
    Square pSquare[dim][dim];
    mutex data_mutex;
    bool start = false;
    bool title = false;


public:
    Game();



    void generateLoop();

    void initData();

    void handleMouseClick();

    void handleKeyPress();

    void drawAndUpdate();

    void music();

    void titleScreen();

    void run();

};


#endif //CSI1430_THE_BYTE_BRIGADE_GAME_H
