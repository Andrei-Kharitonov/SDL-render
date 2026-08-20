#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

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

#endif
