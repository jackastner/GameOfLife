#include <SDL2/SDL.h>
#include "game_of_life.h"
#include "gol_sdl_gui.h"

int main(int argc, char** argv){
    /*load state from file given as first arg*/
    FILE * f = fopen(argv[1],"r");
    load_state(f);
    fclose(f);

    /*read number of itterations to run from second arg*/
    int itters = atoi(argv[2]);

    /* run specifiec number of iterations, printing the state
     * between steps.*/
    print_state();
    printf("\n");
    for(int i = 0; i < itters; i++){
        update_state();
        print_state();
        printf("\n");
    }

    free_state();
}
