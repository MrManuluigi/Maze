/* -*- c-basic-offset: 3 -*-
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

/**
 * @author Luigi 
 * @version 0.0.1 / 7-10-2017
 */

/**
 * @file Structure.h
 * Contains all structure need for the maze game
 */

#ifndef __STRUCTURE_H
#define __STRUCTURE_H

/**
 * Define the structure of the board
*/
typedef struct Board {
	int** matrix;
	int rows;
	int cols;
	char* name;
}Board;

/**
 * Define the structure of score
*/
typedef struct Score {
	char* playerName;
	int score;
}Score;

#endif
