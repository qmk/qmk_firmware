// Copyright 2023 Chris H <chris@zoid.com.au>
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdint.h>

void backlight_init(void);
void backlight_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void backlight_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
void backlight_flush(void);
