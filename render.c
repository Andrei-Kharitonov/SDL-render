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
      int w = fabs(rectangle->position.x - i) <= rectangle->width/2 || fabs(rectangle->position.x + i) <= rectangle->width/2;
      int h = fabs(rectangle->position.y - j) <= rectangle->height/2 || fabs(rectangle->position.y + j) <= rectangle->height/2;
      if (w & h) {
        paint_pixel(i, j, rectangle->color);
      }
    }
  }
}

void draw_circle(Circle *circle) {
  for (int j = 0; j < HEIGHT; j++) {
    for (int i = 0; i < WIDTH; i++) {
      int x_sq = pow(circle->position.x - i, 2);
      int y_sq = pow(circle->position.y - j, 2);
      if ((x_sq + y_sq) <= pow(circle->radius, 2)) {
        paint_pixel(i, j, circle->color);
      }
    }
  }
}

void move_obj(Point *point, double delta_time) {
  point->position.x += point->velocity.x * delta_time;
  point->position.y -= point->velocity.y * delta_time;
}

// Rectangle wall_left = {
//   {WIDTH*0.1, HEIGHT/2.0},
//   {0, 0},
//   WHITE,
//   10,
//   HEIGHT*0.9,
// };
// Rectangle wall_right = {
//   {WIDTH*0.9, HEIGHT/2.0},
//   {0, 0},
//   WHITE,
//   10,
//   HEIGHT*0.9,
// };
Circle ball = {
  {WIDTH/2.0, HEIGHT/2.0},
  {51, 37},
  WHITE,
  20,
};


void my_render(double delta_time) {
  draw_circle(&ball);

  int is_top = ball.position.y - ball.radius <= 0;
  int is_bottom = ball.position.y + ball.radius >= HEIGHT;
  int is_left = ball.position.x - ball.radius <= 0;
  int is_right = ball.position.x + ball.radius >= WIDTH;

  if (is_top || is_bottom) ball.velocity.y = -ball.velocity.y;
  if (is_left || is_right) ball.velocity.x = -ball.velocity.x;

  move_obj((Point *)&ball, delta_time);
}
