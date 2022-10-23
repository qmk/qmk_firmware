// Copyright 2021 Nicolas Druoton (druotoni)
// Copyright 2021 ugfx
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// line
void drawline_vb(uint8_t x, uint8_t y, uint8_t width, bool color);
void drawline_vt(uint8_t x, uint8_t y, uint8_t width, bool color);
void drawline_hr(uint8_t x, uint8_t y, uint8_t width, bool color);
void drawline_hl(uint8_t x, uint8_t y, uint8_t width, bool color);
void drawline_hr_heigth(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, bool color);

// rectangle
void draw_rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, bool color);
void draw_rectangle_fill(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, bool color);
void draw_gradient(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, uint8_t color_start, uint8_t color_end, uint8_t tres);

// circle
void draw_fill_circle(short x, short y, uint8_t radius, bool color);
void draw_circle(uint8_t x, uint8_t y, uint8_t radius, bool color);
void draw_ellipse(uint8_t x, uint8_t y, uint8_t a, uint8_t b, bool color);
void draw_ellipse_fill(uint8_t x, uint8_t y, uint8_t a, uint8_t b, bool color);
void draw_arc_sector(uint8_t x, uint8_t y, uint8_t radius, unsigned char sectors, unsigned char half, bool color);
void draw_static(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, int color, uint8_t density);

// text
void draw_random_char(uint8_t column, uint8_t row, char final_char, int value, uint8_t style);
void draw_label(const char *data, uint8_t len, uint8_t row, int value);
void draw_box(const char *data, uint8_t len, uint8_t row, long value, uint8_t style);
void draw_progress(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, int value, uint8_t style, bool color);

// oled drivers stuff
char get_oled_char(uint16_t start_index);
void oled_write_cursor(uint8_t col, uint8_t line, const char *data, bool invert);
void oled_write_raw_P_cursor(uint8_t col, uint8_t line, const char *data, uint16_t size);

// pixel manipulation
void copy_pixel(int from, int shift, unsigned char mask);
void move_block(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, int shift);
void draw_glitch_comb(uint8_t x, uint8_t y, uint8_t width, uint16_t height, uint8_t iSize, bool odd);

// misc
void render_tv_animation(uint8_t frame_number, uint8_t x, uint8_t y, uint8_t width, uint8_t heigth);
int  interpo_pourcent(int min, int max, int v);
void get_glitch_index(uint32_t *glitch_timer, int *current_glitch_scope_time, uint8_t *glitch_index, uint8_t min_time, uint16_t max_time, uint8_t glitch_probobility, uint8_t glitch_frame_number);
void get_glitch_index_new(uint16_t *glitch_timer, uint8_t *current_glitch_scope_time, uint8_t *glitch_index, uint8_t min_time, uint16_t max_time, uint8_t glitch_probobility, uint8_t glitch_frame_number);
