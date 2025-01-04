/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2015 ZSA Technology Labs Inc (@zsa)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "quantum.h"

void planck_ez_right_led_on(void);
void planck_ez_right_led_off(void);
void planck_ez_right_led_level(uint8_t level);
void planck_ez_left_led_on(void);
void planck_ez_left_led_off(void);
void planck_ez_left_led_level(uint8_t level);

enum planck_ez_keycodes {
    LED_LEVEL = QK_KB_0,
    TOGGLE_LAYER_COLOR,
};

#ifndef WEBUSB_ENABLE
#    define WEBUSB_PAIR KC_NO
#endif

typedef union {
  uint32_t raw;
  struct {
    uint8_t      led_level :3;
    bool         disable_layer_led   :1;
    bool         rgb_matrix_enable   :1;
  };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;
