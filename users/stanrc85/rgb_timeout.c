/*
Copyright 2021 Stanrc85

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "stanrc85.h"

// Backlight timeout feature
// Modified from https://www.reddit.com/r/MechanicalKeyboards/comments/ix65z0/looking_for_qmk_led_idle_timeout_info/g64yov7/
#define BACKLIGHT_TIMEOUT 10 // in minutes
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool led_on = true;
static bool rgb_on = true;
static bool rgb_was_on = false;

void matrix_scan_user(void) {
  // idle_timer needs to be set one time
    if (idle_timer == 0) idle_timer = timer_read();
        if ( (led_on && timer_elapsed(idle_timer) > 30000) || (rgb_on && timer_elapsed(idle_timer) > 30000)) {
            halfmin_counter++;
            idle_timer = timer_read();
        }

        if ( (led_on && halfmin_counter >= BACKLIGHT_TIMEOUT * 2) || (rgb_on && halfmin_counter >= BACKLIGHT_TIMEOUT * 2)) {
            if(rgblight_is_enabled()) {
                rgb_was_on = true;
                rgblight_disable_noeeprom();
                led_on = false;
                rgb_on = false;
            } else {
                rgb_was_on = false;
            }
            halfmin_counter = 0;
        }
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
            if (led_on == false || rgb_on == false ) {
                if (rgb_was_on) {
                    rgblight_enable_noeeprom();
                    led_on = true;
                    rgb_on = true;
                }
            }
        idle_timer = timer_read();
        halfmin_counter = 0;
    }
    return true;
}
