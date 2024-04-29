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
            findCrops(pSquare);
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

void Game::music() {

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);


    Mix_Music * music2 = Mix_LoadMUS("audio/5280419323445248.wav");
    if(!music2){
        cout << "Error: No Music";
    }

    Mix_PlayMusic(music2,-1);
}

void Game::titleScreen() {
    point p = g.getMouseClick();
    int x=0, y=0;
    if(!title){



        Mix_Music * music1 = Mix_LoadMUS("audio/titleMusic.wav");
        Mix_PlayMusic(music1,-1);

        for(int r = 0; r < SIZE; r++)
        {
            for(int c = 0; c < SIZE; c++)
            {
                g.plotPixel(r, c, 100, 100, 100);
            }
        }


    }
    title = true;
    int gr = 0; int n = 200;
    g.getMouseLocation(x,y);
    if(y>SIZE/2-50 and y<SIZE/2+50 and x>SIZE/2-100 and x<SIZE/2+100){
        if(p.x>0 and p.y>0){
            g.clear();
            music();
            start = true;
        }
        gr = 200;
        n = 0;
    }else{
        n = 200;
        gr = 0;
    }


    for(int w = 0; w < 200; w++)
    {
        for(int h = 0; h < 100; h++)
        {
            g.plotPixel(w+SIZE/2-100, h+SIZE/2-50, n, gr, 0);
        }
    }
    g.update();


}


void Game::run()
{
    while (!g.getQuit()) {
        handleKeyPress();

        if (!start) {
            titleScreen();
        }
        if (start) {
            handleMouseClick();
            drawAndUpdate();
        }
    }
}