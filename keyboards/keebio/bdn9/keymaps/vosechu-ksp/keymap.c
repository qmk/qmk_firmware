/* Copyright 2019 Chuck Lauer Vose <vosechu@gmail.com>
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

// // Debugging
// #include <print.h>

#define BASE   TO(_BASE)
#define PANIC  TO(_PANIC)
#define FLIGHT TO(_FLIGHT)
#define RCS    TO(_RCS)

enum my_layers {
    _BASE = 0,
    _PANIC,
    _FLIGHT,
    _RCS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_MUTE, PANIC  , XXXXXXX,
        FLIGHT , XXXXXXX, RCS    ,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_PANIC] = LAYOUT(
        RESET  , BASE   , XXXXXXX,
        _______, XXXXXXX, _______,
        KC_F2  , KC_F5  , KC_F9
    ),
    [_FLIGHT] = LAYOUT(
        XXXXXXX, _______, KC_M   ,
        BASE   , KC_W   , _______,
        KC_A   , KC_S   , KC_D
    ),
    [_RCS] = LAYOUT(
        XXXXXXX, _______, XXXXXXX,
        _______, KC_I   , BASE   ,
        KC_J   , KC_K   , KC_L
    )
};

bool base_mode = false;
bool panic_mode = false;
bool flight_mode = false;
bool rcs_mode = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    base_mode = false;
    panic_mode = false;
    flight_mode = false;
    rcs_mode = false;

    switch (biton32(state)) {
    case _PANIC:
        panic_mode = true; // For use in encoder evaluation
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
    case _FLIGHT:
        flight_mode = true; // For use in encoder evaluation
        rgblight_sethsv_noeeprom(HSV_CYAN);
        break;
    case _RCS:
        rcs_mode = true; // For use in encoder evaluation
        rgblight_sethsv_noeeprom(HSV_BLUE);
        break;
    default: //  for any other layers, or the default layer
        base_mode = true;
        rgblight_sethsv_noeeprom(HSV_SPRINGGREEN);
        break;
    }
    return state;
}

void keyboard_post_init_user(void) {
    // Call the post init code.
    rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 1); // sets mode to Slow breathing without saving
    rgblight_sethsv_noeeprom(HSV_SPRINGGREEN);
}

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         uprintf("Keycode: %s\n", keycode);
//         if (record->event.pressed) {
//           print("pressed");
//           // Do something when pressed
//         } else {
//           print("unpressed");
//           // Do something else when release
//         }
//     }
//     return true;
// }

bool encoder_update_user(uint8_t index, bool clockwise) {
    if(base_mode == true) {
        if (index == 0) {
            if (clockwise) {
                // Volume up
                tap_code(KC_VOLU);
            } else {
                // Volume down
                tap_code(KC_VOLD);
            }
        }
        else if (index == 1) {
            if (clockwise) {
                // Time warp faster
                tap_code(KC_DOT);
            } else {
                // Time warp slower
                tap_code(KC_COMM);
            }
        }
    }

    if(rcs_mode == true) {
        if (index == 0) {
            if (clockwise) {
                // RCS Forward
                tap_code(KC_H);
            } else {
                // RCS Backward
                tap_code(KC_N);
            }
        }
        else if (index == 1) {
            if (clockwise) {
                // RCS Rotate Left
                tap_code(KC_Q);
            } else {
                // RCS Rotate Right
                tap_code(KC_E);
            }
        }
    }

    if(flight_mode == true) {
        if (index == 0) {
            if (clockwise) {
                // Throttle up
                tap_code(KC_LSFT);
            } else {
                // Throttle down
                tap_code(KC_LCTL);
            }
        }
        else if (index == 1) {
            if (clockwise) {
                // Trim left
                tap_code16(LALT(KC_A));
            } else {
                // Trim right
                tap_code16(LALT(KC_D));
            }
        }
    }
    return true;
}
