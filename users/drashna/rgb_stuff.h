/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#if defined(RGBLIGHT_TWINKLE)
typedef struct {
    bool     enabled;
    uint8_t  hue;
    uint16_t timer;
    uint8_t  life;
} rgblight_fadeout;
#endif

bool          process_record_user_rgb_light(uint16_t keycode, keyrecord_t *record);
void          keyboard_post_init_rgb_light(void);
void          matrix_scan_rgb_light(void);
layer_state_t layer_state_set_rgb_light(layer_state_t state);
layer_state_t default_layer_state_set_rgb_light(layer_state_t state);
void          rgblight_sethsv_default_helper(uint8_t index);

#if defined(RGBLIGHT_TWINKLE)
void scan_rgblight_fadeout(void);
#endif
