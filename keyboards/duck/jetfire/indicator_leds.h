#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "duck_led/duck_led.h"

void backlight_init_ports(void);
void backlight_set_state(bool cfg[7]);
void backlight_update_state(void);
void backlight_toggle_rgb(bool enabled);
void backlight_set_rgb(uint8_t cfg[RGBLIGHT_LED_COUNT][3]);
void backlight_set(uint8_t level);
void send_color(uint8_t r, uint8_t g, uint8_t b, enum Device device);
