/*
 * config.h
 *
 *  Created on: Apr 3, 2024
 *      Author: Kevin Huang
 *      Editted by Eric Escobar, Junshen_Huang, Lucas Ulibarri, Merrick Beinhower, Zhicheng Zhao
 */

#ifndef CONFIG_H_
#define CONFIG_H_

const int SIZE = 1000;    // size of the window
const int SIDE = 25;     // size of each square
const int dim = SIZE/SIDE;

enum objType {DIRT,CROPS, GRASS, HUMAN, MAMMOTH, TIGER, WATER}; /* */
const int numTypes = 7;





#endif /* CONFIG_H_ */
