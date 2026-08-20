#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "types.h"
#include "framebuffer.h"

uint32_t framebuffer[WIDTH * HEIGHT];

Sprite_list_node *sprite_list_root;

void clear_framebuf(uint32_t color) {
  memset(framebuffer, color, sizeof(framebuffer));
}

void paint_pixel(uint32_t x, uint32_t y, uint32_t color) {
  framebuffer[WIDTH * y + x] = color;
}

Sprite_list_node *add_sprite(
  Sprite_list_node *start_node,
  Sprite_pixel *sprite,
  uint32_t size
) {
  Sprite_list_node *node = start_node;

  while (node->next != NULL) {
    node = node->next;
  }

  node->sprite = sprite;
  node->sprite_size = size;
  node->next = malloc(sizeof(Sprite_list_node));

  return node;
}

void render_sprites() {
  Sprite_list_node *node = sprite_list_root;

  if (node == NULL) {
    return;
  }

  while (node->next != NULL) {
    for (int j = 0; j < node->sprite_size; j++) {
      int x = node->sprite[j].position.x;
      int y = node->sprite[j].position.y;
      if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT)) {
        paint_pixel(x, y, node->sprite[j].color);
      }
    }

    node = node->next;
  }
}
