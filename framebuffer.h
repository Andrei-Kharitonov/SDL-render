#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

#define WIDTH 320
#define HEIGHT 200
#define SCALE 4
#define FPS_CAP 60

#define WHITE 0xFFFFFF00
#define BLACK 0x00000000
#define RED 0xFF000000
#define GREEN 0x00FF0000
#define BLUE 0x0000FF00

extern uint32_t framebuffer[WIDTH * HEIGHT];

void clear_framebuf(uint32_t color);

void paint_pixel(uint32_t x, uint32_t y, uint32_t color);

uint32_t get_pixel_color(uint32_t x, uint32_t y);

#endif
