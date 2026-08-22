#ifndef DRAW_FIGURES_H
#define DRAW_FIGURES_H

#include "sprites.h"

enum Draw_types {
  RENDER,
  SPRITE
};

int draw_rectangle(
  Rectangle_sprite *rectangle,
  enum Draw_types draw_type,
  char paint_out_of_screen
);

int draw_circle(
  Circle_sprite *circle,
  enum Draw_types draw_type,
  char paint_out_of_screen
);

#endif
