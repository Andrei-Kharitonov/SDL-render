#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

enum shapes {
  CIRCLE,
  RECTANGLE
};

typedef struct {
  double x;
  double y;
} Vector;

typedef struct {
  Vector position;
  Vector velocity;
} _Point;

typedef struct {
  Vector position;
  Vector velocity;

  enum shapes shape;
} _Figure;

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

typedef union {
  _Point point_t;
  _Figure figgure_t;
  _Figure_sprite figure_sprite_t;

  Rectangle_sprite rectangle_t;
  Circle_sprite circle_t;
} Object_sprite;


typedef struct {
  Vector position;
  Vector velocity;

  enum shapes shape;

  double width;
  double height;
} Rectangle_hitbox;

typedef struct {
  Vector position;
  Vector velocity;

  enum shapes shape;

  double radius;
} Circle_hitbox;

typedef union {
  _Point point_t;
  _Figure figure_t;

  Rectangle_hitbox rectangle_t;
  Circle_hitbox circle_t;
} Object_hitbox;

#endif
