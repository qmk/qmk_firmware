#pragma once

#include "hsv2rgb.h"

void set_leds_color_hsv(hsv_color color);
void set_leds_color_rgb(rgb_color color);
void set_led_color_hsv(hsv_color color, int pos);
void set_led_color_rgb(rgb_color color, int pos);

void leds_init(void);
