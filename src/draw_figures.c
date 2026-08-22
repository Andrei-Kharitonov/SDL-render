#include "consts.h"
#include "framebuffer.h"
#include "sprites.h"

int draw_rectangle(
  Rectangle_sprite *rectangle,
  enum Draw_types draw_type,
  char paint_out_of_screen
) {
  float w = rectangle->width / 2.0;
  float h = rectangle->height / 2.0;
  int rx = rectangle->position.x;
  int ry = rectangle->position.y;
  int size = 0;
  int border = 1;

  for (float y = ry - h; y < ry + h; y++) {
    for (float x = rx - w; x < rx + w; x++) {
      if (paint_out_of_screen || (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)) {
        int top    = y >= ry + h - border;
        int right  = x >= rx + w - border;
        int left   = x < rx - w + border;
        int bottom = y < ry - h + border;

        if (left || right || top || bottom) {
          switch (draw_type) {
            case RENDER:
              paint_pixel(x, y, GREEN);
              break;
            case SPRITE:
              rectangle->sprite_arr[size].position.x = x;
              rectangle->sprite_arr[size].position.y = y;
              rectangle->sprite_arr[size].color = RED;
              break;
          }
          size++;
        } else if (!(left || right || top || bottom)) { 
          switch (draw_type) {
            case RENDER:
              paint_pixel(x, y, rectangle->color);
              break;
            case SPRITE:
              rectangle->sprite_arr[size].position.x = x;
              rectangle->sprite_arr[size].position.y = y;
              rectangle->sprite_arr[size].color = rectangle->color;
              break;
          }
          size++;
        }
      }
    }
  }

  return size;
}

int draw_circle(
  Circle_sprite *circle,
  enum Draw_types draw_type,
  char paint_out_of_screen
) {
  int r = circle->radius;
  int cx = circle->position.x;
  int cy = circle->position.y;
  int size = 0;

  double r_sq = circle->radius * circle->radius;
  double inner_r = circle->radius - 1.0;
  double inner_r_sq = inner_r * inner_r;

  for (int y = cy - r; y <= cy + r; y++) {
    for (int x = cx - r; x <= cx + r; x++) {
      if (paint_out_of_screen || (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)) {
        double dx = x - circle->position.x;
        double dy = y - circle->position.y;
        double d_sq = dx * dx + dy * dy;

        if (d_sq <= inner_r_sq) {
          switch (draw_type) {
            case RENDER:
              paint_pixel(x, y, circle->color);
              break;
            case SPRITE:
              circle->sprite_arr[size].position.x = x;
              circle->sprite_arr[size].position.y = y;
              circle->sprite_arr[size].color = circle->color;
              break;
          }
          size++;
        } else if (d_sq <= r_sq) {
          switch (draw_type) {
            case RENDER:
              paint_pixel(x, y, GREEN);
              break;
            case SPRITE:
              circle->sprite_arr[size].position.x = x;
              circle->sprite_arr[size].position.y = y;
              circle->sprite_arr[size].color = RED;
              break;
          }
          size++;
        }
      }
    }
  }

  return size;
}
