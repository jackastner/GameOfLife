all: game_of_life

game_of_life: main.o game_of_life.o gol_sdl_gui.o
	gcc -o game_of_life main.o game_of_life.o gol_sdl_gui.o `pkg-config --libs --cflags sdl2 SDL2_ttf SDL2_image`

main.o: main.c game_of_life.h  gol_sdl_gui.h
	gcc -c main.c
	
game_of_life.o: game_of_life.c game_of_life.h
	gcc -c game_of_life.c

gol_sdl_gui.o: gol_sdl_gui.c gol_sdl_gui.c game_of_life.h
	gcc -c gol_sdl_gui.c

clean:
	rm -f *.o game_of_life
