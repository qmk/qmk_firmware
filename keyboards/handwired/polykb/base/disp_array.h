#pragma once

#include "fonts/gfxfont.h"

uint8_t kdisp_write_gfx_char(const GFXfont **fonts, uint8_t num_fonts, int16_t x, int16_t y, uint16_t c);

void kdisp_write_gfx_text(const GFXfont **fonts, uint8_t num_fonts, int16_t x, int16_t y, const uint16_t *text);

void kdisp_write_base_char(uint16_t x, uint16_t y, char c);

void kdisp_draw_bitmap(uint16_t x, uint16_t y, const uint8_t pgm_bmp[], uint8_t bmp_width, uint8_t bmp_height);

void kdisp_set_buffer(uint8_t vertical_pixel_row_of_8_pixels);

void kdisp_send_buffer(void);

void kdisp_invert(bool invert);

void kdisp_set_contrast(uint8_t contrast);

void kdisp_enable(bool enable);

void kdisp_hw_setup(void);

void kdisp_init(const int8_t num_shift_regs, bool turn_on);
