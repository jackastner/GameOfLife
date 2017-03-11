#include "game_of_life.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cell_state next_state(int row, int col){
    unsigned char neighbours = count_neighbours(row,col);
    if(neighbours == 3){
        return 1;
    } else if (neighbours < 2 || neighbours > 3){
        return 0;
    }
    return current_state[row][col];
}

cell_state get_state(int row, int col){
    if(row < 0 || row >= GAME_ROWS || col < 0 || col >= GAME_ROWS){
        return 0;
    }
    return current_state[row][col];
}

unsigned char count_neighbours(int row, int col){
    return get_state(row-1,col-1) + get_state(row-1,col) + get_state(row-1,col+1) + 
           get_state(row,col-1)     /*      self      */ + get_state(row,col+1)   +
           get_state(row+1,col-1) + get_state(row+1,col) + get_state(row+1,col+1);
}

void update_state(){
    for(int row = 0; row < GAME_ROWS; row++){
        for(int col = 0; col < GAME_COLS; col++){
            buffer_state[row][col] = next_state(row,col);
        }
    }
    memcpy(current_state,buffer_state,(sizeof(cell_state))*GAME_ROWS*GAME_COLS);
}

void load_state(FILE* f){
    for(int row = 0; row < GAME_ROWS; row++){
        int col = 0;
        while(col < GAME_COLS){
            int next_c = getc(f);
            if(next_c == '0' || next_c == '1'){
                current_state[row][col] = next_c-'0';
                col++;
            }
        }
    }
}

void print_state(){
    for(int row = 0; row < GAME_ROWS; row++){
        for(int col = 0; col < GAME_COLS; col++){
            printf("%d",current_state[row][col]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv){
    FILE * f = fopen(argv[1],"r");
    load_state(f);
    fclose(f);

    int itters = atoi(argv[2]);

    print_state();
    printf("\n");
    for(int i = 0; i < itters; i++){
        update_state();
        print_state();
        printf("\n");
    }
}
