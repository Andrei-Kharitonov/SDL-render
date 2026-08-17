#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define WIDTH 320
#define HEIGHT 200
#define SCALE 4
#define FPS_CAP 60

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

uint32_t get_pixel_color(uint32_t x, uint32_t y) {
  return framebuffer[WIDTH * y + x];
}


// ==================
typedef struct {
  double x;
  double y;
} Vector;

typedef struct {
  Vector position;
  Vector velocity;
} Point;

typedef struct {
  Vector position;
  Vector velocity;
  uint32_t color;
  double width;
  double height;
} Rectangle;

typedef struct {
  Vector position;
  Vector velocity;
  uint32_t color;
  double radius;
} Circle;

void draw_rectangle(Rectangle *rectangle) {
  for (int j = 0; j < HEIGHT; j++) {
    for (int i = 0; i < WIDTH; i++) {
      int w = fabs(rectangle->position.x - i) <= rectangle->width/2 || fabs(rectangle->position.x + i) <= rectangle->width/2;
      int h = fabs(rectangle->position.y - j) <= rectangle->height/2 || fabs(rectangle->position.y + j) <= rectangle->height/2;
      if (w & h) {
        paint_pixel(i, j, rectangle->color);
      }
    }
  }
}

void draw_circle(Circle *circle) {
  for (int j = 0; j < HEIGHT; j++) {
    for (int i = 0; i < WIDTH; i++) {
      int x_sq = pow(circle->position.x - i, 2);
      int y_sq = pow(circle->position.y - j, 2);
      if ((x_sq + y_sq) <= pow(circle->radius, 2)) {
        paint_pixel(i, j, circle->color);
      }
    }
  }
}

void move_obj(Point *point, double delta_time) {
  point->position.x += point->velocity.x * delta_time;
  point->position.y -= point->velocity.y * delta_time;
}

Rectangle wall_left = {
  {WIDTH*0.1, HEIGHT/2.0},
  {0, 0},
  WHITE,
  10,
  HEIGHT*0.9,
};
Rectangle wall_right = {
  {WIDTH*0.9, HEIGHT/2.0},
  {0, 0},
  WHITE,
  10,
  HEIGHT*0.9,
};
Circle ball = {
  {WIDTH/2.0, HEIGHT/2.0},
  {10, 2},
  WHITE,
  8,
};

void render(double delta_time) {
  draw_rectangle(&wall_left);
  draw_rectangle(&wall_right);

  draw_circle(&ball);
  move_obj((Point *)&ball, delta_time);
}
// ==================


int main(int argc, char *argv[]) {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  SDL_Event event;

  const double target_framerate = 1.0 / (double)FPS_CAP;
  double delta_time = 0.0;

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
  uint64_t last_time = SDL_GetPerformanceCounter(); 
  uint64_t fps_time = SDL_GetPerformanceCounter();

  while (is_running) {
    uint64_t start = SDL_GetPerformanceCounter();
    delta_time = (double)(start - last_time) / SDL_GetPerformanceFrequency();
    last_time = start;

    // Print fps every 1 second
    if (start - fps_time >= SDL_GetPerformanceFrequency()) {
      fps_time = start;
      printf("\rFPS: %.1f", 1.0 / delta_time);
      fflush(stdout);
    }

    // Poll events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        is_running = 0;
      }
    }

    clear_framebuf(BLACK); // background color
    render(delta_time);

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

    // Cap framerate to FPS_CAP
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
