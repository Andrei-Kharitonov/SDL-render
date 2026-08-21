#include <math.h>
#include "consts.h"
#include "framebuffer.h"
#include "sprites.h"

void render_rectangle(Rectangle_sprite *rectangle) {
  for (int j = -rectangle->height/2; j < rectangle->height/2; j++) {
    for (int i = -rectangle->height/2; i < rectangle->height/2; i++) {
      int h = fabs(rectangle->position.x - i) <= rectangle->width/2 - 1;
      int v = fabs(rectangle->position.y - j) <= rectangle->height/2 - 1;
      int h_border = fabs(rectangle->position.x - i) <= rectangle->width/2;
      int v_border = fabs(rectangle->position.y - j) <= rectangle->height/2;
      // fill
      if (h && v) {
        paint_pixel(i, j, rectangle->color);
      }
      // border
      if ((h_border && v_border) && !(h && v)) {
        paint_pixel(i, j, GREEN);
      }
    }
  }
}

void render_circle(Circle_sprite *circle) {
  int r = circle->radius;
  int cx = circle->position.x;
  int cy = circle->position.y;

  double r_sq = circle->radius * circle->radius;
  double inner_r = circle->radius - 1.0;
  double inner_r_sq = inner_r * inner_r;

  for (int y = cy - r; y <= cy + r; ++y) {
    for (int x = cx - r; x <= cx + r; ++x) {
      if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        double dx = x - circle->position.x;
        double dy = y - circle->position.y;
        double d_sq = dx * dx + dy * dy;

        if (d_sq <= inner_r_sq) {
          paint_pixel(x, y, circle->color);
        }
        else if (d_sq <= r_sq) {
          paint_pixel(x, y, GREEN);
        }
      }
    }
  }
}
