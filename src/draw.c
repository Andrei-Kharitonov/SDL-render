#include "consts.h"
#include "framebuffer.h"
#include "sprites.h"

void render_rectangle(Rectangle_sprite *rectangle) {
  int w = rectangle->width / 2;
  int h = rectangle->height / 2;
  int rx = rectangle->position.x;
  int ry = rectangle->position.y;
  int border = 1;

  for (int y = ry - h; y <= ry + h; y++) {
    for (int x = rx - w; x <= rx + w; x++) {
      if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        int top_left = (x >= rx - w + border) && (y >= ry - h + border);
        int bottom_right = (x <= rx + w - border) && (y <= ry + h - border);

        if (top_left && bottom_right) {
          paint_pixel(x, y, rectangle->color);
        } else {
          paint_pixel(x, y, GREEN);
        }
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
