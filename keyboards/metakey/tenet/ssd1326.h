// Copyright 2026 Connor Gallopo (@connorgallopo)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

// SSD1326 256x32 mono OLED, I2C0 (PB0 SDA / PB1 SCL, AFIO mode 7,
// PD1 active-low RST). 7-bit device address 0x3C.

#define SSD1326_WIDTH  256
#define SSD1326_HEIGHT 32

void ssd1326_init(void);
void ssd1326_send_command(uint8_t cmd);
void ssd1326_send_data(const uint8_t *data, uint16_t len);
void ssd1326_clear(void);
void ssd1326_render(void);
void ssd1326_render_mono(const uint8_t *framebuf);
void ssd1326_fb_pixel(uint16_t x, uint8_t y, bool on);
void ssd1326_fb_char(uint16_t x, uint8_t y, char c, uint8_t scale);
void ssd1326_fb_string(uint16_t x, uint8_t y, const char *str, uint8_t scale);
void ssd1326_set_text(const char *text);
