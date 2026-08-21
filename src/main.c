#include <stdio.h>
#include <stdlib.h>
#include "consts.h"
#include "lists.h"
#include "render.h"
#include "sprites.h"
#include "render_figures.h"

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

  while (node->next != NULL) {
    double width = 0;
    double height = 0;
    Object_sprite *sprite = node->sprite;

    switch (node->sprite->figure_sprite_t.shape) {
      case CIRCLE:
        width = height = node->sprite->circle_t.radius * 2;

        if (node->sprite->figure_sprite_t.sprite_arr == NULL) {
          render_circle(&node->sprite->circle_t);
        }

        break;
      case RECTANGLE:
        width = node->sprite->rectangle_t.width;
        height = node->sprite->rectangle_t.height;

        if (node->sprite->figure_sprite_t.sprite_arr == NULL) {
          render_rectangle(&node->sprite->rectangle_t);
        }

        break;
    }

    if (node->sprite->figure_sprite_t.sprite_arr == NULL) {
      move_point(node->sprite, delta_time);
    } 
    if (node->sprite->circle_t.sprite_arr != NULL) {
      render_sprite((_Figure_sprite *)node->sprite);
      translate_sprite(node->sprite, delta_time);
    }

    window_borders_collision(node->sprite, width, height);

    node = node->next;
  }
}

int main(int argc, char *argv[]) {
  init_sprite_list();

  // creating sprite once
  Rectangle_sprite *rectangle_s = malloc(sizeof(Rectangle_sprite));
  rectangle_s->position.x = 90;
  rectangle_s->position.y = 20;
  rectangle_s->velocity.x = 20;
  rectangle_s->velocity.y = 50;
  rectangle_s->shape = RECTANGLE;
  rectangle_s->color = WHITE;
  rectangle_s->width = 25;
  rectangle_s->height = 15;
  rectangle_s->sprite_arr = create_sprite(
    rectangle_s->width,
    rectangle_s->height,
    (Object_sprite *)rectangle_s,
    draw_rectangle_sprite
  );

  Circle_sprite *ball_s = malloc(sizeof(Circle_sprite));
  ball_s->position.x = 100;
  ball_s->position.y = 90;
  ball_s->velocity.x = 35;
  ball_s->velocity.y = 20;
  ball_s->shape = CIRCLE;
  ball_s->color = WHITE;
  ball_s->radius = 18.2;
  ball_s->sprite_arr = create_sprite(
    ball_s->radius * 2,
    ball_s->radius * 2,
    (Object_sprite *)ball_s,
    draw_circle_sprite
  );

  // calculating sprite every frame
  Rectangle_sprite *rectangle_r = malloc(sizeof(Rectangle_sprite));
  rectangle_r->position.x = 20;
  rectangle_r->position.y = 20;
  rectangle_r->velocity.x = 30;
  rectangle_r->velocity.y = 20;
  rectangle_r->shape = RECTANGLE;
  rectangle_r->sprite_arr = 0;
  rectangle_r->sprite_size = 0;
  rectangle_r->color = WHITE;
  rectangle_r->width = 12;
  rectangle_r->height = 33;
  add_sprite(sprite_list, (Object_sprite *)rectangle_r);

  Circle_sprite *ball_r = malloc(sizeof(Circle_sprite));
  ball_r->position.x = 20;
  ball_r->position.y = 90;
  ball_r->velocity.x = 40;
  ball_r->velocity.y = 40;
  ball_r->shape = CIRCLE;
  ball_r->sprite_arr = 0;
  ball_r->sprite_size = 0;
  ball_r->color = WHITE;
  ball_r->radius = 15.2;
  add_sprite(sprite_list, (Object_sprite *)ball_r);

  int exit_code = render(render_callback);
  return exit_code;
}
