all: game_of_life

game_of_life: game_of_life.o
	gcc -o game_of_life game_of_life.c

game_of_life.o: game_of_life.c game_of_life.h
	gcc -c game_of_life.c

clean:
	rm -f *.o game_of_life
