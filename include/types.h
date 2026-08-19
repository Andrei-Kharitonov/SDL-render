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
} Point;

typedef struct {
  int x;
  int y;
  uint32_t color;
} Sprite_pixel;

typedef struct {
  Vector position;
  Vector velocity;
  Sprite_pixel *sprite;
  uint32_t color;
  double width;
  double height;
} Rectangle;

typedef struct {
  Vector position;
  Vector velocity;
  Sprite_pixel *sprite;
  uint32_t color;
  double radius;
} Circle;

#endif
