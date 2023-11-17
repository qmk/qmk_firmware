// Copyright 2023 KiwiKey
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void oled_pan_area(char start_x, char end_x, char start_y, char end_y, bool left);
void draw_line_h(uint8_t x, uint8_t y, uint8_t len, bool on);
void draw_line_v(uint8_t x, uint8_t y, uint8_t len, bool on);
void draw_rect(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, bool on);
