#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H
#endif

#include <stdio.h>

/* global variables that hold the dimensions of the 
 * game*/
int GAME_COLS,GAME_ROWS;

typedef unsigned char cell_state;

/* global variables that hold the state of the game
 * buffer_state is used to hold intermediate states*/
cell_state **current_state;
cell_state **buffer_state;

cell_state next_state(int row, int col); 
cell_state get_state(int row, int col);
unsigned char count_neighbours(int row, int col);
void update_state();
void load_state(FILE* f);
void print_state();
void free_state();
