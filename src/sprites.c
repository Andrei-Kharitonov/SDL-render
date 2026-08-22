#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "basic_types.h"
#include "consts.h"
#include "framebuffer.h"
#include "lists.h"
#include "sprites.h"
#include "draw_figures.h"

Sprite_pixel *create_sprite(
  Object_sprite *figure_sprite,
  int width,
  int height,
  char paint_out_of_screen
) {
  enum shapes shape = figure_sprite->figure_sprite_t.shape;
  int sprite_size = width * height; // max sprite size
  if (shape != RECTANGLE) {
    sprite_size++;
  }

  Sprite_pixel *sprite = malloc(sizeof(Sprite_pixel) * sprite_size);
  if (!sprite) {
    printf("Sprite memory allocation error\n");
    return 0;
  }
  figure_sprite->figure_sprite_t.sprite_arr = sprite;

  switch (shape) {
    case RECTANGLE:
      draw_rectangle((Rectangle_sprite *)figure_sprite, paint_out_of_screen, SPRITE);
      break;
    case CIRCLE:
      sprite_size = draw_circle((Circle_sprite *)figure_sprite, paint_out_of_screen, SPRITE);
      break;
  }

  if (shape != RECTANGLE) {
    sprite = realloc(sprite, sizeof(Sprite_pixel) * sprite_size);
    if (!sprite) {
      printf("Sprite memory reallocation error\n");
      return 0;
    }
  }

  figure_sprite->figure_sprite_t.sprite_size = sprite_size;
  add_sprite(figure_sprite);
  
  return sprite;
}

void render_sprite(_Figure_sprite *figure_sprite) {
  if (figure_sprite->sprite_arr != NULL) {
    for (int j = 0; j < figure_sprite->sprite_size; j++) {
      int x = figure_sprite->sprite_arr[j].position.x;
      int y = figure_sprite->sprite_arr[j].position.y;

      if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT)) {
        paint_pixel(x, y, figure_sprite->sprite_arr[j].color);
      }
    }
  }
}

void translate_sprite(Object_sprite *figure_sprite_ptr, double delta_time) {
  _Figure_sprite *figure_sprite = &figure_sprite_ptr->figure_sprite_t;

  double dx = figure_sprite->velocity.x * delta_time;
  double dy = figure_sprite->velocity.y * delta_time;

  figure_sprite->position.x += dx;
  figure_sprite->position.y -= dy;

  for (int i = 0; i < figure_sprite->sprite_size; i++) {
    figure_sprite->sprite_arr[i].position.x += dx;
    figure_sprite->sprite_arr[i].position.y -= dy;
  }
}
