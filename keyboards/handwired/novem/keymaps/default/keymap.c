/* Copyright 2020 Jose I. Martinez
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    GITSTTS = SAFE_RANGE,
    GITPULL,
    GITPUSH,
    GITCOM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_ESCAPE,    KC_HOME, KC_DEL,
        MO(_FN)  ,    KC_UP  , KC_ENTER,
        KC_LEFT  ,    KC_DOWN, KC_RIGHT
    ),
    [_FN] = LAYOUT(
        KC_TRNS, GITCOM,   GITPUSH,
        KC_TRNS, GITSTTS,  GITPULL,
        KC_TRNS, KC_TRNS,  KC_TRNS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GITSTTS:
            if (record->event.pressed) {
                // when keycode GITSTTS is pressed
                SEND_STRING("git status");
            }
            break;
        case GITPULL:
            if (record->event.pressed) {
                // when keycode GITPULL is pressed
                SEND_STRING("git pull");
            }
            break;
       case GITPUSH:
            if (record->event.pressed) {
                // when keycode GITPUSH is pressed
                SEND_STRING("git push");
            }
            break;
       case GITCOM:
            if (record->event.pressed) {
                // when keycode GITCOM is pressed
                SEND_STRING("git commit -m ");
            }
            break;
       default:
           return  true;
    }
    return true;
}

