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
 * @version     0.0.1 - 7-10-2017
 *
 * @todo
 * @bug
 */

/**
 * @file maze.c
 * Contains all methods needed for the maze game
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <dirent.h>

#include <maze.h>

#define GREEN_BOLD      "\033[01;32m"
#define NORMAL          "\033[0;0m"
#define LIGHT_GRAY 	"\033[01;34m"
#define RED 		"\033[01;31m"
#define YELLOW	 	"\033[01;33m"

/**
 * Dynamic allocation of the 2-D board
 * @params int rows, the numbers of rows
 * @params int cols, the count of columns
 * @return int** correspond to the 2-D empty board of the maze
 */
int ** mallocMatrix(int rows, int cols) {
   int comptRows = 0;
   int** matrix = NULL;

   if ((matrix = (int**)malloc(rows*sizeof(int*))) == NULL) {
      return NULL;
   }
   if ((matrix[0] = (int*)malloc(rows*(cols)*sizeof(int))) == NULL) {
      free(matrix);
      return NULL;
   }
   for (comptRows = 1; comptRows < rows; comptRows++) {
      matrix[comptRows] = matrix[0]+((cols)*comptRows);
   }
   return matrix;
}

/**
 * Generate the walls in odd cell
 * @params int rows, the number of rows
 * @params int cols, the count of columns
 * @return int**, correspond to the modified board
 */
int** generateBoard(int rows, int cols) {
   int comptRows = 0;
   int comptCols = 0;
   int comptCell = 1;
   int** matrix = NULL;

   matrix = mallocMatrix(rows, cols);

   for (comptRows=0; comptRows <rows; comptRows++) {
      for (comptCols = 0; comptCols < cols; comptCols++) {
	 if ((comptRows%2 == 0)||(comptCols%2 == 0)) {
	    matrix[comptRows][comptCols] = -1;
	 }
	 else {
	    matrix[comptRows][comptCols] = comptCell;
	    comptCell++;
	 }
      }
   }
   return matrix;
}

/**
 * Break the walls to open a path, call bonus methods at the end
 * @params Board, the structure of the maze
 * @return int, 0 if no errors
 */
int generateMaze(Board maze) {
   int compt =0;
   int nbMax ;
   int randPosL;
   int randPosC;
   int toChange;
   int changeVal;

   nbMax = ((maze.rows-1)/2) * ((maze.cols-1)/2);

   maze.matrix[1][0]=-2;
   maze.matrix[maze.rows-2][maze.cols-1]=0;

   /*srand(time(NULL));*/
   while (compt != nbMax-1) {
      do {
	 randPosL = rand()%(maze.rows-2)+1;
	 randPosC = rand()%(maze.cols-2)+1;
      } while ((randPosL%2 == 0 && randPosC%2 ==0) || (randPosL%2 == 1 && randPosC%2 == 1));

      if (randPosL%2 == 1 && randPosC%2 == 0) { /*odd cell -> horizontal cells*/
	 if (maze.matrix[randPosL][(randPosC-1)] != maze.matrix[randPosL][(randPosC+1)]) {
	    toChange = maze.matrix[randPosL][(randPosC+1)];
	    changeVal = maze.matrix[randPosL][(randPosC-1)];
	    maze.matrix[randPosL][randPosC] = toChange;
	    changeValByOther(maze, toChange, changeVal);
	    compt++;
	 }
      }
      else if (randPosL%2 == 0 && randPosC%2 == 1) { /*even cell -> vertical cells */
	 if (maze.matrix[(randPosL-1)][randPosC] != maze.matrix[(randPosL+1)][randPosC]) {
	    toChange = maze.matrix[(randPosL+1)][randPosC];
	    changeVal = maze.matrix[(randPosL-1)][randPosC];
	    maze.matrix[randPosL][randPosC] = toChange;
	    changeValByOther(maze, toChange, changeVal);
	    compt++;
	 }
      }
   }
   changeValByOther(maze, changeVal, 0);
   generateBonus(maze);
   return 0;
}

/**
 * Generate all bonus and penalty over the maze, random amount between 0 and number of normal cell divided by 6, to avoid a spamming of bonus.
 * @params Board, correspond to the current maze
 * @return int, 0 if no errors occured
 */
