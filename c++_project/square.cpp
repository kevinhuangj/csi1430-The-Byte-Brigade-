/*
 * square.cpp
 *
 *  Created on: Apr 3, 2024
 *      Author: Kevin Huang
 *      Editted by Eric_Escobar, Junshen_Huang, Lucas_Ulibarri, Merrick_Beinhower, Zhicheng_Zhao
 */

#include "square.h"

Square::Square() // <-- Constructor
{
    row;
    col;
    type;
    numNeighborN;
    numNeighborS;
    numNeighborE;
    numNeighborW;

    //color brown = color(128, 64, 0);
    _color = color(128, 64, 0);
}

Square::Square(int numNeighbors, objType type)
{
    row = 0;
    col = 0;
    numNeighbors = 0;
    type = DIRT;
    _color = color(128, 64, 0);
}

void Square::draw(SDL_Plotter& g)
{
    for(int r = 0; r < SIDE; r++)
    {
        for(int c = 0; c < SIDE; c++)
        {
            g.plotPixel(c + SIDE * col, r + SIDE * row, _color);
        }
    }
}

void Square::setRow(int r)
{
    row = r;
}

void Square::setCol(int c)
{
    col = c;
}

int Square::getRow()
{
    return row;
}

int Square::getCol()
{
    return col;
}

//getter of type
objType Square::getType()
{
    return type;
}



//setter of type
objType Square::setType(objType t)
{
    type = t;
    switch (type)
    {
        case DIRT:
            _color = color(36, 29, 12); // brown
            break;
        case CROPS:
            _color = color(100, 200, 200); // dull yellow
            break;
        case GRASS:
            _color = color(4, rand()%(145-120)+120, 9); // Dark green
            break;
        case HUMAN:
            _color = color(rand()%(227-205)+205, rand()%(221-200)+200, rand()%(211-200)+200); // bright tan

            break;
        case MAMMOTH:
            _color = color(183, 114, 196); // pinkish
            break;
        case TIGER:
            _color = color(255, 165, 0); // orange
            break;
        case WATER:
            _color = color(0, 0, rand()%(230-200)+200); // blue
    }
    return type;
}

void Square::click()
{
    type = static_cast<objType>(static_cast<int>(type + 1) % numTypes);
    switch (type)
    {
        case DIRT:
            _color = color(36, 29, 12); // brown
            break;
        case CROPS:
            _color = color(100, 200, 200); // dull yellow
            break;
        case GRASS:
            _color = color(4, rand()%(145-140)+140, 9); // Dark green
            break;
        case HUMAN: {
            _color = color(rand()%(227-205)+205, rand()%(221-200)+200, rand()%(211-200)+200); // bright tan
            Mix_Chunk * soundHuman = Mix_LoadWAV("c++_project/audio/Human.wav");
            Mix_PlayChannel(-1, soundHuman, 0);
            break;
        }
        case MAMMOTH: {
            _color = color(183, 114, 196); // pinkish
            Mix_Chunk *soundMamoth = Mix_LoadWAV(
                    "c++_project/audio/Mamoth.wav");
            Mix_PlayChannel(-1, soundMamoth, 0);
            break;
        }
        case TIGER: {
            _color = color(255, 165, 0); // orange
            Mix_Chunk * soundTiger = Mix_LoadWAV("c++_project/audio/Tiger.wav");
            Mix_PlayChannel(-1, soundTiger, 0);
            break;
        }
        case WATER:
            _color = color(0, 0, rand()%(230-225)+225); // blue`
    }
}

int Square::getNumNeighbors() const
{

    return 2;
}

void Square::setNumNeighbors(int num)
{

}


