#ifndef SPRITES_H
#define SPRITES_H

#include "basic_types.h"

typedef struct {
  Vector position;
  uint32_t color;
} Sprite_pixel;

typedef struct {
  Vector position;
  Vector velocity;
  enum shapes shape;
  Sprite_pixel *sprite_arr;
  uint32_t sprite_size;
  uint32_t color;
} _Figure_sprite;

typedef struct {
  Vector position;
  Vector velocity;
  enum shapes shape;
  Sprite_pixel *sprite_arr;
  uint32_t sprite_size;
  uint32_t color;
  double width;
  double height;
} Rectangle_sprite;

typedef struct {
  Vector position;
  Vector velocity;
  enum shapes shape;
  Sprite_pixel *sprite_arr;
  uint32_t sprite_size;
  uint32_t color;
  double radius;
} Circle_sprite;

// generic for sprites
typedef union {
  _Point point_t;
  _Figure figgure_t;
  _Figure_sprite figure_sprite_t;
  Rectangle_sprite rectangle_t;
  Circle_sprite circle_t;
} Object_sprite;


int draw_rectangle_sprite(Sprite_pixel sprite[], Object_sprite *rectangle_ptr);

int draw_circle_sprite(Sprite_pixel sprite[], Object_sprite *circle_ptr);

Sprite_pixel *create_sprite(
  int width,
  int height,
  Object_sprite *figure_sprite,
  int (*draw_sprite)(Sprite_pixel [], Object_sprite *)
);

void translate_sprite(Object_sprite *figure_sprite_ptr, double delta_time);

#endif
