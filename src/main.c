#include <stdint.h>
#include <stdlib.h>
#include "consts.h"
#include "lists.h"
#include "render.h"
#include "sprites.h"
#include "draw.h"

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
      translate_sprite(node->sprite, delta_time);
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
