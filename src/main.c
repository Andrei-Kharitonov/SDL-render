#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdint.h>
#include "../include/framebuffer.h"
#include "../include/render.h"
#include "../include/types.h"

int draw_circle_sprite(Sprite_pixel *sprite, Circle *circle) {
  int index = 0;
  double r_sq = circle->radius * circle->radius;

  for (int y = -circle->radius; y <= circle->radius; y++) {
    for (int x = -circle->radius; x <= circle->radius; x++) {
      // fill
      if (!(x * x + y * y + circle->radius*2 > r_sq)) {
        sprite[index].x = x + circle->position.x;
        sprite[index].y = y + circle->position.y;
        sprite[index].color = circle->color;
        index++;
      }
      // edge
      if ((x * x + y * y <= r_sq) && (x * x + y * y + circle->radius*2 > r_sq)) {
        sprite[index].x = x + circle->position.x;
        sprite[index].y = y + circle->position.y;
        sprite[index].color = RED;
        index++;
      }
    }
  }

  return index;
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

// void draw_circle(Circle *circle) {
//   for (int j = 0; j < HEIGHT; j++) {
//     for (int i = 0; i < WIDTH; i++) {
//       double x_sq = pow(circle->position.x - i, 2);
//       double y_sq = pow(circle->position.y - j, 2);
//       double r_sq = pow(circle->radius, 2);
//       // fill
//       if (!(x_sq + y_sq + circle->radius*2 > r_sq)) {
//         paint_pixel(i, j, circle->color);
//       }
//       // edge
//       if ((x_sq + y_sq <= r_sq) && (x_sq + y_sq + circle->radius*2 > r_sq)) {
//         paint_pixel(i, j, GREEN);
//       }
//     }
//   }
// }

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

Circle ball = {
  {WIDTH/2.0, HEIGHT/2.0},
  {53, 27},
  0,
  WHITE,
  20.5
};

// Called every frame
void draw(double delta_time) {
  // draw_circle(&ball);
  render_sprites();

  window_borders_collision((Point *)&ball, ball.radius*2, ball.radius*2);

  // move_point((Point *)&ball, delta_time);
}

int main(int argc, char *argv[]) {
  int ball_sprite_size = ball.radius*ball.radius * 4; // max size
  Sprite_pixel *ball_sprite = malloc(sizeof(Sprite_pixel) * ball_sprite_size);
  ball_sprite_size = draw_circle_sprite(ball_sprite, &ball); // actual size
  ball_sprite = realloc(ball_sprite, sizeof(Sprite_pixel) * ball_sprite_size);
  ball.sprite = ball_sprite;
  add_sprite(ball_sprite, ball_sprite_size);

  int exit_code = render(draw);
  return exit_code;
}
