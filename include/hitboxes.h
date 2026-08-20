#ifndef HITBOXES_H
#define HITBOXES_H

#include "basic_types.h"

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

// generic for hitboxes
typedef union {
  _Point point_t;
  _Figure figure_t;
  Rectangle_hitbox rectangle_t;
  Circle_hitbox circle_t;
} Object_hitbox;

#endif
