// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record);
void keyboard_post_init_rgb_matrix(void);
void housekeeping_task_rgb_matrix(void);

void rgb_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type, uint8_t led_min, uint8_t led_max);

bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);
bool rgb_matrix_indicators_keymap(void);
