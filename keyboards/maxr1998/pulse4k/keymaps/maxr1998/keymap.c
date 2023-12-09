/*
 * Copyright (C) 2020  Maxr1998 <max.rumpf1998@gmail.com>
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

#include QMK_KEYBOARD_H

enum layers {
    DEFAULT
};

enum combo_events {
    LED_ADJUST
};

const uint16_t PROGMEM led_adjust_combo[] = {KC_F22, KC_F24, COMBO_END};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT(
        KC_F20,  KC_F21,  KC_MUTE,
        KC_F22,  KC_F23,  KC_F24
    )
};

combo_t key_combos[] = {
    [LED_ADJUST] = COMBO_ACTION(led_adjust_combo)
};

bool led_adjust_active = false;

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (combo_index == LED_ADJUST) {
        led_adjust_active = pressed;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (led_adjust_active) {
            if (clockwise) {
                rgblight_increase_val();
            } else {
                rgblight_decrease_val();
            }
            return false;
        }
    } else if (index == 1) {
        if (led_adjust_active) {
            if (clockwise) {
                rgblight_increase_hue();
            } else {
                rgblight_decrease_hue();
            }
            return false;
        }
    }

    return true;
}

void encoder_one_update(bool clockwise) {
    tap_code(!clockwise ? KC_F18 : KC_F19);
}
