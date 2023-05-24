/* Copyright 2021 Harrison Chan (Xelus)
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

#include "la_plus.h"
#include "print.h"

#define _____ NO_LED

keyboard_config_t keyboard_config;

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____ }, \
  { _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____ }, \
  { _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____ }, \
  { _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____ }, \
  { _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____ }  \
}, {
  // LED Index to Physical Position
    {  2, 38 },
    {  0, 31 },
    {  2, 24 },
    {  0, 17 },
    {  2, 10 },
    {  0, 4  },
    {  4, 1  },
    { 14, 1  },
    { 30, 1  },
    { 47, 1  },
    { 63, 1  },
    { 79, 1  },
    { 95, 1  },
    {111, 1  },
    {144, 1  },
    {159, 1  },
    {176, 1  },
    {192, 1  },
    {208, 1  },
    {224, 1  },
    {241, 1  },
    {250, 0  },
    {255, 4  },
    {253, 10 },
    {255, 17 },
    {253, 24 },
    {255, 31 },
    {253, 38 },
    {241, 64 },
    {165, 64 },
    { 90, 64 },
    { 14, 64 }
}, {
  // LED Index to Flag
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8
} };

void keyboard_post_init_kb(void) {
    // Call the post init code.
    // debug_enable=true;

    keyboard_config.raw = eeconfig_read_kb();
    if (keyboard_config.startup_animation_dots) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_startup_animation_dots);
    } else {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_startup_animation_solid);
    }

    keyboard_post_init_user();
}

void eeconfig_init_kb(void) {
#ifdef STARTUP_ANIMATION_DOTS
    keyboard_config.startup_animation_dots = false;
#else
    keyboard_config.startup_animation_dots = true;
#endif
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    if (keycode == STARTUP_ANIMATION_CONFIG && record->event.pressed) {
        keyboard_config.startup_animation_dots = !(keyboard_config.startup_animation_dots);
#ifdef CONSOLE_ENABLE
        uprintf("keyboard_config startup_animation_dots: %b\n", keyboard_config.startup_animation_dots);
#endif
        eeconfig_update_kb(keyboard_config.raw);
    }

    return true;
}
