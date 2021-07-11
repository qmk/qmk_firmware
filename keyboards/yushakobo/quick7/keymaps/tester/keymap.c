/* Copyright 2020 yushakobo
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

#define FAVORITE_COLOR HSV_CYAN

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    YUSHAURL = SAFE_RANGE,
    KEY_00,
    KEY_01,
    KEY_02,
    KEY_10,
    KEY_11,
    KEY_12,
    KEY_20,
    KEY_21,
    KEY_22
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KEY_00, KEY_01, KEY_02,
        KEY_10, KEY_11, KEY_12,
        KEY_20, KEY_21, KEY_22
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KEY_00:
            if (record->event.pressed) {
                rgblight_sethsv_at(FAVORITE_COLOR, 0);
            } else {
                rgblight_sethsv_at(HSV_WHITE, 0);
            }
            break;
        case KEY_01:
            if (record->event.pressed) {
                rgblight_sethsv_at(FAVORITE_COLOR, 1);
            } else {
                rgblight_sethsv_at(HSV_WHITE, 1);
            }
            break;
        case KEY_02:
            if (record->event.pressed) {
                rgblight_sethsv_at(FAVORITE_COLOR, 2);
            } else {
                rgblight_sethsv_at(HSV_WHITE, 2);
            }
            break;
        case KEY_10:
            if (record->event.pressed) {
                rgblight_sethsv_at(FAVORITE_COLOR, 3);
            } else {
                rgblight_sethsv_at(HSV_WHITE, 3);
            }
            break;
        case KEY_11:
            if (record->event.pressed) {
                rgblight_sethsv_at(FAVORITE_COLOR, 4);
            } else {
                rgblight_sethsv_at(HSV_WHITE, 4);
            }
            break;
        case KEY_12:
            if (record->event.pressed) {
                rgblight_sethsv_at(FAVORITE_COLOR, 5);
            } else {
                rgblight_sethsv_at(HSV_WHITE, 5);
            }
            break;
        case KEY_20:
            if (record->event.pressed) {
                rgblight_sethsv_at(FAVORITE_COLOR, 6);
            } else {
                rgblight_sethsv_at(HSV_WHITE, 6);
            }
            break;
        case KEY_21:
            if (record->event.pressed) {
                rgblight_sethsv_at(FAVORITE_COLOR, 7);
            } else {
                rgblight_sethsv_at(HSV_WHITE, 7);
            }
            break;
        case KEY_22:
            if (record->event.pressed) {
                rgblight_sethsv_at(FAVORITE_COLOR, 8);
            } else {
                rgblight_sethsv_at(HSV_WHITE, 8);
            }
            break;
    }
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // Left encoder
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) { // Right encoder
        if (clockwise) {
            rgblight_decrease_hue_noeeprom();
        } else {
            rgblight_increase_hue_noeeprom();
        }
    }
}

const rgblight_segment_t PROGMEM quick7_capslock[] = RGBLIGHT_LAYER_SEGMENTS(
    {9,1,FAVORITE_COLOR},
    {12,1,FAVORITE_COLOR}
);
const rgblight_segment_t PROGMEM quick7_numlock[] = RGBLIGHT_LAYER_SEGMENTS(
    {10,1,FAVORITE_COLOR},
    {11,1,FAVORITE_COLOR}
);

const rgblight_segment_t* const PROGMEM quick7_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    quick7_capslock,
    quick7_numlock
);

void keyboard_post_init_user(void){
    rgblight_layers = quick7_rgb_layers;
    rgblight_sethsv(HSV_WHITE);
}

bool led_update_user(led_t led_state){
    rgblight_set_layer_state(0, led_state.caps_lock);
    rgblight_set_layer_state(1, led_state.num_lock);
    return true;
}