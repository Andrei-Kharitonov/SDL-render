#ifndef SPRITES_H
#define SPRITES_H

#include "basic_types.h"

enum Draw_types {
  RENDER,
  SPRITE
};

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
  int width;
  int height;
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


Sprite_pixel *create_sprite(Object_sprite *figure_sprite, int width, int height, char paint_out_of_screen);

void render_sprite(_Figure_sprite *figure_sprite);

void translate_sprite(Object_sprite *figure_sprite_ptr, double delta_time);

#endif
