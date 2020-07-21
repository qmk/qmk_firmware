#pragma once
#include <stdbool.h>
#include "timer.h"
#include "progmem.h"
#include "oled_driver.h"
#include "lib/lib8tion/lib8tion.h"
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

#define COLLISION_MASK_LEFT (1 << 3)
#define COLLISION_MASK_DOWN (1 << 2)
#define COLLISION_MASK_UP (1 << 1)
#define COLLISION_MASK_RIGHT (1 << 0)

uint8_t rect_out_of_bounds(int16_t x, int16_t y, uint8_t width, uint8_t height, int8_t padding);

bool point_out_of_bounds(int16_t x, int16_t y, int8_t padding);

void oled_write_bitmap(const uint8_t* data, int16_t x, int16_t y, uint8_t width, uint8_t height, bool erase);