int generateBonus(Board maze) {
   int randL;
   int randC;
   int nbMax;
   int nbBonus;
   int nbMalus;
   int compt;

   nbMax = ((maze.rows-1)/2) * ((maze.cols-1)/2);
   /*srand(time(NULL));*/
   nbBonus = rand()%(nbMax/6);
   nbMalus = rand()%(nbMax/6);

   compt = 0;
   while (compt < nbBonus) {
      do {
	 randL = rand()%(maze.rows-2)+1;
	 randC = rand()%(maze.cols-2)+1;
      } while (maze.matrix[randL][randC]!=0);

      maze.matrix[randL][randC] = -3;
      compt++;
   }

   compt = 0;
   while (compt < nbMalus) {
      do {
	 randL = rand()%(maze.rows-2)+1;
	 randC = rand()%(maze.cols-2)+1;
      } while (maze.matrix[randL][randC]!=0);

      maze.matrix[randL][randC] = -4;
      compt++;
   }

   return 0;
}

/**
 * Method call to break walls for the generateMaze method, it change the values in cells of region
 * @params Board maze, correspond to the current maze
 * @params int toChange, correspond to the value we want to change
 * @params int changeVal, the new value to assign to the cell
 * @return int, 0 if no errors occured
 */
int changeValByOther(Board maze, int toChange, int changeVal) {
   int i;
   int j;
   for (i =0; i<maze.rows; i++) {
      for (j=0; j<maze.cols;j++) {
	 if (maze.matrix[i][j]==toChange)
	    maze.matrix[i][j]=changeVal;
      }
   }
   return 0;
}

/**
 * Save the maze in file.cfg, in ./plan/ directory
 * @params Board maze, correspond to the current maze
 * @return int, 0 if no errors occured
 */
int saveMaze(Board maze) {
   FILE *f;
   int l;
   int c;
   char* name_extension;
   char srows[10];
   char scols[10];

   sprintf(srows, "%d", maze.rows);
   sprintf(scols, "%d", maze.cols);

   name_extension = malloc(strlen(maze.name)+12);
   strcpy(name_extension,"./plan/");
   strcat(name_extension,maze.name);
   strcat(name_extension,".cfg");


   f=fopen(name_extension,"w");
   if(f==NULL)
      return -1;

   fputs(srows,f);
   fputc('\n',f);
   fputs(scols,f);
   fputc('\n',f);

   for (l=0;l<maze.rows;l++) {
      for (c=0;c<maze.cols;c++) {
	 switch (maze.matrix[l][c]) {
	 case -1:
	    fputc('#',f);
	    break;
	 case -3:
	    fputc('B',f);
	    break;
	 case -4:
	    fputc('M',f);
	    break;
	 default:
	    fputc(' ',f);
	    break;
	 }
      }
      fputc('\n',f);
   }
   fclose(f);
   free(name_extension);
   return 0;
}

/**
 * Display the maze on the terminal
 * @params Board maze, the current maze to display
 * @return int, 0 if no errors occured
 */
int displayMaze(Board maze) {
   int ro;
   int co;
   char* mur;
   char* player;
   char malus;
   char bonus;

   mur = "\u2588";
   player = "\u29eb";
   malus = '*';
   bonus = '?';

   for (ro=0;ro<maze.rows;ro++) {
      for (co=0;co<maze.cols;co++) {
	 switch (maze.matrix[ro][co]) {
	 case -1:
	    printf("%s%s",LIGHT_GRAY, mur);
	    break;
	 case -2:
	    printf("%s%s",GREEN_BOLD,player);
	    break;
	 case -3:
	    printf("%s%c",YELLOW,bonus);
	    break;
	 case -4:
	    printf("%s%c",RED,malus);
	    break;
	 default:
	    printf(" ");
	    break;
	 }
      }
      printf("\n");
   }
   return 0;
}

/**
 * The methods which manage all movement of the player
 * @params Board maze, the current maze
 * @return int, 0 if no errors occured
 */
