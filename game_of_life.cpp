#include "game_of_life.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*calculate the state that a cell will have after a transition*/
cell_state GameOfLife::next_state(int row, int col){
    unsigned char neighbours = count_neighbours(row,col);
    if(neighbours == 3){
        return 1;
    } else if (neighbours < 2 || neighbours > 3){
        return 0;
    }
    return current_state[row][col];
}

/* retreive the state of a cell at the specifed index. Cells out side the
 * bounds of the underlying array are treated as if they wrap at the edges*/
cell_state GameOfLife::get_state(int row, int col){
    row = row < 0 ? game_rows + row : (row >= game_rows ? row - game_rows : row);
    col = col < 0 ? game_cols + col : (col >= game_cols ? col - game_cols : col);

    return current_state[row][col];
}

/* Count the number of adjacent living neighbours*/
unsigned char GameOfLife::count_neighbours(int row, int col){
    return get_state(row-1,col-1) + get_state(row-1,col) + get_state(row-1,col+1) + 
           get_state(row,col-1)     /*      self      */ + get_state(row,col+1)   +
           get_state(row+1,col-1) + get_state(row+1,col) + get_state(row+1,col+1);
}

/* Update the state of the game. Applying the transition rule to every cell*/
void GameOfLife::update_state(){
    for(int row = 0; row < game_rows; row++){
        for(int col = 0; col < game_cols; col++){
            buffer_state[row][col] = next_state(row,col);
        }
    }

    for(int row = 0; row < game_rows; row++){
        memcpy(current_state[row],buffer_state[row],(sizeof(cell_state))*game_cols);
    }
}

/* Load an initial state from a file where the first line contains the number
 * of row followed by collumns and the reset of the files consists of 1's 
 * and 0's each showing the state of a cell*/
void GameOfLife::load_state(FILE* f){
    /*read the dimensions of the board*/
    fscanf(f,"%d %d",&game_rows,&game_cols);

    /*allocate memory for the game state and buffer state*/
    current_state = (cell_state**) malloc((sizeof(cell_state*))*game_rows);
    buffer_state = (cell_state**) malloc((sizeof(cell_state*))*game_rows);
    /*each row must be initialized individualy*/
    for(int row = 0; row < game_rows; row++){
        current_state[row] = (cell_state*) malloc((sizeof(cell_state))*game_cols);
        buffer_state[row] = (cell_state*) malloc((sizeof(cell_state))*game_cols);
    }

    /*read the remaining lines into the previously alocated data structures.*/
    for(int row = 0; row < game_rows; row++){
        int col = 0;
        while(col < game_cols){
            int next_c = getc(f);
            if(next_c == '0' || next_c == '1'){
                current_state[row][col] = next_c-'0';
                col++;
            }
        }
    }
}

/*print an ASCII repsentation of the current game state to stdout*/
void GameOfLife::print_state(){
    for(int row = 0; row < game_rows; row++){
        for(int col = 0; col < game_cols; col++){
            printf("%c",current_state[row][col]?'X':' ');
        }
        printf("\n");
    }
}

/* Free all memory alocated by calls to load_state. This function
 * should be called between all calls to load_state to eliminate
 * memory leaks.*/
void GameOfLife::free_state(){
    /*all rows need to be freed seperatly*/
    for(int row = 0; row < game_rows; row++){
        free(current_state[row]);
        free(buffer_state[row]);
    }

    /*now the state can be freed*/
    free(current_state);
    free(buffer_state);
}

int main(int argc, char** argv){
    GameOfLife game;

    /*load state from file given as first arg*/
    FILE * f = fopen(argv[1],"r");
    game.load_state(f);
    fclose(f);

    /*read number of itterations to run from second arg*/
    int itters = atoi(argv[2]);

    /* run specifiec number of iterations, printing the state
     * between steps.*/
    game.print_state();
    printf("\n");
    for(int i = 0; i < itters; i++){
        game.update_state();
        game.print_state();
        printf("\n");
    }

    game.free_state();
}
