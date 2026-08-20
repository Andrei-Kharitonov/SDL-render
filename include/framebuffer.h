#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include "types.h"

#define WIDTH 320
#define HEIGHT 200
#define SCALE 4
#define FPS_CAP 60

#define WHITE 0xFFFFFF00
#define BLACK 0x00000000
#define RED 0xFF000000
#define GREEN 0x00FF0000
#define BLUE 0x0000FF00

typedef struct Sprite_list_node {
  Sprite_pixel *sprite;
  uint32_t sprite_size;
  struct Sprite_list_node *next;
} Sprite_list_node;

extern uint32_t framebuffer[WIDTH * HEIGHT];

extern Sprite_list_node *sprite_list_root;

void clear_framebuf(uint32_t color);

void paint_pixel(uint32_t x, uint32_t y, uint32_t color);

Sprite_list_node *add_sprite(Sprite_list_node *head, Sprite_pixel *sprite, uint32_t size);

void render_sprites(void);

#endif
