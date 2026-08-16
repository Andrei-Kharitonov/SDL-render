#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define WIDTH 320
#define HEIGHT 200
#define SCALE 4
#define FPS 60

#define WHITE 0xFFFFFF00
#define BLACK 0x00000000
#define RED 0xFF000000
#define GREEN 0x00FF0000
#define BLUE 0x0000FF00

uint32_t framebuffer[WIDTH * HEIGHT];

void clear_framebuf(uint32_t color) {
  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    framebuffer[i] = color;
  }
}

void paint_pixel(uint32_t x, uint32_t y, uint32_t color) {
  framebuffer[WIDTH * y + x] = color;
}


// Your code
void render() {
  paint_pixel(WIDTH/2, HEIGHT/2, GREEN); 
}


int main(int argc, char *argv[]) {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  SDL_Event event;

  const double target_framerate = 1.0 / (double)FPS;

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "SDL Init failed: %s \n", SDL_GetError());
    return EXIT_FAILURE;
  }

  window = SDL_CreateWindow(
    "SDL Framebuffer",
    WIDTH * SCALE,
    HEIGHT * SCALE,
    0
  );
  if (window == NULL) {
    fprintf(stderr, "SDL Window failed: %s \n", SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(
    window,
    NULL
  );
  if (renderer == NULL) {
    fprintf(stderr, "SDL Renderer failed: %s \n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_RGBX8888,
    SDL_TEXTUREACCESS_STREAMING,
    WIDTH,
    HEIGHT
  );
  if (texture == NULL) {
    fprintf(stderr, "SDL Texture failed: %s \n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

  uint8_t is_running = 1;

  while (is_running) {
    uint64_t start = SDL_GetPerformanceCounter();

    // Poll events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        is_running = 0;
      }
    }

    clear_framebuf(BLACK); // background color
    render();

    SDL_UpdateTexture(
      texture,
      NULL,
      framebuffer,
      WIDTH * sizeof(framebuffer[0]) // pitch: the width of the picture in bytes
    );

    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    uint64_t end = SDL_GetPerformanceCounter();

    double elapsed = (double)(end - start) / (double)SDL_GetPerformanceFrequency();

    // Cap framerate to FPS
    if (elapsed < target_framerate) {
      SDL_Delay((target_framerate - elapsed) * 1000.0);
    }
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
