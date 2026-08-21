#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "consts.h"
#include "framebuffer.h"
#include "lists.h"
#include "sprites.h"

int draw_rectangle_sprite(Sprite_pixel sprite[], Object_sprite *rectangle_prt) {
  Rectangle_sprite *rectangle = &rectangle_prt->rectangle_t;
  int index = 0;

  float w = rectangle->width / 2.0;
  float h = rectangle->height / 2.0;
  int rx = rectangle->position.x;
  int ry = rectangle->position.y;
  int border = 1;

  for (float y = ry - h; y < ry + h; y++) {
    for (float x = rx - w; x < rx + w; x++) {
      int top    = y >= ry + h - border;
      int right  = x >= rx + w - border;
      int left   = x < rx - w + border;
      int bottom = y < ry - h + border;

      if (left || right || top || bottom) {
        sprite[index].position.x = x;
        sprite[index].position.y = y;
        sprite[index].color = RED;
      } else if (!(left || right || top || bottom)) {
        sprite[index].position.x = x;
        sprite[index].position.y = y;
        sprite[index].color = rectangle->color;
      }
      index++;
    }
  }

  return index;
}

int draw_circle_sprite(Sprite_pixel sprite[], Object_sprite *circle_ptr) {
  Circle_sprite *circle = &circle_ptr->circle_t;
  int index = 0;
  
  int r = circle->radius;
  int cx = circle->position.x;
  int cy = circle->position.y;

  double r_sq = circle->radius * circle->radius;
  double inner_r = circle->radius - 1.0;
  double inner_r_sq = inner_r * inner_r;

  for (int y = cy - r; y <= cy + r; y++) {
    for (int x = cx - r; x <= cx + r; x++) {
      double dx = x - circle->position.x;
      double dy = y - circle->position.y;
      double d_sq = dx * dx + dy * dy;

      if (d_sq <= inner_r_sq) {
        sprite[index].position.x = x;
        sprite[index].position.y = y;
        sprite[index].color = circle->color;
        index++;
      } else if (d_sq <= r_sq) {
        sprite[index].position.x = x;
        sprite[index].position.y = y;
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
