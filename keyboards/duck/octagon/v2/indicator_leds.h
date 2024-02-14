#pragma once

#include "duck_led/duck_led.h"

void indicator_leds_set(bool leds[7]);
void backlight_toggle_rgb(bool enabled);
void backlight_set_rgb(uint8_t cfg[17][3]);
void backlight_init_ports(void);
void send_color(uint8_t r, uint8_t g, uint8_t b, enum Device device);
