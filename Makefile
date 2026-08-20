CFLAGS = -I./include -O3
LIBS = `pkg-config --libs sdl3` -lm
SDL_CFLAGS = `pkg-config --cflags sdl3`
SRC = ./src/*.c
OUT = main

build:
	gcc $(CFLAGS) $(SDL_CFLAGS) $(LIBS) $(SRC) -o $(OUT)

run:
	./$(OUT)

