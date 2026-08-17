#include <stdint.h>
#include "framebuffer.h"

uint32_t framebuffer[WIDTH * HEIGHT];

void clear_framebuf(uint32_t color) {
  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    framebuffer[i] = color;
  }
}

void paint_pixel(uint32_t x, uint32_t y, uint32_t color) {
  framebuffer[WIDTH * y + x] = color;
}

uint32_t get_pixel_color(uint32_t x, uint32_t y) {
  return framebuffer[WIDTH * y + x];
}
