all: game_of_life

game_of_life: game_of_life.o gol_gtk_app.o 
	gcc -o game_of_life game_of_life.o gol_gtk_app.o `pkg-config --libs gtk+-3.0` 

game_of_life.o: game_of_life.c game_of_life.h
	gcc -c game_of_life.c

gol_gtk_app.o: gol_gtk_app.c gol_gtk_app.h game_of_life.h
	gcc `pkg-config --cflags gtk+-3.0` -c gol_gtk_app.c

clean:
	rm -f *.o game_of_life
