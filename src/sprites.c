#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "consts.h"
#include "lists.h"
#include "sprites.h"

int draw_circle_sprite(Sprite_pixel sprite[], Object_sprite *circle_ptr) {
  Circle_sprite *circle = &circle_ptr->circle_t;
  int index = 0;
  double r_sq = circle->radius * circle->radius;

  for (double y = -circle->radius; y <= circle->radius; y++) {
    for (double x = -circle->radius; x <= circle->radius; x++) {
      // fill
      if (!(x * x + y * y + circle->radius*2 > r_sq)) {
        sprite[index].position.x = x + circle->position.x;
        sprite[index].position.y = y + circle->position.y;
        sprite[index].color = circle->color;
        index++;
      }
      // edge
      if ((x * x + y * y <= r_sq) && (x * x + y * y + circle->radius*2 > r_sq)) {
        sprite[index].position.x = x + circle->position.x;
        sprite[index].position.y = y + circle->position.y;
        sprite[index].color = RED;
        index++;
      }
    }
  }

  return index;
}

Sprite_pixel *create_sprite(
  int width,
  int height,
  Object_sprite *figure_sprite,
  int (*draw_sprite)(Sprite_pixel [], Object_sprite *)
) {
  enum shapes shape = figure_sprite->figure_sprite_t.shape;

  int sprite_size = width * height; // max sprite size
  if (shape != RECTANGLE) sprite_size++;

  Sprite_pixel *sprite = malloc(sizeof(Sprite_pixel) * sprite_size);

  if (!sprite) {
    printf("Sprite memory allocation error\n");
    return 0;
  }

  sprite_size = draw_sprite(sprite, figure_sprite); // actual size
  if (shape != RECTANGLE) {
    sprite = realloc(sprite, sizeof(Sprite_pixel) * sprite_size);
  }

  if (!sprite) {
    printf("Sprite memory reallocation error\n");
    return 0;
  }

  figure_sprite->figure_sprite_t.sprite_size = sprite_size;
  add_sprite(sprite_list, figure_sprite);
  
  return sprite;
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
