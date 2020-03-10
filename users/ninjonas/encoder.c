/* Copyright 2020 ninjonas
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
#include "ninjonas.h"

#ifdef ENCODER_ENABLE   
void left_encoder_cw(void) {
    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            tap_code16(SGUI(KC_TAB));
            break;
        case _RAISE:
            tap_code(KC_PGUP);
            break;
        case _ADJUST:
            rgblight_increase_hue();
            break;
        default:
            tap_code(KC_BRIU);
            break;
        }
}
void left_encoder_acw(void) {
    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            tap_code16(LGUI(KC_TAB));
            break;
        case _RAISE:
            tap_code(KC_PGDN);
            break;
        case _ADJUST:
            rgblight_decrease_hue();
            break;
        default:
            tap_code(KC_BRID);
            break;
        }
}
void right_encoder_cw(void) {
    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            tap_code(KC_UP);
            break;
        case _RAISE:
            tap_code16(LCTL(KC_TAB));
            break;
        case _ADJUST:
            rgblight_increase_val();
            break;
        default:
            tap_code(KC_VOLU);
            break;
        }
}
void right_encoder_acw(void) {
    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            tap_code(KC_DOWN);
            break;
        case _RAISE:
            tap_code16(LCTL(LSFT(KC_TAB)));
            break;
        case _ADJUST:
            rgblight_decrease_val();
            break;
        default:
            tap_code(KC_VOLD);
            break;
        }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    encoder_rotated_timer = timer_read();
    if (index == 0) {
        left_encoder_rotated = true;
        if (clockwise) {
            left_encoder_cw();
        } else {
            left_encoder_acw();
        }
    }
    else if (index == 1) {
        right_encoder_rotated = true;
        if (clockwise) {
            right_encoder_cw();
        } else {
            right_encoder_acw();
        }
    }
}

#endif