build:
	gcc main.c `pkg-config --cflags sdl3` `pkg-config --libs sdl3` -o main -lm

run:
	./main