int move(Board maze) {
   char movement;
   int arivee = 0;
   int posPL;
   int posPC;
   int score;

   /*Score* tabScore = NULL;*/

   posPL = 1;
   posPC = 0;
   score = 0;



   while (!arivee) {
      movement = getc(stdin);
      switch(movement) {
      case ('z'):
	 if (maze.matrix[posPL-1][posPC] != -1){
	    if (maze.matrix[posPL-1][posPC] == -3)
	       score -= rand()%5;
	    if (maze.matrix[posPL-1][posPC] == -4)
	       score += rand()%5;

	    posPL --;
	    maze.matrix[posPL][posPC] = -2;
	    maze.matrix[posPL+1][posPC] = 0;
	 }
	 break;
      case ('q'):
	 if (maze.matrix[posPL][posPC-1] != -1){
	    if (maze.matrix[posPL][posPC-1] == -3)
	       score -= rand()%5;
	    if (maze.matrix[posPL][posPC-1] == -4)
	       score += rand()%5;

	    posPC --;
	    maze.matrix[posPL][posPC] = -2;
	    maze.matrix[posPL][posPC+1] = 0;
	 }
	 break;
      case ('s'):
	 if (maze.matrix[posPL+1][posPC] != -1){
	    if (maze.matrix[posPL+1][posPC] == -3)
	       score -= rand()%5;
	    if (maze.matrix[posPL+1][posPC] == -4)
	       score += rand()%5;

	    posPL ++;
	    maze.matrix[posPL][posPC] = -2;
	    maze.matrix[posPL-1][posPC] = 0;
	 }
	 break;
      case ('d'):
	 if (maze.matrix[posPL][posPC+1] != -1){
	    if (maze.matrix[posPL][posPC+1] == -3)
	       score -= rand()%5;
	    if (maze.matrix[posPL][posPC+1] == -4)
	       score += rand()%5;

	    posPC ++;
	    maze.matrix[posPL][posPC] = -2;
	    maze.matrix[posPL][posPC-1] = 0;
	 }
	 break;

      default:
	 continue;
      }

      score ++;
      system("clear");
      displayMaze(maze);
      printf("Score : %d\n", score);

      if (posPL==maze.rows-2 && posPC==maze.cols-1) {
	 arivee=1;
	 maze.matrix[maze.rows-2][maze.cols-1]=0;
	 printf("Victoire avec %d déplacements !\n", score);

	 saveScore(maze, score);

	 waitFor(3);
      }
   }
   return 0;
}

/**
 * Read the file which contains best score
 * @params Board maze, the current maze
 * @return Score*, correspond to a table of the Score structure
 * @bugs strtok crash the application
 */
/*Score* readScore(Board maze) {
  FILE* f;
  char* name_extension = NULL;
  int i;
  char* lecture = NULL;
  char* part = NULL;
  int len;
  char* scoreC;
  int score;
  Score* tab = NULL;

  len = strlen(maze.name);

  name_extension = (char*)malloc((len+15)*sizeof(char));
  strcpy(name_extension,"./score/");
  strcat(name_extension,maze.name);
  strcat(name_extension,".score");

  f=fopen(name_extension,"r");
  if(f==NULL)
  return NULL;

  if ((tab = (Score*)malloc(sizeof(Score)*10)) == NULL)
  return NULL;

  printf("ok\n" );

  i = 0;
  while (i < 9) {
  fscanf(f, "%s",lecture);
  printf("%s\n", lecture );
  part = strtok(lecture, ",");
  scoreC = strtok(NULL, ",");
  if (part){
  len = strlen(part);
  if((tab[i].playerName = (char*)malloc(len*(sizeof(char))))==NULL)
  return NULL;

  strcpy(tab[i].playerName, part);

  if (!scoreC)
  score = 0;
  else
  score = atoi(scoreC);

  tab[i].score = score;

  printf("%s : %d pts\n",tab[i].playerName, tab[i].score);
  i++;
  }
  else
  break;
  }
  fclose(f);
  free(name_extension);
  return tab;
  }*/

/**
 * Save the player score if is better than the 10th score
 * @params Board maze, current maze
 * @params Score* tabScore, correspond to the new table of score
 * @return int, 0 if no errors occured
 */
int saveScore(Board maze, int score) {
   FILE* f;
   char* name_extension;
   char pseudo[25];
   char scoreC[10];
   /*int i;*/

   name_extension = (char*)malloc(strlen(maze.name)+15);
   strcpy(name_extension,"./score/");
   strcat(name_extension,maze.name);
   strcat(name_extension,".score");

   printf("Votre pseudo ?\t");
   scanf("%s",pseudo);

   f=fopen(name_extension,"a");
   if(f==NULL)
      return -1;

   fseek(f, 0, SEEK_END);
   fputs(pseudo,f);
   fputc(',',f);
   sprintf(scoreC, "%d", score);
   fputs(scoreC,f);
   fputc('\n',f);

   fclose(f);
   free(name_extension);
   return 0;
}

