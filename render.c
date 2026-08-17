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

void move_obj(Point *point, double delta_time) {
  point->position.x += point->velocity.x * delta_time;
  point->position.y -= point->velocity.y * delta_time;
}

Rectangle rect = {
  {20, 80},
  {35, -41},
  WHITE,
  32,
  20
};

Circle ball = {
  {WIDTH/2.0, HEIGHT/2.0},
  {53, 27},
  WHITE,
  20
};


void my_render(double delta_time) {
  draw_rectangle(&rect);
  draw_circle(&ball);

  int c_is_top = ball.position.y - ball.radius <= 0;
  int c_is_bottom = ball.position.y + ball.radius >= HEIGHT;
  int c_is_left = ball.position.x - ball.radius <= 0;
  int c_is_right = ball.position.x + ball.radius >= WIDTH;

  int r_is_top = rect.position.y - rect.height/2 <= 0;
  int r_is_bottom = rect.position.y + rect.height/2 >= HEIGHT;
  int r_is_left = rect.position.x - rect.width/2 <= 0;
  int r_is_right = rect.position.x + rect.width/2 >= WIDTH;

  if (c_is_top || c_is_bottom) ball.velocity.y = -ball.velocity.y;
  if (c_is_left || c_is_right) ball.velocity.x = -ball.velocity.x;

  if (r_is_top || r_is_bottom) rect.velocity.y = -rect.velocity.y;
  if (r_is_left || r_is_right) rect.velocity.x = -rect.velocity.x;

  move_obj((Point *)&ball, delta_time);
  move_obj((Point *)&rect, delta_time);
}
