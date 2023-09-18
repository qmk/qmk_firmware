// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

bool          process_record_user_rgb_light(uint16_t keycode, keyrecord_t *record);
void          keyboard_post_init_rgb_light(void);
void          matrix_scan_rgb_light(void);
layer_state_t layer_state_set_rgb_light(layer_state_t state);
layer_state_t default_layer_state_set_rgb_light(layer_state_t state);
void          rgblight_sethsv_default_helper(uint8_t index);

const char* rgblight_name(uint8_t effect);
bool is_rgblight_startup_running(void);