/**
 * Methods which free the board before leaving
 * @params Board maze, correspond to the current maze
 * @return int, 0 if no errors occured
 */
int quit(Board maze) {
   free(maze.matrix[0]);
   free(maze.matrix);
   return 0;
}

/**
 * Initialize the maze before call move method
 * @params Board maze, current maze
 * @return int, 0 if no errors occured
 */
int play(Board maze) {
   maze.matrix[1][0]=-2;
   displayMaze(maze);
   move(maze);
   return 0;
}

/**
 * Method which load a chosen maze in ./plan/ directory
 * @return Board, correspond to the new current maze
 */
Board loadMaze() {
   char name[35];
   FILE *f;
   Board maze;
   char* path;
   char* nom;

   int compt;
   char lecture;

   maze.matrix = NULL;

   if (nbFile() -2 > 0) {
      printf("Liste des plans disponibles :\n");
      system("ls -1 ./plan/");

      printf("\nVeuillez entrer le nom du fichier à charger\t");
      scanf("%s",name);

      path = concat("./plan/",name);

      f=fopen(path,"r");
      if (f == NULL)
	 return maze;

      fscanf(f,"%d %d", &maze.rows, &maze.cols);
      maze.matrix = mallocMatrix(maze.rows, maze.cols);

      compt=0;
      fgetc(f);
      while (!feof(f)) {
	 lecture = fgetc(f);
	 switch (lecture) {
	 case '#':
	    maze.matrix[0][compt]=-1;
	    compt++;
	    break;
	 case ' ':
	    maze.matrix[0][compt]=0;
	    compt++;
	    break;
	 case 'B':
	    maze.matrix[0][compt]=-3;
	    compt++;
	    break;
	 case 'M':
	    maze.matrix[0][compt]=-4;
	    compt++;
	    break;
	 default:
	    break;
	 }
      }

      nom = strtok(name, ".");
      maze.name = (char*)malloc((strlen(nom))*sizeof(char));
      strcpy(maze.name,nom);

      fclose(f);
      displayMaze(maze);
      waitFor(2);
   }
   else
      perror("Aucun fichier à charger");
   return maze;
}

/**
 * Method which create a new maze
 * @return Board, correspond to the new current maze
 */
Board createMaze() {
   int rows;
   int cols;
   char nameMaze[30];

   Board maze;

   do {
      printf("Count of rows ? \t");
      scanf("%d",&rows);
      printf("Count of columns ?\t");
      scanf("%d",&cols);
   } while(rows%2 == 0 || cols%2 == 0);

   printf("Name of maze ?\t");
   scanf("%s",nameMaze);

   maze.rows = rows;
   maze.cols = cols;

   if ((maze.name = (char*)malloc(strlen(nameMaze)*sizeof(char))) != NULL)
      strcpy(maze.name,nameMaze);

   maze.matrix = NULL;

   if ((maze.matrix = generateBoard(rows, cols)) != NULL) {
      generateMaze(maze);
      saveMaze(maze);
   }

   return maze;
}

/**
 * Count the number of file in directory
 * @return int, correspond to the number of item in directory
 */
int nbFile() {

   int file_count = 0;
   DIR * dirp;
   struct dirent * entry;

   dirp = opendir("./plan");
   while ((entry = readdir(dirp)) != NULL) {
      file_count++;
   }
   closedir(dirp);

   return file_count;
}


/**
 * Methods which wait for a amount of seconds
 * @params unsigned int secs, amount of seconds
 */
void waitFor(unsigned int secs) {
   unsigned int retTime = time(0) + secs;
   while (time(0) < retTime);
}

/**
 * Concat 2 strings and return the result
 * @params const char* s1, the 1st string (const to not change it)
 * @params const char* s2, the 2nd string (const to not change it)
 * @return char*, correspond to the concat of these 2 strings
 */
char* concat(const char* s1, const char* s2) {
   char* result;
   if ((result = (char*)malloc(strlen(s1)+strlen(s2)+1)) == NULL)
      return NULL;
   strcpy(result, s1);
   strcat(result, s2);
   return result;
}
