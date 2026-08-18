build:
	gcc ./src/*.c `pkg-config --cflags sdl3` `pkg-config --libs sdl3` -o main -lm -O3

run:
	./main
