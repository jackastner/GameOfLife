CFLAGS = -Wall -Wextra -g -std=c++11

all: game_of_life

game_of_life: game_of_life.o
	g++ $(CFLAGS) -o game_of_life game_of_life.o

game_of_life.o: game_of_life.cpp game_of_life.h
	g++ $(CFLAGS) -c game_of_life.cpp

clean:
	rm -f *.o game_of_life
