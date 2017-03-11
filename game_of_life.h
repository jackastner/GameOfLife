#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H
#endif

#include <stdio.h>

#define GAME_ROWS  20
#define GAME_COLS 20

typedef unsigned char cell_state;
typedef cell_state game_board[GAME_ROWS][GAME_COLS];

game_board current_state;
game_board buffer_state;

cell_state next_state(int row, int col); 
cell_state get_state(int row, int col);
unsigned char count_neighbours(int row, int col);
void update_state();
void load_state(FILE* f);
void print_state();
