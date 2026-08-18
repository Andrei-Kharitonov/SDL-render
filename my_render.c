#define _USE_MATH_DEFINES
#include <math.h>
#include <stdint.h>
#include "framebuffer.h"

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
  Sprite_pixel (*sprite)[];
  uint32_t color;
  double width;
  double height;
} Rectangle;

typedef struct {
  Vector position;
  Vector velocity;
  Sprite_pixel (*sprite)[];
  uint32_t color;
  double radius;
} Circle;

void draw_circle_sprite(Sprite_pixel *sprite, int sprite_size, Circle *circle) {
  int index = 0;
  for (int y = 0; y < circle->radius/2; y++) {
    for (int x = 0; x < circle->radius/2; x++) {
      double x_sq = pow(x, 2);
      double y_sq = pow(y, 2);
      double r_sq = pow(circle->radius, 2);
      // fill
      if (!(x_sq + y_sq + circle->radius*2 > r_sq)) {
        sprite[index].x = x;
        sprite[index].y = y;
        sprite[index].color = circle->color;
        index++;
      }
      // edge
      if ((x_sq + y_sq <= r_sq) && (x_sq + y_sq + circle->radius*2 > r_sq)) {
        sprite[index].x = x;
        sprite[index].y = y;
        sprite[index].color = circle->color;
        index++;
      }
    }
  }
}

void draw_rectangle(Rectangle *rectangle) {
  for (int j = 0; j < HEIGHT; j++) {
    for (int i = 0; i < WIDTH; i++) {
      int h = fabs(rectangle->position.x - i) <= rectangle->width/2 - 1;
      int v = fabs(rectangle->position.y - j) <= rectangle->height/2 - 1;
      int h_border = fabs(rectangle->position.x - i) <= rectangle->width/2;
      int v_border = fabs(rectangle->position.y - j) <= rectangle->height/2;
      // fill
      if (h && v) {
        paint_pixel(i, j, rectangle->color);
      }
      // edge
      if ((h_border && v_border) && !(h && v)) {
        paint_pixel(i, j, GREEN);
      }
    }
  }
}

void draw_circle(Circle *circle) {
  for (int j = 0; j < HEIGHT; j++) {
    for (int i = 0; i < WIDTH; i++) {
      double x_sq = pow(circle->position.x - i, 2);
      double y_sq = pow(circle->position.y - j, 2);
      double r_sq = pow(circle->radius, 2);
      // fill
      if (!(x_sq + y_sq + circle->radius*2 > r_sq)) {
        paint_pixel(i, j, circle->color);
      }
      // edge
      if ((x_sq + y_sq <= r_sq) && (x_sq + y_sq + circle->radius*2 > r_sq)) {
        paint_pixel(i, j, GREEN);
      }
    }
  }
}

void move_point(Point *point, double delta_time) {
  point->position.x += point->velocity.x * delta_time;
  point->position.y -= point->velocity.y * delta_time;
}

void window_borders_collision(Point *point, double width, double height) {
  int is_left = point->position.x - width/2 <= 0;
  int is_right = point->position.x + width/2 >= WIDTH;
  int is_top = point->position.y - height/2 <= 0;
  int is_bottom = point->position.y + height/2 >= HEIGHT;

  if (is_left || is_right) point->velocity.x = -point->velocity.x;
  if (is_top || is_bottom) point->velocity.y = -point->velocity.y;
}

// Rectangle rect = {
//   {20, 80},
//   {35, -41},
//   0,
//   WHITE,
//   32,
//   20
// };

Circle ball = {
  {WIDTH/2.0, HEIGHT/2.0},
  {53, 27},
  0,
  WHITE,
  20
};

void my_render(double delta_time) {
  // draw_rectangle(&rect);
  draw_circle(&ball);

  window_borders_collision((Point *)&ball, ball.radius*2, ball.radius*2);
  // window_borders_collision((Point *)&rect, rect.width, rect.height);

  move_point((Point *)&ball, delta_time);
  // move_point((Point *)&rect, delta_time);
}
