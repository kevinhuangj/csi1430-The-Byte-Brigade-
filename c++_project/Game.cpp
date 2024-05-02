//
// Created by Lucas_Ulibarri on 4/17/2024.
//

#include "Game.h"

bool generateRan = false;

Game::Game() : g(SIZE, SIZE)
{
    initData();
}

// Makes the random game board every time it is ran.
void Game::generateLoop()
{
    while(!g.getQuit())
    {
        generateGrassAndWater(20, 1, pSquare);
        drawAndUpdate();    // Update the screen after each generation
        generateCropAroundWater(pSquare);
        drawAndUpdate();    // Update the screen after generating crops
        SDL_Delay(60);  // Delay for a while (e.g., 1 second) to see the changes
        if(g.kbhit())       // Break the loop if any key is pressed
        {
            g.getKey();     // Clear the key press event
            break;
        }
    }
}

// Lets each square know its position
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

// Measures the x and y of the mouse when I clicks and updates the square
void Game::handleMouseClick()
{
    if(g.mouseClick())
    {
        point p = g.getMouseClick();
        cout << p.x/SIDE << " " << p.y/SIDE << endl;
        pSquare[p.y/SIDE][p.x/SIDE].click();
    }
}

// loaded key with pause and unpause
void Game::handleKeyPress()
{
    if(g.kbhit())
    {
        char key = g.getKey();
        switch (key)
        {
        case 'r':
            if(paused == true){
                paused = false;
            }
            else{
                paused = true;
            }
            cout << 'r' << endl;
            break;

        }
    }
}

// Updates every sqaure
void Game::drawAndUpdate()
{
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            pSquare[r][c].draw(g);
        }
    }
    g.update();
}

// Music function
void Game::music() {

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);


    Mix_Music * music2 = Mix_LoadMUS("audio/5280419323445248.wav");
    if(!music2){
        cout << "Error: No Music";
    }

    Mix_PlayMusic(music2,-1);
}


//This goes in Game.h in the PRIVATE:

int mxr = Mix_Init(0);



//plots pixles in the shape of a button and when mouse is in the range the collors change and if click title screen ends
void Game::titleScreen() {
    point p = g.getMouseClick();
    int x=0, y=0;
    int n = 200;
    int gr = 0;
    if(!title){



        Mix_Music * music1 = Mix_LoadMUS("audio/4831631463022592.wav");
        Mix_PlayMusic(music1,-1);

        for(int r = 0; r < SIZE; r++)
        {
            for(int c = 0; c < SIZE; c++)
            {
                g.plotPixel(r, c, 25, 25, 25);
            }
        }


    }
    title = true;

    g.getMouseLocation(x,y);
    if(y>SIZE/2-150 and y<SIZE/2+150 and x>SIZE/2-200 and x<SIZE/2+200){
        if(p.x>0 and p.y>0){


            gr = 150;
            n = 0;
            music();
            start = true;
        }else{
            gr = 0;
        }

        n = 100;
    }else{
        n = 200;
    }

    for(int w = 0; w < 450; w++)
    {
        for(int h = 0; h < 350; h++)
        {
            g.plotPixel(w+SIZE/2-225, h+SIZE/2-175, 40, 40, 40);

        }
    }
    for(int w = 0; w < 400; w++)
    {
        for(int h = 0; h < 300; h++)
        {
            g.plotPixel(w+SIZE/2-200, h+SIZE/2-150, n*55/100, gr, 0);

        }
    }
    for(int w = 0; w < 25; w++)
    {
        for(int h = 0; h < 100; h++)
        {
            //G
            g.plotPixel(w+SIZE*9/24, h+SIZE/2-90, n, gr*200/150, 0);
            g.plotPixel(h+SIZE*9/24, w+SIZE/2-90, n, gr*200/150, 0);
            g.plotPixel(w+SIZE*9/24, h+SIZE/2-15, n, gr*200/150, 0);
            g.plotPixel(w+SIZE*9/24+75, h+SIZE/2-15, n, gr*200/150, 0);
            g.plotPixel(h+SIZE*9/24, w+SIZE/2+60, n, gr*200/150, 0);
            g.plotPixel(h+SIZE*9/24+50, w+SIZE/2-15, n, gr*200/150, 0);
            //O
            g.plotPixel(w+SIZE*15/24-100, h+SIZE/2-90, n, gr*200/150, 0);
            g.plotPixel(h+SIZE*15/24-100, w+SIZE/2-90, n, gr*200/150, 0);
            g.plotPixel(w+SIZE*15/24-25, h+SIZE/2-90, n, gr*200/150, 0);
            g.plotPixel(w+SIZE*15/24-100, h+SIZE/2-15, n, gr*200/150, 0);
            g.plotPixel(w+SIZE*15/24-25, h+SIZE/2-15, n, gr*200/150, 0);
            g.plotPixel(h+SIZE*15/24-100, w+SIZE/2+60, n, gr*200/150, 0);

        }
    }
    g.update();


    if(start){
        for (int i = 4; i > 0; i--) {
            for (int r = 0; r < SIZE; r += i) {
                for (int c = 0; c < SIZE; c += i) {
                    g.plotPixel(r, c, 128, 64, 0);
                }

                g.update();

            }

        for (int r = SIZE+1; r >= 0; r -= i) {
            for (int c = SIZE+1; c >= 0; c -= i) {
                g.plotPixel(r, c, 128, 64, 0);
            }

            g.update();

        }
    }

}

}

//function for the general running of the game
void Game::run()
{
    while (!g.getQuit()) {


        if (!start) {
            titleScreen();
        }
        //start is trigered when the title screen is finished
        if (start) {
            if(generateRan == false)
            {

                generateLoop();
                generateRan = true;
            }else{
                handleKeyPress();
                handleMouseClick();
                //when 'r' is pressed the pause is undone.
                if(!paused) {
                    int choser = rand() % 3 + 1;
                    if (choser >= 2) {
                        findPeeps(pSquare);
                        moveToPeep(pSquare);
                    }
                    if (choser == 1) {
                        findCrops(pSquare);
                        moveToCrop(pSquare);
                    }
                    findGrass(pSquare);
                    moveToGrass(pSquare);



                }
                drawAndUpdate();
            }
        }
    }
}


