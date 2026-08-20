#include <string.h>
#include <stdint.h>
#include "framebuffer.h"

uint32_t framebuffer[WIDTH * HEIGHT];

void clear_framebuf(uint32_t color) {
  memset(framebuffer, color, sizeof(framebuffer));
}

void paint_pixel(uint32_t x, uint32_t y, uint32_t color) {
  framebuffer[WIDTH * y + x] = color;
}
