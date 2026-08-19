#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/framebuffer.h"
#include "../include/render.h"
#include "../include/types.h"

int draw_circle_sprite(Sprite_pixel sprite[], Object *circle_ptr) {
  Circle *circle = &circle_ptr->circle_t;
  int index = 0;
  double r_sq = circle->radius * circle->radius;

  for (double y = -circle->radius; y <= circle->radius; y++) {
    for (double x = -circle->radius; x <= circle->radius; x++) {
      // fill
      if (!(x * x + y * y + circle->radius*2 > r_sq)) {
        sprite[index].position.x = x + circle->position.x;
        sprite[index].position.y = y + circle->position.y;
        sprite[index].color = circle->color;
        index++;
      }
      // edge
      if ((x * x + y * y <= r_sq) && (x * x + y * y + circle->radius*2 > r_sq)) {
        sprite[index].position.x = x + circle->position.x;
        sprite[index].position.y = y + circle->position.y;
        sprite[index].color = RED;
        index++;
      }
    }
  }

  return index;
}

Sprite_pixel *create_sprite(
  int width,
  int height,
  uint32_t *size,
  Object *figure,
  int (*draw_sprite)(Sprite_pixel [], Object *)
) {
  enum shapes shape = figure->figure_t.shape;
  int sprite_size = width * height; // max sprite size
  if (shape != RECTANGLE) {
    sprite_size++;
  }
  Sprite_pixel *sprite = malloc(sizeof(Sprite_pixel) * sprite_size);

  if (!sprite) {
    printf("Sprite memory allocation error\n");
    return 0;
  }

  sprite_size = draw_sprite(sprite, figure); // actual size
  if (shape != RECTANGLE) {
    sprite = realloc(sprite, sizeof(Sprite_pixel) * sprite_size);
  }

  if (!sprite) {
    printf("Sprite memory reallocation error\n");
    return 0;
  }

  *size = sprite_size;
  add_sprite(sprite, sprite_size);
  
  return sprite;
}

void move_figure(Object *figure_ptr, double delta_time) {
  _Figure *figure = &figure_ptr->figure_t;

  double dx = figure->velocity.x * delta_time;
  double dy = figure->velocity.y * delta_time;

  figure->position.x += dx;
  figure->position.y -= dy;

  for (int i = 0; i < figure->sprite_size; i++) {
    figure->sprite[i].position.x += dx;
    figure->sprite[i].position.y += dy;
  }
}

// void draw_rectangle(Rectangle *rectangle) {
//   for (int j = 0; j < HEIGHT; j++) {
//     for (int i = 0; i < WIDTH; i++) {
//       int h = fabs(rectangle->position.x - i) <= rectangle->width/2 - 1;
//       int v = fabs(rectangle->position.y - j) <= rectangle->height/2 - 1;
//       int h_border = fabs(rectangle->position.x - i) <= rectangle->width/2;
//       int v_border = fabs(rectangle->position.y - j) <= rectangle->height/2;
//       // fill
//       if (h && v) {
//         paint_pixel(i, j, rectangle->color);
//       }
//       // edge
//       if ((h_border && v_border) && !(h && v)) {
//         paint_pixel(i, j, GREEN);
//       }
//     }
//   }
// }

void draw_circle(Circle *circle) {
  for (int j = 0; j < HEIGHT; j++) {
    for (int i = 0; i < WIDTH; i++) {
      double x_sq = (circle->position.x - i)*(circle->position.x - i);
      double y_sq = (circle->position.y - j)*(circle->position.y - j);
      double r_sq = circle->radius*circle->radius;
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

void move_point(Object *point_ptr, double delta_time) {
  _Point *point = &point_ptr->point_t;

  point->position.x += point->velocity.x * delta_time;
  point->position.y -= point->velocity.y * delta_time;
}

void window_borders_collision(Object *point_ptr, double width, double height) {
  _Point *point = &point_ptr->point_t;

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
  0,
  CIRCLE,
  WHITE,
  20
};

Circle ball2 = {
  {40, 40},
  {-53, -27},
  0,
  0,
  CIRCLE,
  WHITE,
  20
};

// Called every frame
void render_callback(double delta_time) {
  draw_circle(&ball2);

  window_borders_collision((Object *)&ball, ball.radius*2, ball.radius*2);
  window_borders_collision((Object *)&ball2, ball2.radius*2, ball2.radius*2);

  move_figure((Object *)&ball, delta_time);
  move_point((Object *)&ball2, delta_time);
}

int main(int argc, char *argv[]) {
  ball.sprite = create_sprite(
    ball.radius * 2,
    ball.radius * 2,
    &ball.sprite_size,
    (Object *)&ball,
    draw_circle_sprite
  );

  int exit_code = render(render_callback);
  return exit_code;
}
