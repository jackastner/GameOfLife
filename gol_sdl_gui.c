#include <SDL2/SDL.h>
#include "game_of_life.h"
#include "gol_sdl_gui.h"

SDL_Window* window;
SDL_Renderer* renderer;

int initialize_all(int width, int height){
    /*Initialize SDL library*/
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"SDL_Init failed: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    /*create and initialize SDL resorces*/
    if(SDL_CreateWindowAndRenderer(width,height,0,&window,&renderer)){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Could not create window and renderer: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    
    /*set window title*/
    SDL_SetWindowTitle(window,"Game of Life");

    return EXIT_SUCCESS;
}

void destroy_all(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
