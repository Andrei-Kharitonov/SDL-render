#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include "consts.h"

extern uint32_t framebuffer[WIDTH * HEIGHT];

void clear_framebuf(uint32_t color);

void paint_pixel(uint32_t x, uint32_t y, uint32_t color);

#endif
