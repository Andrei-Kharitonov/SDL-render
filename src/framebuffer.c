#include <stdint.h>
#include "../include/framebuffer.h"
#include "../include/types.h"

uint32_t framebuffer[WIDTH * HEIGHT];

Sprite_pixel *sprites[1024];
int sprite_sizes[1024];
int sprites_index = 0;

void clear_framebuf(uint32_t color) {
  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    framebuffer[i] = color;
  }
}

void paint_pixel(uint32_t x, uint32_t y, uint32_t color) {
  framebuffer[WIDTH * y + x] = color;
}

void add_sprite(Sprite_pixel sprite[], int sprite_size) {
  sprites[sprites_index] = sprite;
  sprite_sizes[sprites_index] = sprite_size;
  sprites_index++;
}

void render_sprites() {
  for (int i = 0; i < sprites_index; i++) {
    Sprite_pixel *sprite = sprites[i];
    if (!sprite) continue;

    for (int j = 0; j < sprite_sizes[i]; j++) {
      int x = sprite[j].position.x;
      int y = sprite[j].position.y;
      if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT)) {
        paint_pixel(x, y, sprite[j].color);
      }
    }
  }
}
