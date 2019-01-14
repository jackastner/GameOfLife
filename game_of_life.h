#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H
#endif

#include <istream>

typedef unsigned char cell_state;

class GameOfLife {
        /* define the dimensions of the game */
        int game_cols, game_rows;

        /* define the state of the game
         * buffer_state is used to hold intermediate states */
        cell_state **current_state, **buffer_state;

        cell_state next_state(int row, int col);
        unsigned char count_neighbours(int row, int col);

    public:
        void update_state();
        cell_state get_state(int row, int col);
        void load_state(std::istream* in);
        void print_state();
        void free_state();
};
