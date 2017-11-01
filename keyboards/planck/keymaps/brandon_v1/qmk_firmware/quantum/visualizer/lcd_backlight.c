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

#include "lcd_backlight.h"
#include <math.h>

static uint8_t current_hue = 0x00;
static uint8_t current_saturation = 0x00;
static uint8_t current_intensity = 0xFF;
static uint8_t current_brightness = 0x7F;

void lcd_backlight_init(void) {
    lcd_backlight_hal_init();
    lcd_backlight_color(current_hue, current_saturation, current_intensity);
}

// This code is based on Brian Neltner's blogpost and example code
// "Why every LED light should be using HSI colorspace".
// http://blog.saikoled.com/post/43693602826/why-every-led-light-should-be-using-hsi
static void hsi_to_rgb(float h, float s, float i, uint16_t* r_out, uint16_t* g_out, uint16_t* b_out) {
    unsigned int r, g, b;
    h = fmodf(h, 360.0f); // cycle h around to 0-360 degrees
    h = 3.14159f * h / 180.0f; // Convert to radians.
    s = s > 0.0f ? (s < 1.0f ? s : 1.0f) : 0.0f; // clamp s and i to interval [0,1]
    i = i > 0.0f ? (i < 1.0f ? i : 1.0f) : 0.0f;

    // Math! Thanks in part to Kyle Miller.
    if(h < 2.09439f) {
        r = 65535.0f * i/3.0f *(1.0f + s * cos(h) / cosf(1.047196667f - h));
        g = 65535.0f * i/3.0f *(1.0f + s *(1.0f - cosf(h) / cos(1.047196667f - h)));
        b = 65535.0f * i/3.0f *(1.0f - s);
    } else if(h < 4.188787) {
        h = h - 2.09439;
        g = 65535.0f * i/3.0f *(1.0f + s * cosf(h) / cosf(1.047196667f - h));
        b = 65535.0f * i/3.0f *(1.0f + s * (1.0f - cosf(h) / cosf(1.047196667f - h)));
        r = 65535.0f * i/3.0f *(1.0f - s);
    } else {
        h = h - 4.188787;
        b = 65535.0f*i/3.0f * (1.0f + s * cosf(h) / cosf(1.047196667f - h));
        r = 65535.0f*i/3.0f * (1.0f + s * (1.0f - cosf(h) / cosf(1.047196667f - h)));
        g = 65535.0f*i/3.0f * (1.0f - s);
    }
    *r_out = r > 65535 ? 65535 : r;
    *g_out = g > 65535 ? 65535 : g;
    *b_out = b > 65535 ? 65535 : b;
}

void lcd_backlight_color(uint8_t hue, uint8_t saturation, uint8_t intensity) {
    uint16_t r, g, b;
    float hue_f = 360.0f * (float)hue / 255.0f;
    float saturation_f = (float)saturation / 255.0f;
    float intensity_f = (float)intensity / 255.0f;
    intensity_f *= (float)current_brightness / 255.0f;
    hsi_to_rgb(hue_f, saturation_f, intensity_f, &r, &g, &b);
	current_hue = hue;
	current_saturation = saturation;
	current_intensity = intensity;
	lcd_backlight_hal_color(r, g, b);
}

void lcd_backlight_brightness(uint8_t b) {
    current_brightness = b;
    lcd_backlight_color(current_hue, current_saturation, current_intensity);
}
