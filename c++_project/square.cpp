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
    row = 0;
    col = 0;
    type = DIRT;
    numNeighbors = 0;
    //color brown = color(128, 64, 0);
    _color = color(128, 64, 0);
    wasCrop = false;
}

Square::Square(int numNeighbors, objType type)
{
    row = 0;
    col = 0;
    numNeighbors = 0;
    type = DIRT;
    _color = color(128, 64, 0);
    wasCrop = false;
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

bool Square::getWasCrop() const
{
    return wasCrop;
}

bool Square::setWasCrop(bool crop)
{
    wasCrop = crop;
    return wasCrop;
}

int Square::getRow() const
{
    return row;
}

int Square::getCol() const
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
    this->type = t;
    switch (type)
    {
        case DIRT:
            _color = color(128, 64, 0); // brown
            break;
        case CROPS:
            _color = color(200, 200, 100); // dull yellow
            break;
        case GRASS:
            _color = color(4, rand()%(40)+100, 9); // Dark green
            break;
        case HUMAN: {
            _color = color(185, 180, 180); // bright tan
            Mix_Chunk * soundHuman = Mix_LoadWAV("audio/human_voice_male_grunt_grumble_caveman_001.wav");
            Mix_PlayChannel(-1, soundHuman, 0);
            break;
        }
        case MAMMOTH: {
            _color = color(183, 114, 196); // pinkish
            Mix_Chunk *soundMamoth = Mix_LoadWAV(
                    "audio/elephant-trumpets-growls-6047.wav");
            Mix_PlayChannel(-1, soundMamoth, 0);
            break;
        }
        case TIGER: {
            _color = color(255, 165, 0); // orange
            Mix_Chunk * soundTiger = Mix_LoadWAV("audio/mixkit-angry-wild-cat-roar-89.wav");
            Mix_PlayChannel(-1, soundTiger, 0);
            break;
        }
        case WATER:
            _color = color(0, 0, rand()%(40)+200); // blue`


    }
    return type;
}

void Square::click()
{
    type = static_cast<objType>(static_cast<int>(type + 1) % numTypes);
    switch (type)
    {
        case DIRT:
            _color = color(128, 64, 0); // brown
            break;
        case CROPS:
            _color = color(200, 200, 100); // dull yellow
            break;
        case GRASS:
            _color = color(4, rand()%(40)+100, 9); // Dark green
            break;
        case HUMAN: {
            _color = color(185, 180, 180); // bright tan
            Mix_Chunk * soundHuman = Mix_LoadWAV("audio/human_voice_male_grunt_grumble_caveman_001.wav");
            Mix_PlayChannel(-1, soundHuman, 0);
            break;
        }
        case MAMMOTH: {
            _color = color(183, 114, 196); // pinkish
            Mix_Chunk *soundMamoth = Mix_LoadWAV(
                    "audio/elephant-trumpets-growls-6047.wav");
            Mix_PlayChannel(-1, soundMamoth, 0);
            break;
        }
        case TIGER: {
            _color = color(255, 165, 0); // orange
            Mix_Chunk * soundTiger = Mix_LoadWAV("audio/mixkit-angry-wild-cat-roar-89.wav");
            Mix_PlayChannel(-1, soundTiger, 0);
            break;
        }
        case WATER:
            _color = color(0, 0, rand()%(40)+200); // blue`

    }
}

int Square::getNumNeighbors() const
{
    return numNeighbors;
}

void Square::setNumNeighbors(int num)
{
    numNeighbors = num;
}


