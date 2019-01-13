all: game_of_life

game_of_life: game_of_life.o
	g++ -o game_of_life game_of_life.o

game_of_life.o: game_of_life.cpp game_of_life.h
	g++ -c game_of_life.cpp

clean:
	rm -f *.o game_of_life
