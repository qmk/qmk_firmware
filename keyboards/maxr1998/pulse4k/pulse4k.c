/*
Copyright (C) 2019  Maxr1998 <max.rumpf1998@gmail.com>

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

#include "pulse4k.h"
#include "rgblight.h"

enum combo_events {
    LED_ADJUST
};

const uint16_t PROGMEM led_adjust_combo[] = {KC_LEFT, KC_RGHT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [LED_ADJUST] = COMBO_ACTION(led_adjust_combo)
};

bool led_adjust_active = false;

void process_combo_event(uint8_t combo_index, bool pressed) {
    if (combo_index == LED_ADJUST) {
        led_adjust_active = pressed;
    }
}

void encoder_update_kb(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (led_adjust_active) {
            if (clockwise) {
                rgblight_increase_val();
            } else {
                rgblight_decrease_val();
            }
        } else encoder_one_update(clockwise);
    } else if (index == 1) {
        if (led_adjust_active) {
            if (clockwise) {
                rgblight_increase_hue();
            } else {
                rgblight_decrease_hue();
            }
        } else encoder_two_update(clockwise);
    }
}

__attribute__((weak)) void encoder_one_update(bool clockwise) {
    if (clockwise) {
        tap_code(KC_PGDN);
    } else {
        tap_code(KC_PGUP);
    }
}

__attribute__((weak)) void encoder_two_update(bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
}
