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
 * @author Luigi Dechanteloup <luigi.dechanteloup@ecole.ensicaen.fr>
 * @version 0.0.1 / 7-10-2017
 */

/**
 * @file maze.h
 * Contains all methods need for the maze game
 */

#ifndef __MAZE_H
#define __MAZE_H

#include <Structure.h>

/**
 * Dynamic allocation of the 2-D board
 * @params int rows, the numbers of rows
 * @params int cols, the count of columns
 * @return int** correspond to the 2-D empty board of the maze
*/
int ** mallocMatrix (int rows, int cols);

/**
 * Generate the walls in odd cell
 * @params int rows, the number of rows
 * @params int cols, the count of columns
 * @return int**, correspond to the modified board
*/
int** generateBoard (int rows, int cols);

/**
 * Break the walls to open a path, call bonus methods at the end
 * @params Board, the structure of the maze
 * @return int, 0 if no errors
*/
int generateMaze (Board maze);

/**
 * Generate all bonus and penalty over the maze, random amount between 0 and number of normal cell divided by 6, to avoid a spamming of bonus.
 * @params Board, correspond to the current maze
 * @return int, 0 if no errors occured
*/
int generateBonus (Board maze);

/**
 * Method call to break walls for the generateMaze method, it change the values in cells of region
 * @params Board maze, correspond to the current maze
 * @params int toChange, correspond to the value we want to change
 * @params int changeVal, the new value to assign to the cell
 * @return int, 0 if no errors occured
*/
int changeValByOther (Board maze, int toChange, int changeVal);

/**
 * Save the maze in file.cfg, in ./plan/ directory
 * @params Board maze, correspond to the current maze
 * @return int, 0 if no errors occured
*/
int saveMaze (Board maze);

/**
 * Display the maze on the terminal
 * @params Board maze, the current maze to display
 * @return int, 0 if no errors occured
*/
int displayMaze (Board maze);


/**
 * The methods which manage all movement of the player
 * @params Board maze, the current maze
 * @return int, 0 if no errors occured
*/
int move (Board maze);

/**
 * Read the file which contains best score
 * @params Board maze, the current maze
 * @return Score*, correspond to a table of the Score structure
*/
/*Score* readScore (Board maze);*/

/**
 * Save the player score if is better than the 10th score
 * @params Board maze, current maze
 * @params Score* tabScore, correspond to the new table of score
 * @return int, 0 if no errors occured
*/
int saveScore (Board maze, int score);

/**
 * Methods which free the board before leaving
 * @params Board maze, correspond to the current maze
 * @return int, 0 if no errors occured
*/
int quit (Board maze);

/**
 * Initialize the maze before call move method
 * @params Board maze, current maze
 * @return int, 0 if no errors occured
*/
int play (Board maze);

/**
 * Method which load a chosen maze in ./plan/ directory
 * @return Board, correspond to the new current maze
*/
Board loadMaze ();

/**
 * Method which create a new maze
 * @return Board, correspond to the new current maze
*/
Board createMaze ();


/**
 * Count the number of file in directory
 * @return int, correspond to the number of item in directory
*/
int nbFile ();

/**
 * Methods which wait for a amount of seconds
 * @params unsigned int secs, amount of seconds
*/
void waitFor (unsigned int secs);

/**
 * Concat 2 strings and return the result
 * @params const char* s1, the 1st string (const to not change it)
 * @params const char* s2, the 2nd string (const to not change it)
 * @return char*, correspond to the concat of these 2 strings
*/
char* concat (const char* s1, const char* s2);


#endif
