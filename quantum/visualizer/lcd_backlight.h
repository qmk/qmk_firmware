/*
The MIT License (MIT)

Copyright (c) 2016 Fred Sundvik

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef LCD_BACKLIGHT_H_
#define LCD_BACKLIGHT_H_
#include "stdint.h"

// Helper macros for storing hue, staturation and intensity as unsigned integers
#define LCD_COLOR(hue, saturation, intensity) (hue << 16 | saturation << 8 | intensity)
#define LCD_HUE(color) ((color >> 16) & 0xFF)
#define LCD_SAT(color) ((color >> 8) & 0xFF)
#define LCD_INT(color) (color & 0xFF)

static inline uint32_t change_lcd_color_intensity(uint32_t color, uint8_t new_intensity) {
    return (color & 0xFFFFFF00) | new_intensity;
}

void lcd_backlight_init(void);
void lcd_backlight_color(uint8_t hue, uint8_t saturation, uint8_t intensity);
void lcd_backlight_brightness(uint8_t b);
uint8_t lcd_get_backlight_brightness(void);

void lcd_backlight_hal_init(void);
void lcd_backlight_hal_color(uint16_t r, uint16_t g, uint16_t b);

#endif /* LCD_BACKLIGHT_H_ */
