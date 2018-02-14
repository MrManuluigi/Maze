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
 * @version     0.0.1 - 7-10-2017
 *
 * @todo the list of improvements suggested for the file.
 * @bug the list of known bugs.
 */

/**
 * @file main.c
 *
 * Main program of labyrinth
 *
 * All necessary references.
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#include <maze.h>
#include <Structure.h>

#define GREEN_BOLD      "\033[01;32m"
#define NORMAL          "\033[0;0m"
#define LIGHT_GRAY 		  "\033[01;34m"

/* Description the command line. eg? (How the launch the program.) */
#define USAGE "usage : %s text_file\n"

/**
 * Main method which permit to play the maze game
 * @params int argc, number of arguments
 * @params char* argv[], table of string, correspond to arguments
 * @return int, 0 if no errors occured
*/
int main(int argc, char* argv[]){
	Board mainBoard;
	char choixMenu;
	char* color;

	mainBoard.matrix = NULL;
	srand(time(NULL));

   	/* Display the command usage. */
   	if ((argc > 1) && (!strcasecmp("-h",argv[1]))) {
  		fprintf(stderr,USAGE,argv[0]);
      	return -1;
   	}

   	do {
   		if (mainBoard.matrix != NULL)
   			color = GREEN_BOLD;
   		else
   			color = NORMAL;

	   	do {
	   		system("clear");
	   		printf("%s\t\t _ __ ___   __ _ _______  ___ \n\t\t| '_ ` _ \\ / _` |_  / _ \\/ __|\n\t\t| | | | | | (_| |/ /  __/\\__ \\ \n\t\t|_| |_| |_|\\__,_/___\\___||___/\n\n",LIGHT_GRAY);
	   		printf("\t1- Créer un labyrinthe\n\t2- Charger un labyrinthe\n\t%s3- Jouer\n\t%sq- Quitter\n", color, LIGHT_GRAY);
	   		scanf("%c",&choixMenu);
			} while (choixMenu != '1' && choixMenu != '2' && choixMenu != '3' && choixMenu != 'q');

			switch (choixMenu) {
				case '1':
					mainBoard = createMaze();
					choixMenu = ' ';
					break;
				case '2':
					mainBoard = loadMaze();
					choixMenu = ' ';
					break;
				case '3':
					if (mainBoard.matrix != NULL) {
				   		system("clear");
						play(mainBoard);
					}
					else
						perror("labyrinthe non chargé\n");
					choixMenu = ' ';
					break;
				case 'q':
					quit(mainBoard);
					break;
				default:
					break;
			}

   	} while (choixMenu != 'q');
   return 0;
}
