#pragma once

#include "fonts/gfxfont.h"

int8_t kdisp_write_gfx_char(const GFXfont **fonts, uint8_t num_fonts, int8_t x, int8_t y, uint16_t c);

void kdisp_write_gfx_text(const GFXfont **fonts, uint8_t num_fonts, int8_t x, int8_t y, const uint16_t *text);

void kdisp_write_base_char(int8_t x, int8_t y, char c);

void kdisp_draw_bitmap(int8_t x, int8_t y, const uint8_t pgm_bmp[], int8_t bmp_width, int8_t bmp_height);

void kdisp_set_buffer(uint8_t vertical_pixel_row_of_8_pixels);

void kdisp_send_buffer(void);

void kdisp_invert(bool invert);

void kdisp_scroll(bool activate);

void kdisp_scroll_modev(bool left, uint8_t vspeed0to7);
void kdisp_scroll_modevh(bool left, uint8_t vspeed0to7, uint8_t hoffset0to63);
void kdisp_scroll_vlines(uint8_t lines0to63);

void kdisp_set_contrast(uint8_t contrast);

void kdisp_enable(bool enable);

void kdisp_hw_setup(void);

void kdisp_init(const int8_t num_shift_regs);

void kdisp_setup(bool turn_on);
