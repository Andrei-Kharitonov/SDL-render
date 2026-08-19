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
  uint32_t color;
} Sprite_pixel;

typedef struct {
  Vector position;
  Vector velocity;

  Sprite_pixel *sprite;
  uint32_t sprite_size;

  enum shapes shape;
  uint32_t color;
} _Figure;


typedef struct {
  Vector position;
  Vector velocity;

  Sprite_pixel *sprite;
  uint32_t sprite_size;

  enum shapes shape;
  uint32_t color;

  double width;
  double height;
} Rectangle;

typedef struct {
  Vector position;
  Vector velocity;

  Sprite_pixel *sprite;
  uint32_t sprite_size;

  enum shapes shape;
  uint32_t color;

  double radius;
} Circle;


typedef union {
  _Point point_t;
  _Figure figure_t;

  Rectangle rectangle_t;
  Circle circle_t;
} Object;

#endif
