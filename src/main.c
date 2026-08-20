#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "framebuffer.h"
#include "objects.h"
#include "render.h"
#include "types.h"

int draw_circle_sprite(Sprite_pixel sprite[], Object_sprite *circle_ptr) {
  Circle_sprite *circle = &circle_ptr->circle_t;
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
  Object_sprite *figure_sprite,
  int (*draw_sprite)(Sprite_pixel [], Object_sprite *)
) {
  enum shapes shape = figure_sprite->figure_sprite_t.shape;

  int sprite_size = width * height; // max sprite size
  if (shape != RECTANGLE) sprite_size++;

  Sprite_pixel *sprite = malloc(sizeof(Sprite_pixel) * sprite_size);

  if (!sprite) {
    printf("Sprite memory allocation error\n");
    return 0;
  }

  sprite_size = draw_sprite(sprite, figure_sprite); // actual size
  if (shape != RECTANGLE) {
    sprite = realloc(sprite, sizeof(Sprite_pixel) * sprite_size);
  }

  if (!sprite) {
    printf("Sprite memory reallocation error\n");
    return 0;
  }

  figure_sprite->figure_sprite_t.sprite_size = sprite_size;
  add_sprite(sprite_list, figure_sprite);
  
  return sprite;
}

void move_figure_sprite(Object_sprite *figure_sprite_ptr, double delta_time) {
  _Figure_sprite *figure_sprite = &figure_sprite_ptr->figure_sprite_t;

  double dx = figure_sprite->velocity.x * delta_time;
  double dy = figure_sprite->velocity.y * delta_time;

  figure_sprite->position.x += dx;
  figure_sprite->position.y -= dy;

  for (int i = 0; i < figure_sprite->sprite_size; i++) {
    figure_sprite->sprite_arr[i].position.x += dx;
    figure_sprite->sprite_arr[i].position.y -= dy;
  }
}

void draw_rectangle(Rectangle_sprite *rectangle) {
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

void draw_circle(Circle_sprite *circle) {
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

void move_point(Object_sprite *point_ptr, double delta_time) {
  _Point *point = &point_ptr->point_t;

  point->position.x += point->velocity.x * delta_time;
  point->position.y -= point->velocity.y * delta_time;
}

void window_borders_collision(Object_sprite *point_ptr, double width, double height) {
  _Point *point = &point_ptr->point_t;

  int is_left = point->position.x - width/2 <= 0;
  int is_right = point->position.x + width/2 >= WIDTH;
  int is_top = point->position.y - height/2 <= 0;
  int is_bottom = point->position.y + height/2 >= HEIGHT;

  if (is_left || is_right) point->velocity.x = -point->velocity.x;
  if (is_top || is_bottom) point->velocity.y = -point->velocity.y;
}

// Called every frame
void render_callback(double delta_time) {
  Sprite_list_node *node = sprite_list;

  for (int i = 0; i < 20; i++) {
    double width = 0;
    double height = 0;

    switch (node->sprite->figure_sprite_t.shape) {
      case CIRCLE:
        width = node->sprite->circle_t.radius * 2;
        height = node->sprite->circle_t.radius * 2;
        break;
      case RECTANGLE:
        width = node->sprite->rectangle_t.width;
        height = node->sprite->rectangle_t.height;
        break;
    }

    if (i < 10) {
      // sprite render
      window_borders_collision(node->sprite, width, height);
      move_figure_sprite(node->sprite, delta_time);
    } else {
      // screen render
      window_borders_collision(node->sprite, width, height);
      draw_circle(&node->sprite->circle_t);
      move_point(node->sprite, delta_time);
    }

    node = node->next;
  }
}

int main(int argc, char *argv[]) {
  init_sprite_list();

  // sprite render
  for (int i = 1; i < 11; i++) {
    Circle_sprite *ball = (Circle_sprite *)malloc(sizeof(Circle_sprite));

    ball->position.x = 20 * i;
    ball->position.y = 80 + 4 * i;
    ball->velocity.x = 50;
    ball->velocity.y = 50;
    ball->shape = CIRCLE;
    ball->color = WHITE;
    ball->radius = 6;
    ball->sprite_arr = 0;
    ball->sprite_size = 0;

    ball->sprite_arr = create_sprite(
      ball->radius * 2,
      ball->radius * 2,
      (Object_sprite *)ball,
      draw_circle_sprite
    );
  }

  // screen render
  for (int i = 1; i < 11; i++) {
    Circle_sprite *ball = (Circle_sprite *)malloc(sizeof(Circle_sprite));

    ball->position.x = 20 * i;
    ball->position.y = 20 + 4 * i;
    ball->velocity.x = 50;
    ball->velocity.y = 50;
    ball->shape = CIRCLE;
    ball->color = WHITE;
    ball->radius = 6;
    ball->sprite_arr = 0;
    ball->sprite_size = 0;

    add_sprite(sprite_list, (Object_sprite *)ball);
  }

  int exit_code = render(render_callback);
  return exit_code;
}
