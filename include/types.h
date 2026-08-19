#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

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
  uint32_t color;
} Sprite_pixel;

typedef struct {
  Vector position;
  Vector velocity;

  Sprite_pixel *sprite;
  uint32_t sprite_size;
} _Figure;

typedef struct {
  Vector position;
  Vector velocity;

  Sprite_pixel *sprite;
  uint32_t sprite_size;

  uint32_t color;
  double width;
  double height;
} Rectangle;

typedef struct {
  Vector position;
  Vector velocity;

  Sprite_pixel *sprite;
  uint32_t sprite_size;

  uint32_t color;
  double radius;
} Circle;

#endif
