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

  while (node->next != NULL) {
    double width = 0;
    double height = 0;

    switch (node->sprite->figure_sprite_t.shape) {
      case CIRCLE:
        width = height = node->sprite->circle_t.radius * 2;
        break;
      case RECTANGLE:
        width = node->sprite->rectangle_t.width;
        height = node->sprite->rectangle_t.height;
        break;
    }

    // window_borders_collision(node->sprite, width, height);
    // translate_sprite(node->sprite, delta_time);

    render_rectangle((Rectangle_sprite *)node->sprite);
    window_borders_collision((Object_sprite *)node->sprite, width, height);
    move_point((Object_sprite *)node->sprite, delta_time);

    node = node->next;
  }
}

int main(int argc, char *argv[]) {
  init_sprite_list();

  for (int i = 0; i < 10; i++) {
    Rectangle_sprite *rectangle = malloc(sizeof(Rectangle_sprite));
    rectangle->position.x = 20 + 8*i;
    rectangle->position.y = 20 + 8*i;
    rectangle->velocity.x = 50;
    rectangle->velocity.y = 50;
    rectangle->shape = RECTANGLE;
    rectangle->sprite_arr = 0;
    rectangle->sprite_size = 0;
    rectangle->color = WHITE;
    rectangle->width = 20;
    rectangle->height = 10;
    add_sprite(sprite_list, (Object_sprite *)rectangle);
    // rectangle->sprite_arr = create_sprite(
    //   rectangle->width,
    //   rectangle->height,
    //   (Object_sprite *)rectangle,
    //   draw_rectangle_sprite
    // );

    // Circle_sprite *ball = (Circle_sprite *)malloc(sizeof(Circle_sprite));
    // ball->position.x = 20 + 15 * i;
    // ball->position.y = 20 + 15 * i;
    // ball->velocity.x = 40;
    // ball->velocity.y = 40;
    // ball->shape = CIRCLE;
    // ball->color = WHITE;
    // ball->radius = 15;
    // ball->sprite_arr = create_sprite(
    //   ball->radius * 2,
    //   ball->radius * 2,
    //   (Object_sprite *)ball,
    //   draw_circle_sprite
    // );
  }

  int exit_code = render(render_callback);
  return exit_code;
}
