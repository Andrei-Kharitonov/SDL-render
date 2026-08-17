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
  Vector position;
  Vector velocity;
  uint32_t color;
  double width;
  double height;
} Rectangle;

typedef struct {
  Vector position;
  Vector velocity;
  uint32_t color;
  double radius;
} Circle;

void draw_rectangle(Rectangle *rectangle) {
  for (int j = 0; j < HEIGHT; j++) {
    for (int i = 0; i < WIDTH; i++) {
      int w = fabs(rectangle->position.x - i) <= rectangle->width/2;
      int h = fabs(rectangle->position.y - j) <= rectangle->height/2;
      if (w && h) {
        paint_pixel(i, j, rectangle->color);
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
      // edge
      if (x_sq + y_sq <= r_sq) {
        paint_pixel(i, j, GREEN);
      }
      // fill
      if (!(x_sq + y_sq + circle->radius*2 > r_sq)) {
        paint_pixel(i, j, circle->color);
      }
    }
  }
}

void move_obj(Point *point, double delta_time) {
  point->position.x += point->velocity.x * delta_time;
  point->position.y -= point->velocity.y * delta_time;
}

Rectangle rect = {
  {20, 80},
  {10, 2},
  WHITE,
  16,
  8
};
Circle ball = {
  {WIDTH/2.0, HEIGHT/2.0},
  {57, 23},
  WHITE,
  20,
};


void my_render(double delta_time) {
  draw_rectangle(&rect);
  draw_circle(&ball);

  int is_top = ball.position.y - ball.radius <= 0;
  int is_bottom = ball.position.y + ball.radius >= HEIGHT;
  int is_left = ball.position.x - ball.radius <= 0;
  int is_right = ball.position.x + ball.radius >= WIDTH;

  if (is_top || is_bottom) ball.velocity.y = -ball.velocity.y;
  if (is_left || is_right) ball.velocity.x = -ball.velocity.x;

  move_obj((Point *)&rect, delta_time);
  move_obj((Point *)&ball, delta_time);
}
