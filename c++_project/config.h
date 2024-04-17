/*
 * config.h
 *
 *  Created on: Apr 3, 2024
 *      Author: Kevin Huang
 *      Editted by Eric Escobar, Junshen_Huang, Lucas Ulibarri, Merrick Beinhower, Zhicheng Zhao
 */

#ifndef CONFIG_H_
#define CONFIG_H_

const int SIZE = 500;
const int SIDE = 25;
const int dim = SIZE/SIDE;

enum objType {DEAD, CELL, GRASS, RABBIT, FOX}; /* */
const int numTypes = 5;





#endif /* CONFIG_H_ */
